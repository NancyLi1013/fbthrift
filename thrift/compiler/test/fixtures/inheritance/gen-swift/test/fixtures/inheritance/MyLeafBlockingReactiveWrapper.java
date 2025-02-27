/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

package test.fixtures.inheritance;

import java.util.*;

public class MyLeafBlockingReactiveWrapper  extends test.fixtures.inheritance.MyNodeBlockingReactiveWrapper
    implements MyLeaf.Reactive {
    private final MyLeaf _delegate;

    public MyLeafBlockingReactiveWrapper(MyLeaf _delegate) {
        super(_delegate);
        this._delegate = _delegate;
    }

    @java.lang.Override
    public void dispose() {
        _delegate.close();
    }

    @java.lang.Override
    public reactor.core.publisher.Mono<Void> doLeaf() {
        return reactor.core.publisher.Mono.<Void>fromRunnable(() -> {
                try {
                    _delegate.doLeaf();
                } catch (Throwable _e) {
                    throw reactor.core.Exceptions.propagate(_e);
                }
            }).subscribeOn(com.facebook.thrift.util.resources.RpcResources.getOffLoopScheduler());
    }

}
