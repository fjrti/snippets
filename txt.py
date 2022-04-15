#!/usr/bin/env python
# -*- coding: utf8 -*-
import argparse
import sys
def main():
    parser = argparse.ArgumentParser(description="something")
    parser.add_argument("--somearg", help="some help",default="val")
    args = parser.parse_args()
    while True:
        line = sys.stdin.readline()
        if not line:
            break
        #do work here
    return 0
if __name__ == '__main__':
  try: sys.exit(main())
  except KeyboardInterrupt: pass
