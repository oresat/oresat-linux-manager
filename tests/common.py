"""Common OLM pytest scripts"""

import canopen

# python canopen require an eds file, even if it is not used
EDS_FILE = "../src/boards/generic/object_dictionary/generic_OD.eds"

FILE_TRANSFER_DIR = "/var/cache/oresat_linux_manager/"
FREAD_CACHE_DIR = FILE_TRANSFER_DIR + "fread/"
FWRITE_CACHE_DIR = FILE_TRANSFER_DIR + "fwrite/"
FREAD_TMP_DIR = FILE_TRANSFER_DIR + "CANopen/fread/"
FWRITE_TMP_DIR = FILE_TRANSFER_DIR + "CANopen/fwrite/"

# require files for CO fread tests
FREAD_FILE = "test_read_123.txt"
FREAD_FILE2 = "test_read_456.txt"

# file must not exist in fread cache
FREAD_FILE3 = "test_read_789.txt"

# require files for file caches tests
FCACHES_FREAD_VALID_FILES = [
    "test_foo_123.txt",
    "test_foo_123",
    "test_bar_123.txt",
    "test_bar_456.txt",
    ]
FCACHES_FREAD_INVALID_FILES = [
    "test.txt",
    "test_baz.txt",
    "_baz_.txt",
    "_baz_",
    "test_123.txt",
    ]
FCACHES_FREAD_EMPTY_FILE = "test_foo_456"


def connect_bus():
    """quick function to connect to can bus"""

    network = canopen.Network()
    node = canopen.RemoteNode(0x10, EDS_FILE)
    network.add_node(node)
    network.connect(bustype="socketcan", channel="vcan0")
    # network.nmt.state = "OPERATIONAL"

    return network, node
