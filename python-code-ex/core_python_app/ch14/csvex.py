#!/usr/bin/env python

from __future__ import print_function
import csv

FILE = 'bookdata.csv'
DATA = (
    (9, 'Web Clients and Servers', 'base64, urllib'),
    (10, 'Web Programming: CGI & WSGI', 'cgi, time, wsgiref'),
    (13, 'Web Services', 'urllib, twython'),
)

print('*** WRITING CSV DATA ***')
with open(FILE, 'w') as f:
    writer = csv.writer(f)
    for record in DATA:
         writer.writerow(record)
         print(record)

print('\n*** PRETTY-PRINTED CSV')
with open(FILE, 'r') as f:
    for chap, title, modpkgs in csv.reader(f):
         print('Chapter %s: %r (featuring %s)' % (
             chap, title, modpkgs))
