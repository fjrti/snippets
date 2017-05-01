#!/usr/bin/env python
# http://oscon.com/oscon2012/public/schedule/detail/24416

# twy_u.py (by Wesley Chun under Apache2 license)
# http://www.apache.org/licenses/LICENSE-2.0.html
from distutils.log import warn as printf
try:
    import twython
except ImportError:
    import twython3k as twython

TMPL = '''
     User: @%(from_user)s
     Date: %(created_at)s
     Tweet: %(text)s'''

printf('\n*** Search for "python" (authorization NOT required)')
twitter = twython.Twython()
data = twitter.search(q='python')
for tweet in data['results']:
     printf(TMPL % tweet)
