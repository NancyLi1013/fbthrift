/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <atomic>
#include <optional>
#include <thread>

#include <folly/ThreadLocal.h>
#include <folly/experimental/coro/BlockingWait.h>
#include <folly/io/async/AsyncSocket.h>
#include <folly/io/async/EventBase.h>
#include <folly/io/async/Request.h>
#include <folly/portability/GMock.h>
#include <folly/portability/GTest.h>
#include <folly/synchronization/Baton.h>
#include <thrift/lib/cpp2/PluggableFunction.h>
#include <thrift/lib/cpp2/async/AsyncProcessor.h>
#include <thrift/lib/cpp2/async/FutureRequest.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/async/RequestCallback.h>
#include <thrift/lib/cpp2/async/RequestChannel.h>
#include <thrift/lib/cpp2/async/RocketClientChannel.h>
#include <thrift/lib/cpp2/server/Cpp2Worker.h>
#include <thrift/lib/cpp2/server/RequestDebugLog.h>
#include <thrift/lib/cpp2/server/ServerInstrumentation.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>
#include <thrift/lib/cpp2/test/gen-cpp2/DebugTestService.h>
#include <thrift/lib/cpp2/test/gen-cpp2/InstrumentationTestService.h>
#include <thrift/lib/cpp2/transport/core/RequestStateMachine.h>
#include <thrift/lib/cpp2/transport/rocket/server/RocketRoutingHandler.h>
#include <thrift/lib/cpp2/util/ScopedServerInterfaceThread.h>

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::test;
using namespace std::literals::chrono_literals;
using namespace ::testing;

class InstrumentationRequestPayload : public folly::RequestData {
 public:
  static const folly::RequestToken& getRequestToken() {
    static folly::RequestToken token(
        "InstrumentationTest::InstrumentationRequestPayload");
    return token;
  }
  explicit InstrumentationRequestPayload(std::unique_ptr<folly::IOBuf> buf)
      : buf_(std::move(buf)) {}
  bool hasCallback() override { return false; }
  const folly::IOBuf* getPayload() { return buf_.get(); }

 private:
  std::unique_ptr<folly::IOBuf> buf_;
};

class InstrumentationTestProcessor
    : public InstrumentationTestServiceAsyncProcessor {
 public:
  explicit InstrumentationTestProcessor(InstrumentationTestServiceSvIf* iface)
      : InstrumentationTestServiceAsyncProcessor(iface) {}

  /**
   * Intercepts and clones incoming payload buffers, then passes them down to
   * method handlers.
   */
  void processSerializedCompressedRequest(
      ResponseChannelRequest::UniquePtr req,
      apache::thrift::SerializedCompressedRequest&& serializedRequest,
      apache::thrift::protocol::PROTOCOL_TYPES protType,
      apache::thrift::Cpp2RequestContext* context,
      folly::EventBase* eb,
      apache::thrift::concurrency::ThreadManager* tm) override {
    folly::RequestContext::get()->setContextData(
        InstrumentationRequestPayload::getRequestToken(),
        std::make_unique<InstrumentationRequestPayload>(
            serializedRequest.clone().uncompress().buffer));
    InstrumentationTestServiceAsyncProcessor::
        processSerializedCompressedRequest(
            std::move(req),
            std::move(serializedRequest),
            protType,
            context,
            eb,
            tm);
  }
};

class DebugInterface : public DebugTestServiceSvIf {
 public:
  void echo(std::string& r, std::unique_ptr<::std::string> s) override {
    r = folly::format("{}:{}", *s, folly::getCurrentThreadName().value()).str();
  }
};

class TestInterface : public InstrumentationTestServiceSvIf {
 public:
  auto requestGuard() {
    reqCount_++;
    return folly::makeGuard([&] { --reqCount_; });
  }

  folly::coro::Task<void> co_sendRequest() override {
    auto rg = requestGuard();
    auto ctx = folly::RequestContext::get();
    EXPECT_TRUE(
        ctx->setContextDataIfAbsent("TestInterface::co_sendRequest", nullptr));
    co_await finished_;
  }

  folly::coro::Task<apache::thrift::ServerStream<int32_t>>
  co_sendStreamingRequest() override {
    auto rg = requestGuard();
    co_await finished_;
    co_return folly::coro::co_invoke(
        []() -> folly::coro::AsyncGenerator<int32_t&&> { co_yield 0; });
  }

  folly::coro::Task<std::unique_ptr<::apache::thrift::test::IOBuf>>
  co_sendPayload(int32_t id, std::unique_ptr<::std::string> /*str*/) override {
    auto rg = requestGuard();
    auto payload = dynamic_cast<InstrumentationRequestPayload*>(
        folly::RequestContext::get()->getContextData(
            InstrumentationRequestPayload::getRequestToken()));
    EXPECT_NE(payload, nullptr);
    co_await finished_;
    co_return payload->getPayload()->clone();
  }

  void stopRequests() {
    finished_.post();
    while (reqCount_ > 0) {
      std::this_thread::yield();
    }
  }

  void waitForRequests(int32_t num) {
    while (reqCount_ != num) {
      std::this_thread::yield();
    }
  }

