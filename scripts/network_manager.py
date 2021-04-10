#!/usr/bin/env python3
"""CANopen Network Manager script"""

import argparse
import canopen

EDS_FILE = "../src/boards/generic/object_dictionary/generic.eds"

states = [
    'INITIALISING',
    'PRE-OPERATIONAL',
    'STOPPED',
    'OPERATIONAL',
    'SLEEP',
    'STANDBY',
    'RESET',
    'RESET COMMUNICATION',
    ]

parser = argparse.ArgumentParser(description='Read or write value to a node\'s \
        object dictionary.')
parser.add_argument('bus', help='CAN bus to use')
parser.add_argument('node', help='device node name in hex')
parser.add_argument('state', help='new state, values can be: ' + ', '.join(states)) 
args = parser.parse_args()

network = canopen.Network()
node = canopen.RemoteNode(int(args.node, 16), EDS_FILE)
network.add_node(node)
network.connect(bustype="socketcan", channel=args.bus)

node.nmt.state = args.state

network.disconnect()
