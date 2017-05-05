import oslo_messaging as messaging
from oslo_context import context
from oslo_config import cfg
from oslo_log import log as logging

CONF = cfg.CONF
LOG = logging.getLogger(__name__)
logging.register_options(CONF)
logging.setup(CONF, "myservice")
CONF(default_config_files=['app.conf'])

ctxt = {}
arg = {'a':'b'}

transport = messaging.get_transport(cfg.CONF)
target = messaging.Target(topic='test123')
client = messaging.RPCClient(transport, target)
client.call(ctxt, 'test', arg=arg)