  void runCallback() override {
    if (callback_) {
      callback_(this);
    }
  }

  void runCallback2() override {
    if (callback2_) {
      callback2_(this);
    }
  }

  folly::coro::Task<void> co_wait(
      int value, bool busyWait, bool shallowRC) override {
    std::unique_ptr<folly::ShallowCopyRequestContextScopeGuard> g;
    if (shallowRC) {
      g = std::make_unique<folly::ShallowCopyRequestContextScopeGuard>();
    }
    auto rg = requestGuard();
    if (busyWait) {
      while (!finished_.ready()) {
        std::this_thread::yield();
      }
    }
    co_await finished_;
  }

  folly::coro::Task<void> co_noop() override { co_return; }

  std::unique_ptr<apache::thrift::AsyncProcessor> getProcessor() override {
    return std::make_unique<InstrumentationTestProcessor>(this);
  }

  void setCallback(folly::Function<void(TestInterface*)> cob) {
    callback_ = std::move(cob);
  }

  void setCallback2(folly::Function<void(TestInterface*)> cob) {
    callback2_ = std::move(cob);
  }

 private:
  folly::coro::Baton finished_;
  std::atomic<int32_t> reqCount_{0};
  folly::Function<void(TestInterface*)> callback_;
  folly::Function<void(TestInterface*)> callback2_;
};

class DebuggingFrameHandler : public rocket::SetupFrameHandler {
 public:
  explicit DebuggingFrameHandler(ThriftServer& server)
      : origServer_(server),
        reqRegistry_([] { return new RequestsRegistry(0, 0, 0); }) {
    auto tf =
        std::make_shared<PosixThreadFactory>(PosixThreadFactory::ATTACHED);
    tm_ = std::make_shared<SimpleThreadManager>(1, false);
    tm_->setNamePrefix("DebugInterface");
    tm_->threadFactory(move(tf));
    tm_->start();
  }
  std::optional<rocket::ProcessorInfo> tryHandle(
      const RequestSetupMetadata& meta) override {
    if (meta.interfaceKind_ref().has_value() &&
        meta.interfaceKind_ref().value() == InterfaceKind::DEBUGGING) {
      return rocket::ProcessorInfo{
          debug_, tm_, origServer_, reqRegistry_.get()};
    }
    return std::nullopt;
  }

 private:
  ThriftServer& origServer_;
  DebugInterface debug_;
  std::shared_ptr<ThreadManager> tm_;
  folly::ThreadLocal<RequestsRegistry> reqRegistry_;
};

namespace {
static std::atomic<uint64_t> currentTick = 0;

THRIFT_PLUGGABLE_FUNC_SET(
    std::unique_ptr<apache::thrift::rocket::SetupFrameHandler>,
    createRocketDebugSetupFrameHandler,
    apache::thrift::ThriftServer& thriftServer) {
  return std::make_unique<DebuggingFrameHandler>(thriftServer);
}

THRIFT_PLUGGABLE_FUNC_SET(uint64_t, getCurrentServerTick) {
  return currentTick;
}

std::set<std::string> excludeFromRecentRequestsCount;
THRIFT_PLUGGABLE_FUNC_SET(
    bool, includeInRecentRequestsCount, const std::string_view methodName) {
  return !excludeFromRecentRequestsCount.count(std::string{methodName});
}

} // namespace

class RequestInstrumentationTest : public testing::Test {
 protected:
  RequestInstrumentationTest() {}

  void SetUp() override { impl_ = std::make_unique<Impl>(); }

  std::shared_ptr<TestInterface> handler() { return impl_->handler_; }
  apache::thrift::ScopedServerInterfaceThread& server() {
    return impl_->server_;
  }
  ThriftServer* thriftServer() { return impl_->thriftServer_; }

  ThriftServer::ServerSnapshot getServerSnapshot() {
    return thriftServer()->getServerSnapshot().get();
  }

  ThriftServer::ServerSnapshot waitForRequestsThenSnapshot(size_t reqNum) {
    SCOPE_EXIT { handler()->stopRequests(); };
    handler()->waitForRequests(reqNum);
    return getServerSnapshot();
  }

  ThriftServer::RequestSnapshots getRequestSnapshots(size_t reqNum) {
    auto serverReqSnapshots = waitForRequestsThenSnapshot(reqNum).requests;
    EXPECT_EQ(serverReqSnapshots.size(), reqNum);
    return serverReqSnapshots;
  }

  std::vector<intptr_t> getRootIdsOnThreads() {
    std::vector<intptr_t> results;
    for (auto& root : folly::RequestContext::getRootIdsFromAllThreads()) {
      if (!root.id) {
        continue;
      }
      results.push_back(root.id);
    }
    return results;
  }

  auto makeHeaderClient() {
    return server().newClient<InstrumentationTestServiceAsyncClient>(
        nullptr, [&](auto socket) mutable {
          return HeaderClientChannel::newChannel(std::move(socket));
        });
  }
  auto makeRocketClient() {
    return server().newClient<InstrumentationTestServiceAsyncClient>(
        nullptr, apache::thrift::RocketClientChannel::newChannel);
  }

