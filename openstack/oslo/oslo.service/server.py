# -*- coding: utf-8 -*-
import sys
from oslo_config import cfg
from oslo_log import log as logging
import miniservice

CONF = cfg.CONF
LOG = logging.getLogger(__name__)

def default_action(env, method, path, query, body):
    LOG.info("demo action (method:%s, path:%s, query:%s, body:%s)"
        % (method, path, query, body))
    return ("200 OK", "default")

def test_action(env, method, path, query, body):
    LOG.info("test (method:%s, path:%s, query:%s, body:%s)"
        % (method, path, query, body))
    return ("200 OK", "test")

if __name__ == "__main__":
    CONF(sys.argv[1:])
    host = getattr(CONF, "host", "0.0.0.0")
    port = getattr(CONF, "port", "8001")
    service = miniservice.MiniService(host, port)
    service.add_action("", default_action)
    service.add_action("test", test_action)
    service.start()

