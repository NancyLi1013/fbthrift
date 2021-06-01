/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#include "thrift/compiler/test/fixtures/adapter/gen-cpp2/ServiceAsyncClient.h"

#include <thrift/lib/cpp2/gen/client_cpp.h>

namespace cpp2 {
typedef apache::thrift::ThriftPresult<false, apache::thrift::FieldData<1, ::apache::thrift::type_class::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>*>, apache::thrift::FieldData<2, ::apache::thrift::type_class::structure, ::cpp2::Foo*>> Service_func_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, ::apache::thrift::type_class::integral, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>*>> Service_func_presult;

template <typename Protocol_>
void ServiceAsyncClient::funcT(Protocol_* prot, const apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::transport::THeader> header, apache::thrift::ContextStack* contextStack, apache::thrift::RequestClientCallback::Ptr callback, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {

  Service_func_pargs args;
  args.get<0>().value = const_cast<::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>*>(&p_arg1);
  args.get<1>().value = const_cast<::cpp2::Foo*>(&p_arg2);
  auto sizer = [&](Protocol_* p) { return args.serializedSizeZC(p); };
  auto writer = [&](Protocol_* p) { args.write(p); };

  static ::apache::thrift::MethodMetadata::Data* methodMetadata =
        new ::apache::thrift::MethodMetadata::Data(
                "func",
                ::apache::thrift::FunctionQualifier::None);
  apache::thrift::clientSendT<apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, Protocol_>(prot, rpcOptions, std::move(callback), contextStack, std::move(header), channel_.get(), ::apache::thrift::MethodMetadata::from_static(methodMetadata), writer, sizer);

}



void ServiceAsyncClient::func(std::unique_ptr<apache::thrift::RequestCallback> callback, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  ::apache::thrift::RpcOptions rpcOptions;
  func(rpcOptions, std::move(callback), p_arg1, p_arg2);
}

void ServiceAsyncClient::func(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  auto [ctx, header] = funcCtx(&rpcOptions);
  apache::thrift::RequestCallback::Context callbackContext;
  callbackContext.protocolId =
      apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  auto* contextStack = ctx.get();
  if (callback) {
    callbackContext.ctx = std::move(ctx);
  }
  auto wrappedCallback = apache::thrift::toRequestClientCallbackPtr(std::move(callback), std::move(callbackContext));
  funcImpl(rpcOptions, std::move(header), contextStack, std::move(wrappedCallback), p_arg1, p_arg2);
}

void ServiceAsyncClient::funcImpl(const apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::transport::THeader> header, apache::thrift::ContextStack* contextStack, apache::thrift::RequestClientCallback::Ptr callback, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  switch (apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolWriter writer;
      funcT(&writer, rpcOptions, std::move(header), contextStack, std::move(callback), p_arg1, p_arg2);
      break;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolWriter writer;
      funcT(&writer, rpcOptions, std::move(header), contextStack, std::move(callback), p_arg1, p_arg2);
      break;
    }
    default:
    {
      apache::thrift::detail::ac::throw_app_exn("Could not find Protocol");
    }
  }
}

std::pair<std::unique_ptr<::apache::thrift::ContextStack>, std::shared_ptr<::apache::thrift::transport::THeader>> ServiceAsyncClient::funcCtx(apache::thrift::RpcOptions* rpcOptions) {
  auto header = std::make_shared<apache::thrift::transport::THeader>(
      apache::thrift::transport::THeader::ALLOW_BIG_FRAMES);
  header->setProtocolId(channel_->getProtocolId());
  if (rpcOptions) {
    header->setHeaders(rpcOptions->releaseWriteHeaders());
  }

  auto ctx = apache::thrift::ContextStack::createWithClientContext(
      handlers_,
      getServiceName(),
      "Service.func",
      *header);

  return {std::move(ctx), std::move(header)};
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> ServiceAsyncClient::sync_func(const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  ::apache::thrift::RpcOptions rpcOptions;
  return sync_func(rpcOptions, p_arg1, p_arg2);
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> ServiceAsyncClient::sync_func(apache::thrift::RpcOptions& rpcOptions, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  apache::thrift::ClientReceiveState returnState;
  apache::thrift::ClientSyncCallback<false> callback(&returnState);
  auto protocolId = apache::thrift::GeneratedAsyncClient::getChannel()->getProtocolId();
  auto evb = apache::thrift::GeneratedAsyncClient::getChannel()->getEventBase();
  auto [ctx, header] = funcCtx(&rpcOptions);
  auto wrappedCallback = apache::thrift::RequestClientCallback::Ptr(&callback);
  funcImpl(rpcOptions, std::move(header), ctx.get(), std::move(wrappedCallback), p_arg1, p_arg2);
  callback.waitUntilDone(evb);

  if (returnState.isException()) {
    returnState.exception().throw_exception();
  }
  returnState.resetProtocolId(protocolId);
  returnState.resetCtx(std::move(ctx));
  SCOPE_EXIT {
    if (returnState.header() && !returnState.header()->getHeaders().empty()) {
      rpcOptions.setReadHeaders(returnState.header()->releaseHeaders());
    }
  };
  return folly::fibers::runInMainContext([&] {
      return recv_func(returnState);
  });
}


folly::Future<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>> ServiceAsyncClient::future_func(const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  ::apache::thrift::RpcOptions rpcOptions;
  return future_func(rpcOptions, p_arg1, p_arg2);
}

folly::SemiFuture<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>> ServiceAsyncClient::semifuture_func(const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  ::apache::thrift::RpcOptions rpcOptions;
  return semifuture_func(rpcOptions, p_arg1, p_arg2);
}

folly::Future<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>> ServiceAsyncClient::future_func(apache::thrift::RpcOptions& rpcOptions, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  folly::Promise<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::FutureCallback<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>>(std::move(promise), recv_wrapped_func, channel_);
  func(rpcOptions, std::move(callback), p_arg1, p_arg2);
  return future;
}

folly::SemiFuture<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>> ServiceAsyncClient::semifuture_func(apache::thrift::RpcOptions& rpcOptions, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  auto callbackAndFuture = makeSemiFutureCallback(recv_wrapped_func, channel_);
  auto callback = std::move(callbackAndFuture.first);
  func(rpcOptions, std::move(callback), p_arg1, p_arg2);
  return std::move(callbackAndFuture.second);
}

folly::Future<std::pair<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>, std::unique_ptr<apache::thrift::transport::THeader>>> ServiceAsyncClient::header_future_func(apache::thrift::RpcOptions& rpcOptions, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  folly::Promise<std::pair<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>, std::unique_ptr<apache::thrift::transport::THeader>>> promise;
  auto future = promise.getFuture();
  auto callback = std::make_unique<apache::thrift::HeaderFutureCallback<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>>(std::move(promise), recv_wrapped_func, channel_);
  func(rpcOptions, std::move(callback), p_arg1, p_arg2);
  return future;
}

folly::SemiFuture<std::pair<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>, std::unique_ptr<apache::thrift::transport::THeader>>> ServiceAsyncClient::header_semifuture_func(apache::thrift::RpcOptions& rpcOptions, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  auto callbackAndFuture = makeHeaderSemiFutureCallback(recv_wrapped_func, channel_);
  auto callback = std::move(callbackAndFuture.first);
  func(rpcOptions, std::move(callback), p_arg1, p_arg2);
  return std::move(callbackAndFuture.second);
}

void ServiceAsyncClient::func(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback, const ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::string>& p_arg1, const ::cpp2::Foo& p_arg2) {
  func(std::make_unique<apache::thrift::FunctionReplyCallback>(std::move(callback)), p_arg1, p_arg2);
}

#if FOLLY_HAS_COROUTINES
#endif // FOLLY_HAS_COROUTINES
folly::exception_wrapper ServiceAsyncClient::recv_wrapped_func(::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>& _return, ::apache::thrift::ClientReceiveState& state) {
  if (state.isException()) {
    return std::move(state.exception());
  }
  if (!state.hasResponseBuffer()) {
    return folly::make_exception_wrapper<apache::thrift::TApplicationException>("recv_ called without result");
  }

  using result = Service_func_presult;
  switch (state.protocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          &reader, state, _return);
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          &reader, state, _return);
    }
    default:
    {
    }
  }
  return folly::make_exception_wrapper<apache::thrift::TApplicationException>("Could not find Protocol");
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> ServiceAsyncClient::recv_func(::apache::thrift::ClientReceiveState& state) {
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> _return;
  auto ew = recv_wrapped_func(_return, state);
  if (ew) {
    ew.throw_exception();
  }
  return _return;
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> ServiceAsyncClient::recv_instance_func(::apache::thrift::ClientReceiveState& state) {
  return recv_func(state);
}

folly::exception_wrapper ServiceAsyncClient::recv_instance_wrapped_func(::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_wrapped_func(_return, state);
}


} // cpp2
