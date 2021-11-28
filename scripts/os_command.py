#!/usr/bin/env python3
"""OS command script"""

from time import sleep
from argparse import ArgumentParser
import canopen


EDS_FILE = "../src/boards/generic/object_dictionary/generic.eds"
OS_COMMAND_INDEX = 0x1023

parser = ArgumentParser(description="Send bash command over CAN bus")
parser.add_argument("bus", help="CAN bus to use")
parser.add_argument("node", help="device node name in hex")
parser.add_argument("command", nargs="?", help="bash command to run, must in \
inside of \"\"")
args = parser.parse_args()

network = canopen.Network()
node = canopen.RemoteNode(int(args.node, 16), EDS_FILE)
network.add_node(node)
network.connect(bustype="socketcan", channel=args.bus)

node.sdo[OS_COMMAND_INDEX][1].raw = args.command.encode("utf-8")

while node.sdo[OS_COMMAND_INDEX][2].phys == 0xFF:
    sleep(0.1)

print("status: " + str(node.sdo[OS_COMMAND_INDEX][2].phys))
print("reply:\n\n" + node.sdo[OS_COMMAND_INDEX][3].raw.decode("utf-8"))

network.disconnect()
