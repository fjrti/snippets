from wsgiref.simple_server import make_server
from webob import Request, Response
from webob.dec import *
from routes import Mapper, middleware

'''
webob提供了包装后的WSGI请求（Request）环境，并辅助创建WSGI响应（Response）
routes：是一个管理URL（路由）的模块

'''

class Test(object):
    def index(self):
        return "do index()\n"
    def add(self):
        return "do show()\n"

class Router(object):
    def __init__(self):
        print '__init__'
        self.controller = Test()
        mapper = Mapper()
        mapper.connect('blog', '/blog/{action}/{id}', controller=Test,conditions={'method': ['GET']})
        mapper.redirect('/', '/blog/index/1')
        self.router = middleware.RoutesMiddleware(self.dispatch, mapper)

    @wsgify
    def dispatch(self, req):
        match = req.environ['wsgiorg.routing_args'][1]
        print req.environ['wsgiorg.routing_args']
        if not match:
            return 'error url: %s' % req.environ['PATH_INFO']
        action = match['action']
        if hasattr(self.controller, action):
            func = getattr(self.controller, action)
            ret = func()
            return ret
        else:
            return "has no action:%s" % action

    @wsgify
    def __call__(self,req):
        print '__call__'
        return self.router

if __name__ == '__main__':
    httpd = make_server('127.0.0.1', 8080, Router())
    print "listening on 8080..."
    httpd.serve_forever()


