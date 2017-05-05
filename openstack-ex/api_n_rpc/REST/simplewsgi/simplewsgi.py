from paste import httpserver

def application(environ, start_response):
    start_response('200 OK', [('Content-Type', 'text/html')])
    return '<h1>Hello, web!</h1>'

httpserver.serve(application, host='127.0.0.1', port=8080)
