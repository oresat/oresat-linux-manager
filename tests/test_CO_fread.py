"""Test OLM CO fread ODF"""

from os.path import isfile
import pytest
from canopen import SdoAbortedError
from common import connect_bus, FREAD_CACHE_DIR, FREAD_TMP_DIR, FREAD_FILE, \
        FREAD_FILE2, FREAD_FILE3

FREAD_INDEX = 0x3003
NAME_SUBINDEX = 1
DATA_SUBINDEX = 2
RESET_SUBINDEX = 3
DELETE_SUBINDEX = 4


def test_fread_name():
    """Test the fread filename subindex (DOMAIN, readwrite)."""
    network, node = connect_bus()
    subindex = node.sdo[FREAD_INDEX][NAME_SUBINDEX]

    # read no data
    with pytest.raises(SdoAbortedError):
        print(subindex.phys)

    # read and write filename with invalid olm file format
    with pytest.raises(SdoAbortedError):
        subindex.raw = "test.txt".encode("utf-8")

    # readwrite with filename that does not end with '\0'
    subindex.raw = FREAD_FILE2.encode("utf-8")
    assert subindex.raw.decode("utf-8") == (FREAD_FILE2+'\0')

    # read and write filename that ends with '\0'
    read_file_b = FREAD_FILE + '\0'
    subindex.raw = read_file_b.encode("utf-8")
    assert subindex.raw.decode("utf-8") == read_file_b

    # readwrite with filename that does not exist
    with pytest.raises(SdoAbortedError):
        subindex.raw = FREAD_FILE3.encode("utf-8")

    network.disconnect()


def test_fread_data():
    """Test the fread filedata subindex (DOMAIN, readonly)."""
    network, node = connect_bus()
    name_subindex = node.sdo[FREAD_INDEX][NAME_SUBINDEX]
    data_subindex = node.sdo[FREAD_INDEX][DATA_SUBINDEX]

    # readonly
    with pytest.raises(SdoAbortedError):
        data_subindex.raw = "0".encode("utf-8")

    # read a file over CANbus
    name_subindex.raw = FREAD_FILE.encode("utf-8")
    file_data = data_subindex.raw.decode("utf-8")
    with open(FREAD_CACHE_DIR + FREAD_FILE, "r") as fptr:
        assert fptr.read() == file_data

    # read another file over CANbus that require multiple blocks
    name_subindex.raw = FREAD_FILE2.encode("utf-8")
    file2_data = data_subindex.raw.decode("utf-8")
    assert isfile(FREAD_CACHE_DIR + FREAD_FILE2)
    with open(FREAD_CACHE_DIR + FREAD_FILE2, "r") as fptr:
        assert fptr.read() == file2_data

    network.disconnect()


def test_fread_reset():
    """Test the reset subindex (DOMAIN, writeonly)"""
    network, node = connect_bus()
    subindex = node.sdo[FREAD_INDEX][RESET_SUBINDEX]

    # writeonly
    with pytest.raises(SdoAbortedError):
        subindex.raw

    # reset deletes file
    fname = FREAD_TMP_DIR + "test.txt"
    with open(fname, "w") as fptr:
        fptr.write("test")
    subindex.raw = "0".encode("utf-8")
    assert not isfile(fname)

    # should never fail
    subindex.raw = "0".encode("utf-8")
    subindex.raw = "0".encode("utf-8")
    subindex.raw = "0".encode("utf-8")

    # reset clear name
    node.sdo[FREAD_INDEX][NAME_SUBINDEX].raw = FREAD_FILE.encode("utf-8")
    subindex.raw = "0".encode("utf-8")
    with pytest.raises(SdoAbortedError):
        node.sdo[FREAD_INDEX][NAME_SUBINDEX].raw

    network.disconnect()


def test_fread_delete():
    """Test the delete file subindex (DOMAIN, writeonly)"""
    network, node = connect_bus()
    subindex = node.sdo[FREAD_INDEX][DELETE_SUBINDEX]

    # writeonly
    with pytest.raises(SdoAbortedError):
        subindex.raw

    # delete file
    node.sdo[FREAD_INDEX][NAME_SUBINDEX].raw = FREAD_FILE.encode("utf-8")
    subindex.raw = "0".encode("utf-8")
    assert not isfile(FREAD_CACHE_DIR + FREAD_FILE)

    # delete another file
    node.sdo[FREAD_INDEX][NAME_SUBINDEX].raw = FREAD_FILE2.encode("utf-8")
    subindex.raw = "0".encode("utf-8")
    assert not isfile(FREAD_CACHE_DIR + FREAD_FILE2)

    network.disconnect()
