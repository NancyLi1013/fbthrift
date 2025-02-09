/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

package test.fixtures.sink;

import java.util.*;

public class SinkServiceBlockingReactiveWrapper 
    implements SinkService.Reactive {
    private final SinkService _delegate;

    public SinkServiceBlockingReactiveWrapper(SinkService _delegate) {
        
        this._delegate = _delegate;
    }

    @java.lang.Override
    public void dispose() {
        _delegate.close();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<test.fixtures.sink.FinalResponse> method( org.reactivestreams.Publisher<test.fixtures.sink.SinkPayload> payloads) {
        throw new UnsupportedOperationException();
    }

    @java.lang.Override
    public reactor.core.publisher.Flux<com.facebook.thrift.model.StreamResponse<test.fixtures.sink.InitialResponse,test.fixtures.sink.FinalResponse>> methodAndReponse( org.reactivestreams.Publisher<test.fixtures.sink.SinkPayload> payloads) {
        throw new UnsupportedOperationException();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<test.fixtures.sink.FinalResponse> methodThrow( org.reactivestreams.Publisher<test.fixtures.sink.SinkPayload> payloads) {
        throw new UnsupportedOperationException();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<test.fixtures.sink.FinalResponse> methodSinkThrow( org.reactivestreams.Publisher<test.fixtures.sink.SinkPayload> payloads) {
        throw new UnsupportedOperationException();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<test.fixtures.sink.FinalResponse> methodFinalThrow( org.reactivestreams.Publisher<test.fixtures.sink.SinkPayload> payloads) {
        throw new UnsupportedOperationException();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<test.fixtures.sink.FinalResponse> methodBothThrow( org.reactivestreams.Publisher<test.fixtures.sink.SinkPayload> payloads) {
        throw new UnsupportedOperationException();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<test.fixtures.sink.FinalResponse> methodFast( org.reactivestreams.Publisher<test.fixtures.sink.SinkPayload> payloads) {
        throw new UnsupportedOperationException();
    }

}
