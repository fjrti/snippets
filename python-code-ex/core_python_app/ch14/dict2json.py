#!/usr/bin/env python

from __future__ import print_function
from json import dumps

BOOKs = {
    '0132269937': {
        'title': 'Core Python Programming',
        'edition': 2,
        'year': 2007,
    },
    '0132356139': {
        'title': 'Python Web Development with Django',
        'authors': ['Jeff Forcier', 'Paul Bissex', 'Wesley Chun'],
        'year': 2009,
    },
    '0137143419': {
        'title': 'Python Fundamentals',
        'year': 2009,
    },
}

print('\n*** RAW JSON ***')
print(dumps(BOOKs))

print('\n*** PRETTY_PRINTED JSON ***')
print(dumps(BOOKs, indent=4))
