#!/usr/bin/env python

import argparse, sys
import re

parser = argparse.ArgumentParser()
parser.add_argument('filename', nargs='?')
args = parser.parse_args()
if args.filename:
    f = open(args.filename)
elif not sys.stdin.isatty():
    f = sys.stdin
else:
    parser.print_help()

# string

#skip first line
line = f.readline()

regex = re.compile(r'\s+')

in_pub = 0
out_pub = 0
in_pri = 0
out_pri = 0

while line:
    if re.search('stat', line):
        in_pub += int(regex.split(line)[4].strip())
        out_pub += int(regex.split(line)[5].strip())
        in_pri += int(regex.split(line)[6].strip())
        out_pri += int(regex.split(line)[7].strip())
    line = f.readline()

print "inpub: %s, outpub: %s, inpri: %s, outpri: %s" % (in_pub, out_pub, in_pri, out_pri)
