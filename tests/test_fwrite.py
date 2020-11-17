"""testing candeamon"""

import pytest
from test_helpers import connect_bus

FWRITE_INDEX = 0x3001


def test_fwrite():
    """test if a file write works"""
    network, node = connect_bus()

    node.sdo.download(FWRITE_INDEX, 1, str.encode("a_update_test1.txt"))
    node.sdo.download(FWRITE_INDEX, 2, str.encode("test "*1000 + "\n"))

    network.disconnect()
    assert True


def test_fwrite_cancel_empty_buf():
    """test if canceling a file write works"""

    network, node = connect_bus()

    node.sdo.download(FWRITE_INDEX, 3, b"00")
    node.sdo.download(FWRITE_INDEX, 3, b"00")

    network.disconnect()
    assert True


def test_fwrite_cancel():
    """test if canceling a file write works"""

    network, node = connect_bus()

    node.sdo.download(FWRITE_INDEX, 1, str.encode("a_update_test2.txt"))
    node.sdo.download(FWRITE_INDEX, 3, b"00")

    network.disconnect()
    assert True


def test_fwrite_no_filename():
    """test if canceling a file write works"""

    network, node = connect_bus()

    # make sure filename is cleared
    node.sdo.download(FWRITE_INDEX, 3, b"00")

    with pytest.raises(Exception):
        node.sdo.download(FWRITE_INDEX, 2, str.encode("test "*1000 + "\n"))

    network.disconnect()
    assert True
