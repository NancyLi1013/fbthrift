/**
 * Autogenerated by Thrift for src/empty.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "thrift/compiler/test/fixtures/py3/gen-cpp2/NullService.h"
#include "thrift/compiler/test/fixtures/py3/gen-cpp2/NullService.tcc"
#include "thrift/compiler/test/fixtures/py3/gen-cpp2/empty_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace cpp2 {
std::unique_ptr<apache::thrift::AsyncProcessor> NullServiceSvIf::getProcessor() {
  return std::make_unique<NullServiceAsyncProcessor>(this);
}




const char* NullServiceAsyncProcessor::getServiceName() {
  return "NullService";
}

void NullServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<NullServiceSvIf>::gen(*response.metadata_ref(), *response.context_ref());
}

void NullServiceAsyncProcessor::processSerializedCompressedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

const NullServiceAsyncProcessor::ProcessMap& NullServiceAsyncProcessor::getOwnProcessMap() {
  return kOwnProcessMap_;
}

const NullServiceAsyncProcessor::ProcessMap NullServiceAsyncProcessor::kOwnProcessMap_ {};

} // cpp2
