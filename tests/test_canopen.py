"""testing candeamon"""

from test_helpers import connect_bus


def test_fread_list():
    """test if a file write works"""
    network, node = connect_bus()

    network.nmt.state = 'OPERATIONAL'

    node_id = node.sdo.upload(0x2101, 0)
    assert int.from_bytes(node_id, byteorder="little", signed=False) == 0x10

    network.disconnect()
    assert True
