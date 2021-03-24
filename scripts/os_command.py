#!/usr/bin/env python3
"""SDO transfer script"""

import sys
from time import sleep
import argparse
import canopen


EDS_FILE = "../src/boards/generic/object_dictionary/generic_OD.eds"
OS_COMMAND_INDEX = 0x1023
COMMAND_SUBINDEX = 1
STATUS_SUBINDEX = 2
REPLY_SUBINDEX = 3

parser = argparse.ArgumentParser(description='Read or write value to a node\'s \
        object dictionary.')
parser.add_argument('bus', help='CAN bus to use')
parser.add_argument('node', help='device node name in hex')
parser.add_argument('command', nargs='?', help='bash command to run, must in inside of \"\"')
args = parser.parse_args()

network = canopen.Network()
node = canopen.RemoteNode(int(args.node, 16), EDS_FILE)
network.add_node(node)
network.connect(bustype="socketcan", channel=args.bus)

node.sdo[OS_COMMAND_INDEX][COMMAND_SUBINDEX].raw = args.command.encode("utf-8")

while node.sdo[OS_COMMAND_INDEX][STATUS_SUBINDEX].phys == 0xFF:
    sleep(0.1)

print("status: " + str(node.sdo[OS_COMMAND_INDEX][STATUS_SUBINDEX].phys))
print("reply: " + node.sdo[OS_COMMAND_INDEX][REPLY_SUBINDEX].raw.decode("utf-8"))

network.disconnect()
