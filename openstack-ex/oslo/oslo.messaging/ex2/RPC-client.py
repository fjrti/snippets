#coding=utf-8

from oslo_config import cfg
import oslo_messaging as messaging

transport = messaging.get_transport(cfg.CONF)
target = messaging.Target(topic='test')
#在构造RPC-client的target时，需要topic参数，其他可选。
client = messaging.RPCClient(transport, target)
ret = client.call(ctxt = {},
                  method = 'test',
                  arg = 'myarg')

#远程调用时，需要提供一个字典对象来指明调用的上下文，调用方法的名字和传
#递给调用方法的参数(用字典表示)。
cctxt = client.prepare(namespace='control', version='2.0')

#prepare函数用于修改RPC-client对象的Target对象的属性。

cctxt.cast({},'stop')
