from cgi import parse_qs
from cgi import escape
import logging

'''
wsgiref是python内置的wsgi服务器参考实现
environ
    包含所有HTTP请求信息的dict对象
start_response
    发送HTTP响应的函数
    param1: http resp code
    param2: list of http header (tuple)
    return: http body
'''

def hello_world(environ, start_response):
    parameters = parse_qs(environ.get('QUERY_STRING', ''))

    if 'subject' in parameters:
        subject = escape(parameters['subject'][0])
    else:
        subject = 'World.'

    start_response('200 OK', [('Context-Type', 'text/html')])
    return ['''Hello %(subject)s
    Hello %(subject)s!''' %{'subject': subject}]


if __name__ == '__main__':
    from wsgiref.simple_server import make_server
    IP = 'localhost'
    port = 8080
    server = make_server(IP, port, hello_world)
    logging.basicConfig(level=logging.INFO)
    LOG = logging.getLogger('wsgi')
    LOG.info('listening on %s: %d'%(IP, port))
    server.serve_forever()


