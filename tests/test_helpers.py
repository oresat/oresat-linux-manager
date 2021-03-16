"""testing candeamon"""

import canopen

# all nodes require an eds file, even if it is not used
EDS_FILE = "../src/boards/generic/object_dictionary/generic_OD.eds"
FREAD_CACHE_DIR = "/var/lib/oresat_linux_manager/fread/"
FWRTIE_CACHE_DIR = "/var/lib/oresat_linux_manager/fwrite/"
FREAD_TMP_DIR = "/tmp/olm_fread/"
FWRITE_TMP_DIR = "/tmp/olm_fwrite/"


def connect_bus():
    """quick function to connect to can bus"""

    network = canopen.Network()
    node = canopen.RemoteNode(0x10, EDS_FILE)
    network.add_node(node)
    network.connect(bustype='socketcan', channel='vcan0')

    return network, node

# network.nmt.state = 'OPERATIONAL'

# temp = node.sdo[0x2101].raw
# print("node {}".format(hex(temp)))

# node.sdo[FWRITE_INDEX][1] = i
# device_type_data = node.sdo.upload(0x1000, 0)
