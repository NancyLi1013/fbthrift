/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

package test.fixtures.adapter;

import java.util.*;

public class ServiceBlockingReactiveWrapper 
    implements Service.Reactive {
    private final Service _delegate;

    public ServiceBlockingReactiveWrapper(Service _delegate) {
        
        this._delegate = _delegate;
    }

    @java.lang.Override
    public void dispose() {
        _delegate.close();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<Integer> func(final String arg1, final test.fixtures.adapter.Foo arg2) {
        return reactor.core.publisher.Mono.fromSupplier(() -> {
                try {
                    return _delegate.func(arg1, arg2);
                } catch (Throwable _e) {
                    throw reactor.core.Exceptions.propagate(_e);
                }
            }).subscribeOn(com.facebook.thrift.util.resources.RpcResources.getOffLoopScheduler());
    }

}
