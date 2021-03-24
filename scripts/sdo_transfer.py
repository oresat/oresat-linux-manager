#!/usr/bin/env python3
"""SDO transfer script"""

import sys
import argparse
from struct import pack, unpack
from enum import Enum, auto
import canopen


EDS_FILE = "../src/boards/generic/object_dictionary/generic_OD.eds"


class CANopenTypes(Enum):
    """All valid canopen types supported"""
    b = auto()
    i8 = auto()
    u8 = auto()
    i16 = auto()
    u16 = auto()
    i32 = auto()
    u32 = auto()
    i64 = auto()
    u64 = auto()
    f32 = auto()
    f64 = auto()
    s = auto()
    d = auto()


parser = argparse.ArgumentParser(description='Read or write value to a node\'s \
        object dictionary.')
parser.add_argument('bus', help='CAN bus to use')
parser.add_argument('node', help='device node name in hex')
parser.add_argument('mode', help='read or write')
parser.add_argument('index', help='Object Dictionary index in hex')
parser.add_argument('subindex', help='Object Dictionary subindex in hex')
parser.add_argument('type',  help='data type')
parser.add_argument('value', nargs='?', default=0, help='data to write')
args = parser.parse_args()

# make sure valid type
co_type = CANopenTypes[args.type]

# convert hex str to int
index = int(args.index, 16)
subindex = int(args.subindex, 16)

network = canopen.Network()
node = canopen.RemoteNode(int(args.node, 16), EDS_FILE)
network.add_node(node)
network.connect(bustype="socketcan", channel=args.bus)

if args.mode == "r" or args.mode == "read":
    raw_data = node.sdo.upload(index, subindex)
    network.disconnect()

    if co_type == CANopenTypes.b:
        data = unpack('?', raw_data)
    elif co_type == CANopenTypes.i8:
        data = unpack('b', raw_data)
    elif co_type == CANopenTypes.u8:
        data = unpack('B', raw_data)
    elif co_type == CANopenTypes.i16:
        data = unpack('h', raw_data)
    elif co_type == CANopenTypes.u16:
        data = unpack('H', raw_data)
    elif co_type == CANopenTypes.i32:
        data = unpack('i', raw_data)
    elif co_type == CANopenTypes.u32:
        data = unpack('I', raw_data)
    elif co_type == CANopenTypes.i64:
        data = unpack('q', raw_data)
    elif co_type == CANopenTypes.u64:
        data = unpack('Q', raw_data)
    elif co_type == CANopenTypes.f32:
        data = unpack('f', raw_data)
    elif co_type == CANopenTypes.f64:
        data = unpack('d', raw_data)
    elif co_type == CANopenTypes.s:
        data = raw_data.decode("utf-8")
        print(data)
        sys.exit(0)
    elif co_type == CANopenTypes.d:
        print(raw_data)
        sys.exit(0)

    print(data[0])
elif args.mode == "w" or args.mode == "write":
    if co_type == CANopenTypes.b:
        raw_data = pack('?', int(args.value))
    elif co_type == CANopenTypes.i8:
        raw_data = pack('b', int(args.value))
    elif co_type == CANopenTypes.u8:
        raw_data = pack('B', int(args.value))
    elif co_type == CANopenTypes.i16:
        raw_data = pack('h', int(args.value))
    elif co_type == CANopenTypes.u16:
        raw_data = pack('H', int(args.value))
    elif co_type == CANopenTypes.i32:
        raw_data = pack('i', int(args.value))
    elif co_type == CANopenTypes.u32:
        raw_data = pack('I', int(args.value))
    elif co_type == CANopenTypes.i64:
        raw_data = pack('q', int(args.value))
    elif co_type == CANopenTypes.u64:
        raw_data = pack('Q', int(args.value))
    elif co_type == CANopenTypes.f32:
        raw_data = pack('f', float(args.value))
    elif co_type == CANopenTypes.f64:
        raw_data = pack('d', float(args.value))
    elif co_type == CANopenTypes.s:
        raw_data = args.value.encode("utf-8")
    elif co_type == CANopenTypes.d:
        raw_data = args.value

    node.sdo.download(index, subindex, raw_data)
    network.disconnect()
