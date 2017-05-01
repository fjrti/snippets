from oslo_config import cfg
import oslo_messaging
from oslo_log import log as logging
import time

CONF = cfg.CONF
LOG = logging.getLogger(__name__)
logging.register_options(CONF)
logging.setup(CONF, "myservice")
CONF(default_config_files=['app.conf'])

class ServerControlEndpoint(object):
    target = oslo_messaging.Target(namespace='control',
                                   version='2.0')

    def __init__(self, server):
        self.server = server

    def stop(self, ctx):
        if self.server:
            self.server.stop()

class TestEndpoint(object):
    def test(self, ctx, arg):
        print "test"
        print arg
        return arg

transport = oslo_messaging.get_transport(cfg.CONF)
target = oslo_messaging.Target(topic='test123', server='server1')
endpoints = [
    ServerControlEndpoint(None),
    TestEndpoint(),
]
server = oslo_messaging.get_rpc_server(transport, target, endpoints,
                                       executor='blocking')
try:
    server.start()
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print("Stopping server")

server.stop()
server.wait()



