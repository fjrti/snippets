#coding=utf-8

from oslo_config import cfg
import oslo_messaging
import time

class ServerControlEndpoint(object):
    target = oslo_messaging.Target(namespace='control',
                                  version='2.0')
    def __init__(self, server):
        self.server = server

    def stop(self, ctx):
        print "------ServerControlEndpoint. stop --------"
        if self.server:
            self.server.stop()

class TestEndpoint(object):
    def test(self, ctx, arg):
        print "------ TestEndpoint.test --------"
        return arg

transport = oslo_messaging.get_transport(cfg.CONF)

#从cfg对象中，读取transport_url,rpc_backend和control_exchange信息构
#造Transport对象，其中rpc_backend和control_exchange的默认值分别为：
#’rabbit’和’openstack’。
target = oslo_messaging.Target(topic='test', server='server1')
#在构造RPC-server的target时，需要topic和server参数，exchange参数可
#选。

endpoints = [
    ServerControlEndpoint(None),
    TestEndpoint(),
]

#一个RPC-server可以暴露多个endpoint，每个endpoint包含一组方法，这组
#方法可以被RPC-client通过某种Transport对象远程调用。

server = oslo_messaging.get_rpc_server(transport, target, endpoints,
                                      executor='blocking')

#构造RPC-server对象，其中executor有两种方式：blocking和eventlet。
#blocking：用户调用start函数后，在start函数中开始请求处理循环，用户线程
#阻塞，处理下一个请求。直到用户调用了stop函数后，这个处理循环才退出。
#消息的接受和分发处理都在调用start函数的线程中完成的。
#eventlet：在这种方式中，会有一个协程GreenThread来处理消息的接收，然后
#有其他不同二屌GreenThread来处理不同消息的分发处理。调用start的用户
#线程不会被阻塞。
#在这里我们使用blocking方式。

try:
    server.start()
    while True:
        time.sleep(1)

except KeyboardInterrupt:
   print("Stopping server")

server.stop()
server.wait()
