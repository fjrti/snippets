#!/usr/bin/env python

from __future__ import print_function
from unittest import TestCase, main

import settings # customize settings_TMPL.py

# set up supported APIs
CMDs = {
    'twython': {
        'search':               None,
        'verify_credentials':   None,
        'user_timeline':        'get_user_timeline',
        'update_status':        None,
    },
    'tweepy': dict.fromkeys((
        'search',
        'verify_credentials',
        'user_timeline',
        'update_status',
    )),
}
APIs = set(CMDs)

# remove unavailable APIs
remove = set()
for api in APIs:
    try:
        __import__(api)
    except ImportError:
        remove.add(api)

APIs.difference_update(remove)
if not APIs:
    raise NotImplementedError(
        'No Twitter API found; install one & add to CMDs!')

class Twitter(object):
    'Twitter -- Use available APIs to talk to Twitter'
    def __init__(self, api, auth=True):
        if api not in APIs:
            raise NotImplementedError(
                '%r unsupported; try one of: %r' % (api, APIs))

        self.api = api
        if api == 'twython':
            import twython
            if auth:
                self.twitter = twython.Twython(
                    settings.CONSUMER_KEY,
                    settings.CONSUMER_SECRET,
                    settings.ACCESS_TOKEN,
                    settings.ACCESS_TOKEN_SECRET,
                )
            else:
                self.twitter = twython.Twython()
        elif api == 'tweepy':
            import tweepy
            if auth:
                auth = tweepy.OAuthHandler(
                        settings.CONSUMER_KEY,
                        settings.CONSUMER_SECRET)
                auth.set_access_token(
                        settings.ACCESS_TOKEN,
                        settings.ACCESS_TOKEN_SECRET)
                self.twitter = tweepy.API(auth)
            else:
                self.twitter = tweepy.api

    def _get_meth(self, cmd):
        meth_name = CMDs[self.api][cmd] or cmd
        return getattr(self.twitter, meth_name)

    def search(self, q):
        api = self.api
        if api == 'twython':
            res = self._get_meth('search')(q=q)['statuses']
            return (ResultsWrapper(tweet) for tweet in res)
        elif api == 'tweepy':
            return (ResultsWrapper(tweet)
                for tweet in self._get_meth('search')(q=q))

    def verify_credentials(self):
        return ResultsWrapper(
            self._get_meth('verify_credentials')())

    def user_timeline(self):
        return (ResultsWrapper(tweet)
            for tweet in self._get_meth('user_timeline')())

    def update_status(self, s):
        return ResultsWrapper(
            self._get_meth('update_status')(status=s))

class ResultsWrapper(object):
    "ResultsWrapper -- makes foo.bar the same as foo['bar']"
    def __init__(self, obj):
        self.obj = obj

    def __str__(self):
        return str(self.obj)

    def __repr__(self):
        return repr(self.obj)

    def __getattr__(self, attr):
        if hasattr(self.obj, attr):
            return getattr(self.obj, attr)
        elif hasattr(self.obj, '__contains__') and attr in self.obj:
            return self.obj[attr]
        else:
            raise AttributeError(
                '%r has no attribute %r' % (self.obj, attr))

    __getitem__ = __getattr__

def _demo_search():
    for api in APIs:
        print(api.upper())
        t = Twitter(api)
        tweets = t.search('core python')
        for tweet in tweets:
            print('----' * 10)
            print('@%s' % ResultsWrapper(tweet.user).screen_name)
            print('Status: %s' % tweet.text)
            print('Posted at: %s' % tweet.created_at)
        print('----' * 10)

def _demo_ver_creds():
    for api in APIs:
        t = Twitter(api)
        res = t.verify_credentials()
        status = ResultsWrapper(res.status)
        print('@%s' % res.screen_name)
        print('Status: %s' % status.text)
        print('Posted at: %s' % status.created_at)
        print('----' * 10)

def _demo_user_timeline():
    for api in APIs:
        print(api.upper())
        t = Twitter(api)
        tweets = t.user_timeline()
        for tweet in tweets:
            print('----' * 10)
            print('Status: %s' % tweet.text)
            print('Posted at: %s' % tweet.created_at)
        print('----' * 10)

def _demo_update_status():
    for api in APIs:
        t = Twitter(api)
        res = t.update_status(
            'Test tweet posted to Twitter using %s' % api.title())
        print('Posted at: %s' % res.created_at)
        print('----' * 10)

# object wrapper unit tests
def _unit_dict_wrap():
    d = {'foo': 'bar'}
    wrapped = ResultsWrapper(d)
    return wrapped['foo'], wrapped.foo

def _unit_attr_wrap():
    class C(object):
        foo = 'bar'
    wrapped = ResultsWrapper(C)
    return wrapped['foo'], wrapped.foo

class TestSequenceFunctions(TestCase):
   def test_dict_wrap(self):
       self.assertEqual(_unit_dict_wrap(), ('bar', 'bar'))

   def test_attr_wrap(self):
       self.assertEqual(_unit_attr_wrap(), ('bar', 'bar'))

if __name__ == '__main__':
    print('\n*** DEMO SEARCH')
    _demo_search()
    print('\n*** DEMO VERIFY CREDENTIALS')
    _demo_ver_creds()
    print('\n*** DEMO USER TIMELINE')
    _demo_user_timeline()
    print('\n*** DEMO UPDATE STATUS')
    _demo_update_status()
    print('\n*** RESULTS_WRAPPER REGRESSION TEST')
    main()
