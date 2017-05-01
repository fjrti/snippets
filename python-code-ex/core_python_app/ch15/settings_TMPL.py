#!/usr/bin/env python
# http://oscon.com/oscon2012/public/schedule/detail/24416

# settings.py (by Wesley Chun under Apache2 license)
# http://www.apache.org/licenses/LICENSE-2.0.html

# - confidential info for your app
# - all values below are strings
# - in a real app, these should be encrypted
# - in a real app, these should NOT be hardcoded in source
#   (use a database, credential server/proxy, etc.)

# Twitter
# 1. go to http://dev.twitter.com/apps to create your app
# 2. click/select that app to get the 4 values below on the resulting page
# 3. these values come in pairs and should be assigned as strings below
CONSUMER_KEY = xxx
CONSUMER_SECRET	 = xxx
ACCESS_TOKEN = xxx
ACCESS_TOKEN_SECRET = xxx

# Google+
# 1. go to http://code.google.com/apis/console to create your app/project
# 2. enable the Google+ API on the "Services" tab
# 3. go to your app's "API Access" tab and get the API_KEY at the bottom
# 4. in the middle of the same tab, create a client to get its ID & secret
#    (put those values in CLIENT_ID & CLIENT_SECRET respectively)
# 5. use an appropriate HTTP client USER_AGENT (we used the one below)
# 6. AUTH_FILE = local file(name) to cache OAuth2 token
#    (else reauthorize every time you run your app)
# 7. SCOPE needs to include at least the Google+
#    (you can add others [space-delimited])
API_KEY = xxx
CLIENT_ID = xxx
CLIENT_SECRET = xxx
USER_AGENT = 'Python-urllib/2.7'
AUTH_FILE = xxx
SCOPE = 'https://www.googleapis.com/auth/plus.me'

# - after filling out all the fields, rename to 'settings.py'
