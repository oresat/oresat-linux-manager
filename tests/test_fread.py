"""testing candeamon"""

import pytest
from ctypes import c_ubyte
from test_helpers import connect_bus

FREAD_LIST_INDEX = 0x3002
FREAD_LIST_INDEX_LEN = 128

FREAD_CTRL_INDEX = 0x3003
FREAD_CTRL_SUBINDECIES = 0
FREAD_CTRL_SI_SELECTOR = 1
FREAD_CTRL_SI_FILENAME = 2
FREAD_CTRL_SI_FILEDATA = 3
FREAD_CTRL_SI_FILESIZE = 4
FREAD_CTRL_SI_DELETE_FILE = 5
FREAD_CTRL_SI_TOTAL_FILES = 6
FREAD_CTRL_SI_OVERFLOW = 7
FREAD_CTRL_SI_REFRESH = 8


def test_fread_list():
    """test if a file write works"""
    network, node = connect_bus()

    for i in range(FREAD_LIST_INDEX_LEN):
        node.sdo.upload(FREAD_LIST_INDEX, i)

    network.disconnect()
    assert True


def test_fread_ctrl_no_files():
    """test if a file write works"""
    network, node = connect_bus()

    subindecies = node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SUBINDECIES)
    assert int.from_bytes(subindecies, byteorder="little", signed=False) == 9

    selector = node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_SELECTOR)
    assert int.from_bytes(selector, byteorder="little", signed=False) == 1

    filename = node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_FILENAME)
    assert filename.decode() == "\0"

    with pytest.raises(Exception):
        node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_FILEDATA)

    size = node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_FILESIZE)
    assert int.from_bytes(size, byteorder="little", signed=False) == 0

    with pytest.raises(Exception):
        node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_DELETE_FILE)

    files = node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_TOTAL_FILES)
    assert int.from_bytes(files, byteorder="little", signed=False) == 0

    overflow = node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_OVERFLOW)
    assert int.from_bytes(overflow, byteorder="little", signed=False) == 0

    with pytest.raises(Exception):
        node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_REFRESH)

    network.disconnect()
    assert True


def test_fread():
    """test if a file write works"""
    network, node = connect_bus()

    # add file
    with open("/var/cache/candaemon/test.txt", "w") as f:
        f.write("read test "*1000 + "\n")

    # refresh after new file
    node.sdo.download(FREAD_CTRL_INDEX, FREAD_CTRL_SI_REFRESH, b"00")

    node.sdo.download(FREAD_CTRL_INDEX, FREAD_CTRL_SI_SELECTOR, bytes(c_ubyte(1)))
    sel = node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_SELECTOR)
    assert int.from_bytes(sel, byteorder="little", signed=False) == 1

    node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_FILENAME)
    node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_FILESIZE)
    node.sdo.upload(FREAD_CTRL_INDEX, FREAD_CTRL_SI_FILEDATA)
    node.sdo.download(FREAD_CTRL_INDEX, FREAD_CTRL_SI_DELETE_FILE, b"00")

    network.disconnect()
    assert True
