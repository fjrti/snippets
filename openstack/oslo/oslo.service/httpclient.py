# -*- coding: utf-8 -*-
import uuid
import socket
import functools
import requests
from oslo_config import cfg
from oslo_log import log as logging
from oslo_serialization import jsonutils

client_opts = [
    cfg.BoolOpt('debug',
                default=False,
                help="Print log in every request"),
]

CONF = cfg.CONF
CONF.register_opts(client_opts)
LOG = logging.getLogger(__name__)

class HttpClient(object):
    def __init__(self, cert=None, timeout=None, session=None):
        self.cert = cert
        self.timeout = None
        if not session:
            session = requests.Session()
            # Use TCPKeepAliveAdapter to fix bug 1323862
            for scheme in list(session.adapters):
                session.mount(scheme, TCPKeepAliveAdapter())
        self.session = session

    def request(self, url, method, json=None, connect_retries=0, **kwargs):
        #设置Http头，一般用于存储认证信息和格式信息
        headers = kwargs.setdefault('headers', dict())

        if self.cert:
            kwargs.setdefault('cert', self.cert)

        if self.timeout is not None:
            kwargs.setdefault('timeout', self.timeout)

        user_agent = headers.setdefault('User-Agent', uuid.uuid4().hex)

        if json is not None:
            headers['Content-Type'] = 'application/json'
            kwargs['data'] = jsonutils.dumps(json)

        #设置重试
        send = functools.partial(self._send_request, url, method, connect_retries)

        #获取response
        resp = send(**kwargs)
        return resp

    def _send_request(self, url, method, connect_retries, connect_retry_delay=0.5, **kwargs):
        try:
            if CONF.debug:
                LOG.debug("REQ:{url:%s, method:%s}" % (url, method))
            resp = self.session.request(method, url, **kwargs)
        except (requests.exceptions.Timeout, requests.exceptions.ConnectionError) as e:
            if connect_retries <= 0:
                raise

            time.sleep(connect_retry_delay)

            return self._send_request(
                url, method, connect_retries=connect_retries - 1,
                connect_retry_delay=connect_retry_delay * 2,
                **kwargs)
        if CONF.debug:
            LOG.debug("RESP:{url:%s, method:%s, status:%s}" % (url, method, resp.status_code))
        return resp

    def head(self, url, **kwargs):
        return self.request(url, 'HEAD', **kwargs)

    def get(self, url, **kwargs):
        return self.request(url, 'GET', **kwargs)

    def post(self, url, **kwargs):
        return self.request(url, 'POST', **kwargs)

    def put(self, url, **kwargs):
        return self.request(url, 'PUT', **kwargs)

    def delete(self, url, **kwargs):
        return self.request(url, 'DELETE', **kwargs)

    def patch(self, url, **kwargs):
        return self.request(url, 'PATCH', **kwargs)


#用于解决TCP Keep-Alive的补丁
class TCPKeepAliveAdapter(requests.adapters.HTTPAdapter):
    def init_poolmanager(self, *args, **kwargs):
        if 'socket_options' not in kwargs:
            socket_options = [
                # Keep Nagle's algorithm off
                (socket.IPPROTO_TCP, socket.TCP_NODELAY, 1),
                # Turn on TCP Keep-Alive
                (socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1),
            ]
            if hasattr(socket, 'TCP_KEEPIDLE'):
                socket_options += [
                    # Wait 60 seconds before sending keep-alive probes
                    (socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, 60)
                ]

            if hasattr(socket, 'TCP_KEEPCNT'):
                socket_options += [
                    # Set the maximum number of keep-alive probes
                    (socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 4)
                ]

            if hasattr(socket, 'TCP_KEEPINTVL'):
                socket_options += [
                    # Send keep-alive probes every 15 seconds
                    (socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 15)
                ]

            kwargs['socket_options'] = socket_options
        super(TCPKeepAliveAdapter, self).init_poolmanager(*args, **kwargs)

httpclient = HttpClient()
print httpclient.request("http://localhost:8001/test", "POST", "{'a':'b'}")

