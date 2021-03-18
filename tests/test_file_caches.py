"""Test OLM file caches ODF"""

import pytest
from canopen import SdoAbortedError
from common import connect_bus, FCACHES_FREAD_VALID_FILES, \
        FCACHES_FREAD_INVALID_FILES, FCACHES_FREAD_EMPTY_FILE

FILE_CACHES_INDEX = 0x3001
FREAD_CACHE_LEN_SUBINDEX = 1
FWRITE_CACHE_LEN_SUBINDEX = 2
CACHE_SELECTOR_SUBINDEX = 3
FILTER_SUBINDEX = 4
CACHE_LEN_SUBINDEX = 5
ITERATOR_SUBINDEX = 6
NAME_SUBINDEX = 7
SIZE_SUBINDEX = 8
DELETE_SUBINDEX = 9

# valid cache selector inputs
FREAD_CACHE = 0
FWRITE_CACHE = 1


def test_fread_cache_len():
    """Test the fread cache length subindex  (uint8, readonly)."""
    network, node = connect_bus()
    subindex = node.sdo[FILE_CACHES_INDEX][FWRITE_CACHE_LEN_SUBINDEX]

    # test read
    subindex.phys

    # test readonly
    with pytest.raises(SdoAbortedError):
        subindex.phys = 0

    network.disconnect()


def test_fwrite_cache_len():
    """Test the fwrite cache length subindex (uint8, readonly)."""
    network, node = connect_bus()
    subindex = node.sdo[FILE_CACHES_INDEX][FWRITE_CACHE_LEN_SUBINDEX]

    # test read
    subindex.phys

    # test readonly
    with pytest.raises(SdoAbortedError):
        subindex.phys = 0

    network.disconnect()


def test_cache_selector():
    """Test the cache selector subindex (uint8, readwrite)."""
    network, node = connect_bus()
    subindex = node.sdo[FILE_CACHES_INDEX][CACHE_SELECTOR_SUBINDEX]

    # test read
    subindex.phys

    # test write with valid inputs
    subindex.phys = FREAD_CACHE
    assert FREAD_CACHE == subindex.phys
    subindex.phys = FWRITE_CACHE
    assert FWRITE_CACHE == subindex.phys
    subindex.phys = FREAD_CACHE
    assert FREAD_CACHE == subindex.phys
    subindex.phys = FWRITE_CACHE
    assert FWRITE_CACHE == subindex.phys

    # test with invalid input
    with pytest.raises(SdoAbortedError):
        subindex.phys = 12

    network.disconnect()


def test_filer():
    """Test the cache filter subindex (DOMAIN, readonly)."""
    network, node = connect_bus()
    node.sdo[FILE_CACHES_INDEX][CACHE_SELECTOR_SUBINDEX].phys = FREAD_CACHE
    subindex = node.sdo[FILE_CACHES_INDEX][FILTER_SUBINDEX]

    # test read with empty filter
    with pytest.raises(SdoAbortedError):
        subindex.raw

    # test write with valid inputs
    subindex.raw = "foo".encode("utf-8")
    assert "foo\0" == subindex.raw.decode("utf-8")
    subindex.raw = "bar\0".encode("utf-8")
    assert "bar\0" == subindex.raw.decode("utf-8")
    subindex.raw = b'\00'  # clear filter
    with pytest.raises(SdoAbortedError):
        subindex.raw

    network.disconnect()


def test_cache_len():
    """Test the selected cache length subindex (uint32, readonly)."""
    network, node = connect_bus()
    selector_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_SELECTOR_SUBINDEX]
    len_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_LEN_SUBINDEX]

    selector_subindex.phys = FREAD_CACHE

    # test readonly fro fread cache
    len = len_subindex.phys
    with pytest.raises(SdoAbortedError):
        len_subindex.phys = 42
    assert len == len_subindex.phys

    selector_subindex.phys = FWRITE_CACHE

    # test readonly fro fwrite cache
    len = len_subindex.phys
    with pytest.raises(SdoAbortedError):
        len_subindex.phys = 42
    assert len == len_subindex.phys

    selector_subindex.phys = FREAD_CACHE
    network.disconnect()


