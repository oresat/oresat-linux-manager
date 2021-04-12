#!/usr/bin/env python3
"""OLM app manager script"""

from enum import Enum
from argparse import ArgumentParser
import canopen

EDS_FILE = "../src/boards/generic/object_dictionary/generic.eds"

APP_MANAGER_INDEX = 0x3005


class States(Enum):
    inactive = 0
    reloading = 1
    active = 2
    failed = 3
    activating = 4
    deactivating = 5
    unknown = 6


class Commands(Enum):
    no_command = 0
    stop = 1
    start = 2
    restart = 3


parser = ArgumentParser(description="OLM app manager")
parser.add_argument("bus", help="CAN bus to use")
parser.add_argument("node", help="device node name in hex")
parser.add_argument("-l", "--list", dest="list", action="store_true",
                    help="list all apps and their status")
parser.add_argument("-w", "--start", dest="start", type=int,
                    help="start the apps daemon")
parser.add_argument("-s", "--stop", dest="stop", type=int,
                    help="stop the apps daemon")
parser.add_argument("-r", "--restart", dest="restart", type=int,
                    help="restart the apps daemon")

args = parser.parse_args()
network = canopen.Network()
node = canopen.RemoteNode(int(args.node, 16), EDS_FILE)
network.add_node(node)
network.connect(bustype="socketcan", channel=args.bus)


if args.list:
    apps = node.sdo[APP_MANAGER_INDEX][1].phys
    if apps == 0:
        print("No apps")
    else:
        print("Apps")
        for i in range(apps):
            node.sdo[APP_MANAGER_INDEX][4].phys = i
            name = node.sdo[APP_MANAGER_INDEX][5].raw.decode("utf-8")
            state = node.sdo[APP_MANAGER_INDEX][6].phys
            print("{}: {} is {}".format(i, name, States(state).name))
elif args.start:
    node.sdo[APP_MANAGER_INDEX][4].phys = args.start
    node.sdo[APP_MANAGER_INDEX][6].phys = Commands.start.value
elif args.stop:
    node.sdo[APP_MANAGER_INDEX][4].phys = args.stop
    node.sdo[APP_MANAGER_INDEX][6].phys = Commands.stop.value
elif args.restart:
    node.sdo[APP_MANAGER_INDEX][4].phys = args.restart
    node.sdo[APP_MANAGER_INDEX][6].phys = Commands.restart.value

network.disconnect()
