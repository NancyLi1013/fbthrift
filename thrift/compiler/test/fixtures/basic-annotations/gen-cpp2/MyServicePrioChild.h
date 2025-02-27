/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/service_h.h>

#include "thrift/compiler/test/fixtures/basic-annotations/gen-cpp2/MyServicePrioChildAsyncClient.h"
#include "thrift/compiler/test/fixtures/basic-annotations/gen-cpp2/module_types.h"
#include "thrift/compiler/test/fixtures/basic-annotations/gen-cpp2/MyServicePrioParent.h"

namespace folly {
  class IOBuf;
  class IOBufQueue;
}
namespace apache { namespace thrift {
  class Cpp2RequestContext;
  class BinaryProtocolReader;
  class CompactProtocolReader;
  namespace transport { class THeader; }
}}

namespace cpp2 {

class MyServicePrioChildSvAsyncIf {
 public:
  virtual ~MyServicePrioChildSvAsyncIf() {}
  virtual void async_tm_pang(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) = 0;
  virtual folly::Future<folly::Unit> future_pang() = 0;
  virtual folly::SemiFuture<folly::Unit> semifuture_pang() = 0;
};

class MyServicePrioChildAsyncProcessor;

class MyServicePrioChildSvIf : public MyServicePrioChildSvAsyncIf, virtual public ::cpp2::MyServicePrioParentSvIf {
 public:
  typedef MyServicePrioChildAsyncProcessor ProcessorType;
  std::unique_ptr<apache::thrift::AsyncProcessor> getProcessor() override;


  virtual void pang();
  folly::Future<folly::Unit> future_pang() override;
  folly::SemiFuture<folly::Unit> semifuture_pang() override;
  void async_tm_pang(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) override;
 private:
  std::atomic<apache::thrift::detail::si::InvocationType> __fbthrift_invocation_pang{apache::thrift::detail::si::InvocationType::AsyncTm};
};

class MyServicePrioChildSvNull : public MyServicePrioChildSvIf, virtual public ::cpp2::MyServicePrioParentSvIf {
 public:
  void pang() override;
};

class MyServicePrioChildAsyncProcessor : public ::cpp2::MyServicePrioParentAsyncProcessor {
 public:
  const char* getServiceName() override;
  void getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) override;
  using BaseAsyncProcessor = ::cpp2::MyServicePrioParentAsyncProcessor;
 protected:
  MyServicePrioChildSvIf* iface_;
 public:
  void processSerializedCompressedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) override;
 public:
  using ProcessFuncs = GeneratedAsyncProcessor::ProcessFuncs<MyServicePrioChildAsyncProcessor>;
  using ProcessMap = GeneratedAsyncProcessor::ProcessMap<ProcessFuncs>;
  static const MyServicePrioChildAsyncProcessor::ProcessMap& getOwnProcessMap();
 private:
  static const MyServicePrioChildAsyncProcessor::ProcessMap kOwnProcessMap_;
 private:
  template <typename ProtocolIn_, typename ProtocolOut_>
  void setUpAndProcess_pang(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_pang(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static apache::thrift::LegacySerializedResponse return_pang(int32_t protoSeqId, apache::thrift::ContextStack* ctx);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_pang(apache::thrift::ResponseChannelRequest::UniquePtr req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
 public:
  MyServicePrioChildAsyncProcessor(MyServicePrioChildSvIf* iface) :
      ::cpp2::MyServicePrioParentAsyncProcessor(iface),
      iface_(iface) {}

  virtual ~MyServicePrioChildAsyncProcessor() {}
};

} // cpp2
