#!/usr/bin/env python3

import os
import sys
import argparse
import canopen

EDS_FILE = "../src/boards/generic/object_dictionary/generic_OD.eds"

# valid cache selector inputs
FREAD_CACHE = 0
FWRITE_CACHE = 1
FCACHE_INDEX = 0x3002

parser = argparse.ArgumentParser(description='OLM file transfer.')
parser.add_argument('bus', help='CAN bus to use')
parser.add_argument('node', help='device node name in hex')
parser.add_argument('-l', '--list', dest='cache', default=None,
        help='list files in cache, where CACHE can be fread or fwrite')
parser.add_argument('-r', '--read', dest='read_file',
        help='read file from OLM fread cache')
parser.add_argument('-w', '--write', dest='write_file',
        help='write file to OLM')

args = parser.parse_args()
network = canopen.Network()
node = canopen.RemoteNode(int(args.node, 16), EDS_FILE)
network.add_node(node)
network.connect(bustype="socketcan", channel=args.bus)

if args.cache is not None:
    if args.cache == "fread":
        node.sdo[FCACHE_INDEX][3].phys = FREAD_CACHE
    elif args.cache == "fwrite":
        node.sdo[FCACHE_INDEX][3].phys = FWRITE_CACHE
    else:
        print("invalid cache")
        sys.exit(1)

    node.sdo[FCACHE_INDEX][4].raw = b'\00'  # clear filter

    for i in range(node.sdo[FCACHE_INDEX][5].phys):
        node.sdo[FCACHE_INDEX][6].phys = i
        print(node.sdo[FCACHE_INDEX][7].raw.decode("utf-8"))
elif args.read_file is not None:
    node.sdo[0x3003][1].raw = args.read_file.encode("utf-8")
    infile = node.sdo[0x3003][2].open('r', encoding='ascii')
    outfile = open(args.read_file, 'w', encoding='ascii')
    outfile.writelines(infile)

    infile.close()
    outfile.close()
elif args.write_file is not None:
    node.sdo[0x3004][1].raw = args.write_file.encode("utf-8")
    with open(args.write_file, "r") as fptr:
        file_data = fptr.read()
    node.sdo[0x3004][2].raw = file_data.encode("utf-8")
else:
    print("invalid mode")
    sys.exit(1)

network.disconnect()