  auto makeDebugClient() {
    return server().newClient<DebugTestServiceAsyncClient>(
        nullptr, [](auto socket) mutable {
          RequestSetupMetadata meta;
          meta.interfaceKind_ref() = InterfaceKind::DEBUGGING;
          return apache::thrift::RocketClientChannel::newChannelWithMetadata(
              std::move(socket), std::move(meta));
        });
  }

  template <typename ClientChannelT>
  auto makeSingleSocketClient(folly::EventBase* eventBase) {
    struct ViaEventBaseDeleter {
      folly::Executor::KeepAlive<folly::EventBase> ka_;

      void operator()(InstrumentationTestServiceAsyncClient* client) const {
        ka_->add([client] { delete client; });
      }
    };
    ClientChannel::Ptr channel;
    eventBase->runInEventBaseThreadAndWait([&] {
      auto socket =
          folly::AsyncSocket::newSocket(eventBase, server().getAddress());
      channel = ClientChannelT::newChannel(std::move(socket));
    });
    return std::
        unique_ptr<InstrumentationTestServiceAsyncClient, ViaEventBaseDeleter>{
            new InstrumentationTestServiceAsyncClient(std::move(channel)),
            {folly::Executor::getKeepAliveToken(eventBase)}};
  }

  auto rpcOptionsFromHeaders(
      const std::map<std::string, std::string>& headers) {
    RpcOptions rpcOptions;
    for (const auto& kv : headers) {
      rpcOptions.setWriteHeader(kv.first, kv.second);
    }
    return rpcOptions;
  }

  struct Impl {
    Impl(ScopedServerInterfaceThread::ServerConfigCb&& serverCfgCob = {})
        : handler_(std::make_shared<TestInterface>()),
          server_(handler_, "::1", 0, std::move(serverCfgCob)),
          thriftServer_(
              dynamic_cast<ThriftServer*>(&server_.getThriftServer())) {}
    std::shared_ptr<TestInterface> handler_;
    apache::thrift::ScopedServerInterfaceThread server_;
    ThriftServer* thriftServer_;
  };
  std::unique_ptr<Impl> impl_;
};

TEST_F(RequestInstrumentationTest, simpleRocketRequestTest) {
  size_t reqNum = 5;
  auto client = server().newClient<InstrumentationTestServiceAsyncClient>(
      nullptr, [](auto socket) mutable {
        return apache::thrift::RocketClientChannel::newChannel(
            std::move(socket));
      });

  for (size_t i = 0; i < reqNum; i++) {
    client->semifuture_sendStreamingRequest();
    client->semifuture_sendRequest();
  }
  handler()->waitForRequests(2 * reqNum);

  // we expect all requests to get off the thread, eventually
  int attempt = 0;
  while (attempt < 5 && getRootIdsOnThreads().size() > 0) {
    sleep(1);
    attempt++;
  }
  EXPECT_LT(attempt, 5);

  for (auto& reqSnapshot : getRequestSnapshots(2 * reqNum)) {
    auto methodName = reqSnapshot.getMethodName();
    EXPECT_NE(reqSnapshot.getRootRequestContextId(), 0);
    EXPECT_TRUE(
        methodName == "sendRequest" || methodName == "sendStreamingRequest");
  }
}

TEST_F(RequestInstrumentationTest, threadSnapshot) {
  auto client = server().newClient<InstrumentationTestServiceAsyncClient>(
      nullptr, [](auto socket) mutable {
        return apache::thrift::RocketClientChannel::newChannel(
            std::move(socket));
      });

  client->semifuture_sendRequest();
  handler()->waitForRequests(1);
  client->semifuture_wait(0, true, false);

  handler()->waitForRequests(2);
  auto onThreadReqs = getRootIdsOnThreads();
  auto allReqs = getRequestSnapshots(2);
  EXPECT_EQ(1, onThreadReqs.size());
  EXPECT_EQ(2, allReqs.size());

  for (const auto& req : allReqs) {
    if (req.getMethodName() == "wait") {
      EXPECT_EQ(req.getRootRequestContextId(), onThreadReqs[0]);
    } else {
      EXPECT_NE(req.getRootRequestContextId(), onThreadReqs[0]);
    }
  }
}

TEST_F(RequestInstrumentationTest, PendingTaskCount) {
  auto client = makeRocketClient();
  folly::Baton baton;
  folly::Baton baton2;
  handler()->setCallback([&](TestInterface* ti) {
    ti->getThreadManager()->add([] {});
    ti->getThreadManager()->add([] {});
    ti->getThreadManager()->add([] {});
    baton.post();
    baton2.wait();
  });
  auto firstReq = client->semifuture_runCallback();
  baton.wait();
  EXPECT_EQ(3, thriftServer()->getThreadManager()->pendingTaskCount());
  EXPECT_EQ(0, thriftServer()->getThreadManager()->pendingUpstreamTaskCount());

  handler()->setCallback([&](TestInterface*) {});
  auto secondReq = client->semifuture_runCallback();

  auto expire = std::chrono::steady_clock::now() + 5s;
  while (thriftServer()->getThreadManager()->pendingUpstreamTaskCount() < 1 &&
         std::chrono::steady_clock::now() < expire) {
    std::this_thread::yield();
  }
  EXPECT_EQ(4, thriftServer()->getThreadManager()->pendingTaskCount());
  EXPECT_EQ(1, thriftServer()->getThreadManager()->pendingUpstreamTaskCount());

  baton2.post();
  std::move(firstReq).get();
  std::move(secondReq).get();
}

