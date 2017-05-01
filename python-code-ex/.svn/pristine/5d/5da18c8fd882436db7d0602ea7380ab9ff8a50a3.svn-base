#!/usr/bin/env python

from __future__ import print_function
from contextlib import closing
from time import ctime
try:
    from urllib.request import urlopen
except ImportError:
    from urllib import urlopen

TICKs = ('yhoo', 'csco', 'msft', 'adbe', 'intc')
URL = 'http://quote.yahoo.com/d/quotes.csv?s=%s&f=sl1c1p2'

print('\nPrices quoted as of: %s\n' % ctime())
print('TICKER', 'PRICE', 'CHANGE', '%AGE')
print('------', '-----', '------', '----')
with closing(urlopen(URL % ','.join(TICKs))) as u:
    for row in u:
        tick, price, chg, per = row.decode('utf-8').strip().split(',')
        print(tick, '%.2f' % float(price), chg, per)
