"""Test OLM CO fwrite ODF"""

from os.path import isfile
import pytest
from canopen import SdoAbortedError
from common import connect_bus, FWRITE_CACHE_DIR, FWRITE_TMP_DIR, \
        random_string_generator

FWRITE_INDEX = 0x3004
NAME_SUBINDEX = 1
DATA_SUBINDEX = 2
RESET_SUBINDEX = 3


def test_fwrite_name():
    """Test if the fwrite filename subindex (DOMAIN, readwrite)."""
    network, node = connect_bus()
    subindex = node.sdo[FWRITE_INDEX][NAME_SUBINDEX]

    # read no data
    with pytest.raises(SdoAbortedError):
        subindex.phys

    # read and write filename with invalid olm file format
    with pytest.raises(SdoAbortedError):
        subindex.raw = "test.txt".encode("utf-8")

    # readwrite with filename that does not end with '\0'
    new_file = "test_write_123.txt"
    node.sdo[FWRITE_INDEX][NAME_SUBINDEX].raw = new_file.encode("utf-8")
    assert subindex.raw.decode("utf-8") == (new_file+'\0')

    # read and write filename that ends with '\0'
    new_file = "test_write_123.txt\0"
    subindex.raw = new_file.encode("utf-8")
    assert subindex.raw.decode("utf-8") == new_file

    network.disconnect()


def test_fwrite_data():
    """Test if the fwrite filedata subindex (DOMAIN, writeonly)."""
    network, node = connect_bus()
    name_subindex = node.sdo[FWRITE_INDEX][NAME_SUBINDEX]
    data_subindex = node.sdo[FWRITE_INDEX][DATA_SUBINDEX]

    with pytest.raises(SdoAbortedError):
        data_subindex.phys

    # write a file over CANbus
    new_file = "test_write_123.txt"
    name_subindex.raw = new_file.encode("utf-8")
    file_data = random_string_generator(10)
    data_subindex.raw = file_data.encode("utf-8")
    assert isfile(FWRITE_CACHE_DIR + new_file)
    with open(FWRITE_CACHE_DIR + new_file, "r") as fptr:
        assert fptr.read() == file_data

    # write another file over CANbus that require multiple blocks
    new_file2 = "test_write_456.txt"
    name_subindex.raw = new_file2.encode("utf-8")
    file2_data = random_string_generator(2000)
    data_subindex.raw = file2_data.encode("utf-8")
    assert isfile(FWRITE_CACHE_DIR + new_file2)
    with open(FWRITE_CACHE_DIR + new_file2, "r") as fptr:
        assert fptr.read() == file2_data

    # write another file over CANbus with same name as last
    name_subindex.raw = new_file2.encode("utf-8")
    file2b_data = random_string_generator(50)
    data_subindex.raw = file2b_data.encode("utf-8")
    assert isfile(FWRITE_CACHE_DIR + new_file2)
    with open(FWRITE_CACHE_DIR + new_file2, "r") as fptr:
        assert fptr.read() == file2b_data

    network.disconnect()


def test_fwrite_reset():
    """Test if the reset subindex (DOMAIN, writeonly)"""
    network, node = connect_bus()
    subindex = node.sdo[FWRITE_INDEX][RESET_SUBINDEX]

    # writeonly
    with pytest.raises(SdoAbortedError):
        subindex.raw

    # reset deletes file
    fname = FWRITE_TMP_DIR + "test.txt"
    with open(fname, "w") as fptr:
        fptr.write("test")
    subindex.raw = "0".encode("utf-8")
    assert not isfile(fname)

    # should never fail
    subindex.raw = "0".encode("utf-8")
    subindex.raw = "0".encode("utf-8")
    subindex.raw = "0".encode("utf-8")

    # reset clear name
    name = "test_file_123.txt"
    node.sdo[FWRITE_INDEX][NAME_SUBINDEX].raw = name.encode("utf-8")
    subindex.raw = "0".encode("utf-8")
    with pytest.raises(SdoAbortedError):
        node.sdo[FWRITE_INDEX][NAME_SUBINDEX].raw

    network.disconnect()
