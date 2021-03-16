"""Test OLM fstream ODFs"""

from os.path import isfile
import pytest
from canopen import SdoAbortedError
from test_helpers import connect_bus, FREAD_CACHE_DIR, FWRTIE_CACHE_DIR, \
        FREAD_TMP_DIR, FWRITE_TMP_DIR

def test_fwrite_reset():
    network, node = connect_bus()

    fname = FWRITE_TMP_DIR + "test.txt"
    with open(fname, "w") as fptr:
        fptr.write("test")

    node.sdo[0x3003][3].raw = "0".encode("utf-8")

    assert not isfile(fname)

    # should never fail
    node.sdo[0x3003][3].raw = "0".encode("utf-8")
    node.sdo[0x3003][3].raw = "0".encode("utf-8")
    node.sdo[0x3003][3].raw = "0".encode("utf-8")

    network.disconnect()


def test_fwrite_name():
    """test if a file write works"""
    network, node = connect_bus()

    node.sdo[0x3003][3].raw = "0".encode("utf-8")

    # read no data
    with pytest.raises(SdoAbortedError):
        print(node.sdo[0x3003][1].phys)

    # readwrite
    new_file = "test.txt\0"
    node.sdo[0x3003][1].raw = new_file.encode("utf-8")
    temp = node.sdo[0x3003][1].raw.decode("utf-8")
    assert temp == new_file

    network.disconnect()
