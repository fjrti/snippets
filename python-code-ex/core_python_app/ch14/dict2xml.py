#!/usr/bin/env python

from __future__ import print_function
from xml.etree import ElementTree as ET
from xml.dom import minidom

BOOKs = {
    '0132269937': {
        'title': 'Core Python Programming',
        'edition': 2,
        'year': 2006,
    },
    '0132356139': {
        'title': 'Python Web Development with Django',
        'authors': 'Jeff Forcier:Paul Bissex:Wesley Chun',
        'year': 2009,
    },
    '0137143419': {
        'title': 'Python Fundamentals',
        'year': 2009,
    },
}

books = ET.Element('books')
for isbn, info in iter(BOOKs.items()):
    book = ET.SubElement(books, 'book')
    info.setdefault('authors', 'Wesley Chun')
    info.setdefault('edition', 1)
    for key, val in iter(info.items()):
        ET.SubElement(book, key).text = ', '.join(str(val).split(':'))

xml = ET.tostring(books)
print('*** RAW XML ***')
print(xml)

print('\n*** PRETTY-PRINTED XML ***')
dom = minidom.parseString(xml)
print(dom.toprettyxml('    '))

print('*** FLAT STRUCTURE ***')
for elmt in books.getiterator():
    print(elmt.tag, '-', elmt.text)

print('\n*** TITLES ONLY ***')
for book in books.findall('.//title'):
    print(book.text)