TEST_F(RequestInstrumentationTest, threadSnapshotWithShallowRC) {
  auto client = makeRocketClient();

  client->semifuture_sendRequest();
  handler()->waitForRequests(1);
  client->semifuture_wait(0, true, true);
  handler()->waitForRequests(2);

  auto onThreadReqs = getRootIdsOnThreads();
  auto allReqs = getRequestSnapshots(2);
  EXPECT_EQ(1, onThreadReqs.size());
  EXPECT_EQ(2, allReqs.size());

  for (const auto& req : allReqs) {
    if (req.getMethodName() == "wait") {
      EXPECT_EQ(req.getRootRequestContextId(), onThreadReqs.front());
    } else {
      EXPECT_NE(req.getRootRequestContextId(), onThreadReqs.front());
    }
  }
}

TEST_F(RequestInstrumentationTest, debugInterfaceTest) {
  size_t reqNum = 5;

  auto client = makeRocketClient();
  auto debugClient = makeDebugClient();
  for (size_t i = 0; i < reqNum; i++) {
    client->semifuture_sendStreamingRequest();
    client->semifuture_sendRequest();
  }

  auto echoed = debugClient->semifuture_echo("echome").get();
  EXPECT_TRUE(folly::StringPiece(echoed).startsWith("echome:DebugInterface-"));

  for (auto& reqSnapshot : getRequestSnapshots(2 * reqNum)) {
    auto methodName = reqSnapshot.getMethodName();
    EXPECT_TRUE(
        methodName == "sendRequest" || methodName == "sendStreamingRequest");
  }
}

TEST_F(RequestInstrumentationTest, simpleHeaderRequestTest) {
  size_t reqNum = 5;
  auto client = makeHeaderClient();

  for (size_t i = 0; i < reqNum; i++) {
    client->semifuture_sendRequest();
  }

  for (auto& reqSnapshot : getRequestSnapshots(reqNum)) {
    EXPECT_EQ(reqSnapshot.getMethodName(), "sendRequest");
    EXPECT_NE(reqSnapshot.getRootRequestContextId(), 0);
    EXPECT_EQ(
        reqSnapshot.getFinishedTimestamp(),
        std::chrono::steady_clock::time_point{
            std::chrono::steady_clock::duration::zero()});
  }
}

TEST_F(RequestInstrumentationTest, ConnectionSnapshotsTest) {
  auto getLocalAddressOf = [&](auto& client) {
    auto& clientChannel = dynamic_cast<ClientChannel&>(*client.getChannel());
    auto transport = clientChannel.getTransport();
    EXPECT_NE(transport, nullptr);
    return transport->getLocalAddress();
  };

  {
    folly::ScopedEventBaseThread eventBaseThread;
    auto evb = eventBaseThread.getEventBase();
    auto client1 = makeSingleSocketClient<RocketClientChannel>(evb);
    auto client2 = makeSingleSocketClient<RocketClientChannel>(evb);
    auto client3 = makeSingleSocketClient<RocketClientChannel>(evb);
    auto headerClient = makeSingleSocketClient<HeaderClientChannel>(evb);

    for (size_t i = 0; i < 10; ++i) {
      client1->semifuture_sendRequest();
    }
    for (size_t i = 0; i < 20; ++i) {
      client2->semifuture_sendRequest();
    }
    client3->semifuture_sendStreamingRequest();
    // Header connections are not counted towards connection snapshots
    headerClient->semifuture_sendRequest();

    auto serverSnapshot = waitForRequestsThenSnapshot(32);
    EXPECT_EQ(serverSnapshot.requests.size(), 32);
    auto& connections = serverSnapshot.connections;
    EXPECT_EQ(connections.size(), 3);

    auto client1Snapshot = connections.find(getLocalAddressOf(*client1));
    ASSERT_NE(client1Snapshot, connections.end());
    EXPECT_EQ(client1Snapshot->second.numActiveRequests, 10);

    auto client2Snapshot = connections.find(getLocalAddressOf(*client2));
    ASSERT_NE(client2Snapshot, connections.end());
    EXPECT_EQ(client2Snapshot->second.numActiveRequests, 20);

    auto client3Snapshot = connections.find(getLocalAddressOf(*client3));
    ASSERT_NE(client3Snapshot, connections.end());
    EXPECT_EQ(client3Snapshot->second.numActiveRequests, 1);

    handler()->stopRequests();
    // Wait for requests to be marked as completed
    while (thriftServer()->getActiveRequests() > 0) {
      std::this_thread::yield();
    }
  }

  // Client-side connections are closed. The server-side sockets may not be
  // closed yet! Let's give it some leeway.
  auto deadline = std::chrono::steady_clock::now() + 1s;
  while (deadline > std::chrono::steady_clock::now()) {
    if (getServerSnapshot().connections.empty()) {
      break;
    }
    std::this_thread::yield();
  }
  EXPECT_TRUE(getServerSnapshot().connections.empty());
}