def test_iterator():
    """Test the iterator subindex (uint32, readonly)."""
    network, node = connect_bus()
    selector_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_SELECTOR_SUBINDEX]
    len_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_LEN_SUBINDEX]
    iter_subindex = node.sdo[FILE_CACHES_INDEX][ITERATOR_SUBINDEX]

    selector_subindex.phys = FREAD_CACHE

    # valid iterator values
    for i in range(len_subindex.phys):
        iter_subindex.phys = i

    # invalid iterator values
    with pytest.raises(SdoAbortedError):
        iter_subindex.phys = len_subindex.phys
    with pytest.raises(SdoAbortedError):
        iter_subindex.phys = len_subindex.phys + 10

    selector_subindex.phys = FWRITE_CACHE

    # valid iterator values
    for i in range(len_subindex.phys):
        iter_subindex.phys = i

    # invalid iterator values
    with pytest.raises(SdoAbortedError):
        iter_subindex.phys = len_subindex.phys
    with pytest.raises(SdoAbortedError):
        iter_subindex.phys = len_subindex.phys + 10

    selector_subindex.phys = FREAD_CACHE
    network.disconnect()


def test_file_name():
    """Test the file name subindex (DOMAIN, readonly)."""
    network, node = connect_bus()
    len_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_LEN_SUBINDEX]
    iter_subindex = node.sdo[FILE_CACHES_INDEX][ITERATOR_SUBINDEX]
    name_subindex = node.sdo[FILE_CACHES_INDEX][NAME_SUBINDEX]

    # test readonly
    with pytest.raises(SdoAbortedError):
        name_subindex.raw = "0".encode("utf-8")

    count = 0

    # check for all valid and invalid files
    # make sure to handle the posible for files from CO fread test
    for i in range(len_subindex.phys):
        iter_subindex.phys = i
        name = name_subindex.raw.decode("utf-8").replace('\0', '')

        assert name not in FCACHES_FREAD_INVALID_FILES or \
            name == FCACHES_FREAD_EMPTY_FILE

        if name in FCACHES_FREAD_VALID_FILES:
            count += 1

    assert count == len(FCACHES_FREAD_VALID_FILES)

    network.disconnect()


def test_file_size():
    """Test the file size subindex (uint32, readonly)."""
    network, node = connect_bus()
    len_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_LEN_SUBINDEX]
    iter_subindex = node.sdo[FILE_CACHES_INDEX][ITERATOR_SUBINDEX]
    size_subindex = node.sdo[FILE_CACHES_INDEX][SIZE_SUBINDEX]

    # test readonly
    with pytest.raises(SdoAbortedError):
        size_subindex.phys = 0

    # all files have their size set and there are not empty files
    for i in range(len_subindex.phys):
        iter_subindex.phys = i
        assert size_subindex.phys != 0

    network.disconnect()


def test_delete_file():
    """Test the delete file subindex (DOMAIN, readonly)."""
    network, node = connect_bus()
    selector_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_SELECTOR_SUBINDEX]
    len_subindex = node.sdo[FILE_CACHES_INDEX][CACHE_LEN_SUBINDEX]
    iter_subindex = node.sdo[FILE_CACHES_INDEX][ITERATOR_SUBINDEX]
    name_subindex = node.sdo[FILE_CACHES_INDEX][NAME_SUBINDEX]
    delete_subindex = node.sdo[FILE_CACHES_INDEX][DELETE_SUBINDEX]

    # test writeonly
    with pytest.raises(SdoAbortedError):
        delete_subindex.phys

    # Delete all FCACHES_FREAD_VALID_FILES cache files but don't delete any
    # fread files
    for i in range(len(FCACHES_FREAD_VALID_FILES)):
        found = False
        length = len_subindex.phys

        for i in range(length):
            iter_subindex.phys = i
            name = name_subindex.raw.decode("utf-8").replace('\0', '')

            if name in FCACHES_FREAD_VALID_FILES:
                delete_subindex.raw = "0".encode("utf-8")
                assert len_subindex.phys == length-1
                found = True
                break

        assert found

    selector_subindex.phys = FWRITE_CACHE

    for i in range(len_subindex.phys-1, 0, -1):
        iter_subindex.phys = i
        delete_subindex.raw = "0".encode("utf-8")
        assert len_subindex.phys == i
        assert iter_subindex.phys == 0  # should be 0 after delete is called

    selector_subindex.phys = FREAD_CACHE

    network.disconnect()
