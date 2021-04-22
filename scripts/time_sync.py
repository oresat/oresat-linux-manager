#!/usr/bin/env python3
"""Time Sync script"""

from argparse import ArgumentParser
from math import modf
from time import time
import struct
import canopen

parser = ArgumentParser(description="Time sync")
parser.add_argument("bus", help="CAN bus to use")
parser.add_argument("-m", "--mock", action="store_true",
                    help="mock the time sync message")
args = parser.parse_args()

network = canopen.Network()
network.connect(bustype="socketcan", channel=args.bus)

if args.mock:
    ts = time()
    ts_us = int(modf(ts)[0] * 1000000)
    data = struct.pack("=2I", int(ts), ts_us)
    network.send_message(0x4B7, b'\x9F\xD9\x81\x60\xE9\x29\x0A\x00')
else:
    network.sync.start(10)

network.disconnect()