class RequestInstrumentationTestP
    : public RequestInstrumentationTest,
      public ::testing::WithParamInterface<std::tuple<int, int, bool>> {
 protected:
  size_t finishedRequestsLimit;
  size_t reqNum;
  bool rocket;
  void SetUp() override {
    std::tie(finishedRequestsLimit, reqNum, rocket) = GetParam();
    impl_ = std::make_unique<Impl>([&](auto& ts) {
      ts.setMaxFinishedDebugPayloadsPerWorker(finishedRequestsLimit);
    });
  }
};

TEST_P(RequestInstrumentationTestP, requestPayloadTest) {
  std::array<std::string, 4> strList = {
      "apache", "thrift", "test", "InstrumentationTest"};
  auto client = rocket ? makeRocketClient() : makeHeaderClient();

  std::vector<folly::SemiFuture<folly::IOBuf>> tasks;
  int32_t reqId = 0;
  for (const auto& testStr : strList) {
    auto task = client->semifuture_sendPayload(reqId, testStr)
                    .deferValue([](const apache::thrift::test::IOBuf& buf) {
                      return buf;
                    });
    tasks.emplace_back(std::move(task));
    reqId++;
  }
  auto reqSnapshots = getRequestSnapshots(strList.size());

  auto interceptedPayloadList =
      folly::collect(tasks.begin(), tasks.end()).get();

  std::set<const folly::IOBuf*, folly::IOBufLess> snapshotPayloadSet;
  for (const auto& reqSnapshot : reqSnapshots) {
    snapshotPayloadSet.insert(&reqSnapshot.getPayload());
  }

  EXPECT_EQ(interceptedPayloadList.size(), snapshotPayloadSet.size());
  for (const auto& interceptedPayload : interceptedPayloadList) {
    auto it = snapshotPayloadSet.find(&interceptedPayload);
    EXPECT_TRUE(it != snapshotPayloadSet.end());
  }
}

TEST_F(RequestInstrumentationTest, rocketSnapshotContainsMetadataHeadersTest) {
  std::map<std::string, std::string> originalHeaders = {
      {"header1", "value1"}, {"header2", "value2"}};
  auto client = server().newClient<InstrumentationTestServiceAsyncClient>(
      nullptr, [](auto socket) mutable {
        return apache::thrift::RocketClientChannel::newChannel(
            std::move(socket));
      });
  auto rpcOptions = rpcOptionsFromHeaders(originalHeaders);

  client->header_semifuture_sendRequest(rpcOptions);
  handler()->waitForRequests(1);
  auto reqs = getRequestSnapshots(1);
  EXPECT_EQ(reqs.size(), 1);

  auto snapshotHeaders = reqs[0].getHeaders();
  EXPECT_EQ(snapshotHeaders.size(), originalHeaders.size());
  for (const auto& kv : snapshotHeaders) {
    auto original = folly::get_ptr(originalHeaders, kv.first);
    EXPECT_TRUE(original != nullptr)
        << "expected to find " << kv.first << " in the original headers";
    EXPECT_EQ(kv.second, *original);
  }
}

TEST_F(
    RequestInstrumentationTest,
    headerSnapshotDoesNotContainMetadataHeadersTest) {
  auto client = makeHeaderClient();
  RpcOptions rpcOptions;
  rpcOptions.setWriteHeader("header", "value");
  client->header_semifuture_sendRequest(rpcOptions);
  handler()->waitForRequests(1);

  auto reqs = getRequestSnapshots(1);
  EXPECT_EQ(reqs.size(), 1);

  auto snapshotHeaders = reqs[0].getHeaders();
  EXPECT_EQ(snapshotHeaders.size(), 0);
}

TEST_F(RequestInstrumentationTest, snapshotRecentRequestCountsTest) {
  currentTick = 0;
  folly::Baton baton;
  handler()->setCallback([&](TestInterface*) { baton.post(); });

  // Make a header request
  auto headerClient = makeHeaderClient();
  auto req1 = headerClient->semifuture_runCallback();
  baton.wait();
  baton.reset();

  // Make a rocket request
  auto rocketClient = makeRocketClient();
  currentTick = 100;
  auto req2 = rocketClient->semifuture_runCallback();
  baton.wait();

  auto snapshot = getServerSnapshot();
  // arrived requests
  EXPECT_EQ(snapshot.recentCounters[0].first, 1);
  EXPECT_EQ(snapshot.recentCounters[100].first, 1);
}

class RecentRequestsTest : public RequestInstrumentationTest,
                           public ::testing::WithParamInterface<bool> {
 protected:
  bool rocket;
  void SetUp() override {
    rocket = GetParam();
    RequestInstrumentationTest::SetUp();
  }
};

TEST_P(RecentRequestsTest, Exclude) {
  auto client = rocket ? makeRocketClient() : makeHeaderClient();
  auto debugClient = makeDebugClient();

  auto g = folly::makeGuard([] { excludeFromRecentRequestsCount.clear(); });
  excludeFromRecentRequestsCount.insert("runCallback");

  client->sync_runCallback();
  client->sync_runCallback2();
  auto f = client->semifuture_sendRequest();
  handler()->waitForRequests(1);
  auto snapshot = getServerSnapshot();
  // there were 3 requests that arrived but one should be excluded
  int expectedArrived = 2;
  EXPECT_EQ(snapshot.recentCounters.at(0).first, expectedArrived);
  // there is one active request
  EXPECT_EQ(snapshot.recentCounters.at(0).second, 1);

  handler()->stopRequests();
  f.wait();

  snapshot = getServerSnapshot();
  EXPECT_EQ(snapshot.recentCounters.at(0).first, expectedArrived);
  // there are no active requests
  EXPECT_EQ(snapshot.recentCounters.at(0).second, 0);
}

INSTANTIATE_TEST_CASE_P(
    RecentRequestsTest, RecentRequestsTest, testing::Values(true, false));

class RequestInstrumentationTestWithFinishedDebugPayload
    : public RequestInstrumentationTest {
 protected:
  void SetUp() override {
    impl_ = std::make_unique<Impl>(
        [&](auto& ts) { ts.setMaxFinishedDebugPayloadsPerWorker(1); });
  }
};

TEST_F(
    RequestInstrumentationTestWithFinishedDebugPayload,
    snapshotStartedProcessingTest) {
  auto client = makeRocketClient();

  folly::Baton baton1;
  folly::Baton baton2;
  folly::Baton baton3;

  // "finished" request
  handler()->setCallback([&](TestInterface*) { baton1.post(); });
  auto req1 = client->semifuture_runCallback();
  baton1.wait();

  // "started processing" request
  handler()->setCallback([&](TestInterface*) {
    baton2.post();
    baton3.wait();
  });
  auto req2 = client->semifuture_runCallback();
  baton2.wait();

  // "not started processing" request
  handler()->setCallback([](TestInterface*) {});
  auto req3 = client->semifuture_runCallback();
  while (thriftServer()->getActiveRequests() < 2) {
    std::this_thread::yield();
  }

  // record and sort snapshots
  auto reqSnapshots = getServerSnapshot().requests;
  baton3.post();
  std::vector<int> idxs;
  idxs.resize(reqSnapshots.size());
  std::iota(idxs.begin(), idxs.end(), 0);
  std::sort(idxs.begin(), idxs.end(), [&](auto i, auto j) {
    const auto& s1 = reqSnapshots[i];
    const auto& s2 = reqSnapshots[j];
    return s1.getCreationTimestamp() < s2.getCreationTimestamp();
  });

  // test
  ASSERT_EQ(reqSnapshots.size(), 3);
  EXPECT_NE(
      reqSnapshots[idxs[0]].getFinishedTimestamp().time_since_epoch().count(),
      0);
  EXPECT_TRUE(reqSnapshots[idxs[0]].getStartedProcessing());
  EXPECT_TRUE(reqSnapshots[idxs[1]].getStartedProcessing());
  EXPECT_FALSE(reqSnapshots[idxs[2]].getStartedProcessing());

  // cleanup
  std::move(req1).get();
  std::move(req2).get();
  std::move(req3).get();
}

class ServerInstrumentationTest : public testing::Test {};

TEST_F(ServerInstrumentationTest, simpleServerTest) {
  ThriftServer serverNotServing;
  ScopedServerInterfaceThread server0(std::make_shared<TestInterface>());
  // We need to make sure server is really serving, the simplest way is
  // to wait for the first request to be completed.
  folly::coro::blockingWait(
      server0.newClient<InstrumentationTestServiceAsyncClient>()->co_noop());
  {
    ScopedServerInterfaceThread server1(std::make_shared<TestInterface>());
    folly::coro::blockingWait(
        server1.newClient<InstrumentationTestServiceAsyncClient>()->co_noop());
    EXPECT_EQ(
        instrumentation::getServerCount(
            instrumentation::kThriftServerTrackerKey),
        2);
  }
  EXPECT_EQ(
      instrumentation::getServerCount(instrumentation::kThriftServerTrackerKey),
      1);
}

TEST_P(RequestInstrumentationTestP, FinishedRequests) {
  auto client = rocket ? makeRocketClient() : makeHeaderClient();

  for (size_t i = 0; i < reqNum; i++) {
    client->semifuture_sendRequest();
  }

  handler()->waitForRequests(reqNum);
  handler()->stopRequests();

  // we expect all requests to stop now ...
  {
    size_t expected = std::min(reqNum, finishedRequestsLimit);
    int i = 0;
    while (i < 5 &&
           thriftServer()->getServerSnapshot().get().requests.size() !=
               expected) {
      sleep(1);
      i++;
    }
    EXPECT_LT(i, 5);
  }

  auto serverSnapshot = thriftServer()->getServerSnapshot().get();
  auto serverReqSnapshots = serverSnapshot.requests;
  EXPECT_EQ(serverReqSnapshots.size(), std::min(reqNum, finishedRequestsLimit));
  for (auto& req : serverReqSnapshots) {
    EXPECT_EQ(req.getMethodName(), "sendRequest");
    EXPECT_NE(req.getRootRequestContextId(), 0);
    EXPECT_NE(
        req.getFinishedTimestamp(),
        std::chrono::steady_clock::time_point{
            std::chrono::steady_clock::duration::zero()});
  }
}

INSTANTIATE_TEST_CASE_P(
    FinishedRequestsSequence,
    RequestInstrumentationTestP,
    testing::Combine(
        testing::Values(0, 3, 20),
        testing::Values(3, 10),
        testing::Values(true, false)));

class RegistryTests : public testing::TestWithParam<std::tuple<size_t, bool>> {
 protected:
  // test params
  int finishedMax_;
  bool requestKeepsRegistryAlive_;

  void SetUp() override {
    std::tie(finishedMax_, requestKeepsRegistryAlive_) = GetParam();
  }

  class MockRequest : public ResponseChannelRequest {
    Cpp2ConnContext mockConnCtx_;
    Cpp2RequestContext mockReqCtx_{&mockConnCtx_};

    // mock ResponseChannelRequest so that it keeps registry alive.
    std::shared_ptr<RequestsRegistry> registry_;

   public:
    MockRequest(
        RequestsRegistry::DebugStub& stub,
        std::shared_ptr<RequestsRegistry> registry)
        : registry_(registry), stateMachine_(true, controller_) {
      new (&stub) RequestsRegistry::DebugStub(
          *registry,
          *this,
          mockReqCtx_,
          std::make_shared<folly::RequestContext>(0),
          apache::thrift::protocol::PROTOCOL_TYPES::T_COMPACT_PROTOCOL,
          rocket::Payload(),
          stateMachine_);
    }

    auto registry() { return registry_; }

    MOCK_METHOD(bool, isActive, (), (const, override));
    MOCK_METHOD(bool, isOneway, (), (const, override));
    MOCK_METHOD(bool, includeEnvelope, (), (const, override));
    MOCK_METHOD(bool, tryStartProcessing, (), (override));
    MOCK_METHOD(
        void,
        sendReply,
        (ResponsePayload&&,
         MessageChannel::SendCallback*,
         folly::Optional<uint32_t>),
        (override));
    MOCK_METHOD(
        void,
        sendException,
        (ResponsePayload&&, MessageChannel::SendCallback*),
        (override));
    MOCK_METHOD(
        void,
        sendErrorWrapped,
        (folly::exception_wrapper, std::string),
        (override));

   private:
    folly::observer::SimpleObservable<AdaptiveConcurrencyController::Config>
        oConfig{AdaptiveConcurrencyController::Config{}};
    AdaptiveConcurrencyController controller_{oConfig.getObserver()};
    RequestStateMachine stateMachine_;
  };
};

// Test registry destruction order. The hard case here is
// when ResponseChannelRequest is the only thing keeping RequestsRegistry
// alive.
TEST_P(RegistryTests, Destruction) {
  auto registry = std::make_shared<RequestsRegistry>(0, 0, finishedMax_);

  auto req = RequestsRegistry::makeRequest<MockRequest>(registry);
  if (requestKeepsRegistryAlive_) {
    registry = nullptr;
  }
  EXPECT_EQ(req->registry()->getFinished().size(), 0);

  // Create requests and "finish" them (by releasing unique_ptr).
  auto req2 = RequestsRegistry::makeRequest<MockRequest>(req->registry());
  req2.reset();
  EXPECT_EQ(req->registry()->getFinished().size(), std::min(1, finishedMax_));

  auto req3 = RequestsRegistry::makeRequest<MockRequest>(req->registry());
  req3.reset();
  EXPECT_EQ(req->registry()->getFinished().size(), std::min(2, finishedMax_));

  // "finish" last active request to initiate tearing down registry.
  req.reset();
}

INSTANTIATE_TEST_CASE_P(
    RegistryTestsSequence,
    RegistryTests,
    testing::Combine(
        testing::Values(0, 1, 2, 10), testing::Values(true, false)));

TEST(RegistryTests, RootId) {
  RequestsRegistry registry(0, 0, 0);
  auto rootid = registry.genRootId();
  auto rootid2 = registry.genRootId();
  EXPECT_NE(rootid, rootid2);

  RequestsRegistry registry2(0, 0, 0);
  auto rootid3 = registry2.genRootId();
  EXPECT_NE(rootid3, rootid);
  EXPECT_NE(rootid3, rootid2);
}

TEST(RegistryTests, ManyRegistries) {
  // Verify we can create > 4096 RequestRegistries
  for (size_t i = 0; i < 50; i++) {
    std::vector<std::unique_ptr<RequestsRegistry>> registries;
    for (size_t j = 0; j < 100; ++j) {
      auto registry = std::make_unique<RequestsRegistry>(0, 0, 0);
      auto rootid = registry->genRootId();
      auto reqid = RequestsRegistry::getRequestId(rootid);
      registries.push_back(std::move(registry));
    }
    // destruction orders deal reusing request ids correctly
    std::random_shuffle(registries.begin(), registries.end());
  }
}

TEST(RegistryTests, ManyRegistriesDeathTest) {
  // Verify we can simultaneously maintain up to 4096 registries
  std::list<RequestsRegistry> registries;
  for (size_t i = 0; i < 4096; i++) {
    registries.emplace_back(0, 0, 0).genRootId();
  }
  // We also limit number of concurrent registries to 4096
  EXPECT_EXIT(
      registries.emplace_back(0, 0, 0).genRootId(),
      ::testing::KilledBySignal(SIGABRT),
      "");
}

class MaxRequestsTest : public RequestInstrumentationTest,
                        public ::testing::WithParamInterface<bool> {
 protected:
  bool rocket;
  void SetUp() override {
    rocket = GetParam();
    impl_ = std::make_unique<Impl>([&](auto& ts) {
      ts.setMaxRequests(1);
      ts.setMethodsBypassMaxRequestsLimit({"runCallback2"});
    });
  }
};

TEST_P(MaxRequestsTest, Bypass) {
  auto client = rocket ? makeRocketClient() : makeHeaderClient();

  client->semifuture_sendRequest();
  handler()->waitForRequests(1);

  EXPECT_ANY_THROW(client->sync_runCallback());
  EXPECT_NO_THROW(client->sync_runCallback2());
  handler()->stopRequests();
}

INSTANTIATE_TEST_CASE_P(
    MaxRequestsTestsSequence, MaxRequestsTest, testing::Values(true, false));

class TimestampsTest
    : public RequestInstrumentationTest,
      public ::testing::WithParamInterface<std::tuple<bool, bool>> {
 protected:
  bool rocket;
  bool forceTimestamps;
  std::optional<server::TServerObserver::CallTimestamps> timestamps;
  std::optional<folly::Baton<>> timestampObserverComplete;
  struct Observer : public server::TServerObserver {
    explicit Observer(folly::Function<void(const CallTimestamps&)>&& f)
        : server::TServerObserver(1), f_(std::move(f)) {}
    void callCompleted(const CallTimestamps& timestamps) override {
      f_(timestamps);
    }
    folly::Function<void(const CallTimestamps&)> f_;
  };
  void SetUp() override {
    std::tie(rocket, forceTimestamps) = GetParam();
    impl_ = std::make_unique<Impl>([&](auto& ts) {
      if (forceTimestamps) {
        ts.setObserver(std::make_shared<Observer>([&](auto& t) {
          timestamps = t;
          if (timestampObserverComplete) {
            timestampObserverComplete->post();
          }
        }));
      }
    });
  }
};

namespace {
void validateTimestamps(
    bool expectTimestamps,
    std::chrono::steady_clock::time_point started,
    const server::TServerObserver::PreHandlerTimestamps& timestamps) {
  auto now = std::chrono::steady_clock::now();
  auto zero = std::chrono::steady_clock::time_point();
  if (expectTimestamps) {
    EXPECT_GT(timestamps.readEnd, started);
    EXPECT_GT(timestamps.processBegin, timestamps.readEnd);
    EXPECT_LE(timestamps.processBegin, now);
    EXPECT_TRUE(timestamps.processDelayLatencyUsec().has_value());
    EXPECT_GT(timestamps.processDelayLatencyUsec().value(), 0);
  } else {
    EXPECT_EQ(timestamps.readEnd, zero);
    EXPECT_EQ(timestamps.processBegin, timestamps.readEnd);
    EXPECT_FALSE(timestamps.processDelayLatencyUsec().has_value());
  }
}
} // namespace

TEST_P(TimestampsTest, Basic) {
  timestampObserverComplete.emplace();
  auto client = rocket ? makeRocketClient() : makeHeaderClient();
  auto now = std::chrono::steady_clock::now();
  handler()->setCallback([&](TestInterface* ti) {
    validateTimestamps(
        forceTimestamps, now, ti->getConnectionContext()->getTimestamps());
    now = std::chrono::steady_clock::now();
  });
  client->sync_runCallback();
  if (forceTimestamps) {
    timestampObserverComplete->try_wait_for(1s);
    EXPECT_GT(timestamps->processEnd, now);
    EXPECT_GT(timestamps->writeBegin, timestamps->processEnd);
    EXPECT_GT(timestamps->writeEnd, timestamps->writeBegin);
  }
}

TEST_P(TimestampsTest, QueueTimeout) {
  if (!forceTimestamps) {
    return;
  }
  auto client = rocket ? makeRocketClient() : makeHeaderClient();

  // force queue timeout by blocking CPU worker
  folly::Baton<> receivedBlockingCall;
  folly::Baton<> done;
  handler()->setCallback([&](TestInterface*) {
    receivedBlockingCall.post();
    done.wait();
  });
  auto blockingCall = client->semifuture_runCallback();
  receivedBlockingCall.wait();
  auto guard = folly::makeGuard([&] {
    done.post();
    std::move(blockingCall).get();
  });

  try {
    RpcOptions rpcOptions;
    rpcOptions.setQueueTimeout(std::chrono::milliseconds(1));
    client->sync_runCallback(rpcOptions);
    FAIL() << "Expected exception to be thrown";
  } catch (const TApplicationException& ex) {
    ASSERT_EQ(ex.getType(), TApplicationException::TIMEOUT);
  }
  // callCompleted should not be called for requests which timed out the queue.
  EXPECT_FALSE(timestamps.has_value());
}

INSTANTIATE_TEST_CASE_P(
    TimestampsTestSequence,
    TimestampsTest,
    testing::Combine(
        testing::Values(true, false), testing::Values(true, false)));
