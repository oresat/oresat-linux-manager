"""Test OLM OS command"""

import pytest
from enum import Enum
from time import sleep
from canopen import SdoAbortedError
from common import connect_bus, random_string_generator

FWRITE_INDEX = 0x1023
COMMAND_SUBINDEX = 1
STATUS_SUBINDEX = 2
REPLY_SUBINDEX = 3


class OSCommandReply(Enum):
    no_error_no_reply = 0x00
    no_error_reply = 0x01
    error_no_reply = 0x02
    error_reply = 0x03
    excuting = 0xFF


def test_os_command():
    """Test if the fwrite filename subindex (DOMAIN, readwrite)."""
    network, node = connect_bus()
    command_subindex = node.sdo[FWRITE_INDEX][COMMAND_SUBINDEX]
    status_subindex = node.sdo[FWRITE_INDEX][STATUS_SUBINDEX]
    reply_subindex = node.sdo[FWRITE_INDEX][REPLY_SUBINDEX]

    assert status_subindex.phys == OSCommandReply.no_error_no_reply.value

    # read no data
    with pytest.raises(SdoAbortedError):
        command_subindex.raw

    assert status_subindex.phys == OSCommandReply.no_error_no_reply.value

    # invalid message with reply
    command_subindex.raw = "echo \"abcd\"".encode("utf-8")
    while status_subindex.phys == OSCommandReply.excuting.value:
        sleep(0.1)
    assert status_subindex.phys == OSCommandReply.no_error_reply.value

    # message with reply
    message = random_string_generator(10)
    bash_message = "echo \"" + message + "\""
    command_subindex.raw = bash_message.encode("utf-8")
    assert command_subindex.raw.decode("utf-8") == bash_message+"\0"
    if status_subindex.phys == OSCommandReply.excuting.value:
        sleep(1)
    assert status_subindex.phys == OSCommandReply.no_error_reply.value
    assert len(reply_subindex.raw.decode("utf-8")) == len(message)+1
    assert reply_subindex.raw.decode("utf-8") == message+"\n"

    # medium message with medium reply
    message = random_string_generator(100)
    bash_message = "echo \"" + message + "\""
    command_subindex.raw = bash_message.encode("utf-8")
    assert command_subindex.raw.decode("utf-8") == bash_message+"\0"
    if status_subindex.phys == OSCommandReply.excuting.value:
        sleep(1)
    assert status_subindex.phys == OSCommandReply.no_error_reply.value
    assert len(reply_subindex.raw.decode("utf-8")) == len(message)+1
    assert reply_subindex.raw.decode("utf-8") == message+"\n"

    # large message with large reply
    message = random_string_generator(5000)
    bash_message = "echo \"" + message + "\""
    command_subindex.raw = bash_message.encode("utf-8")
    assert command_subindex.raw.decode("utf-8") == bash_message+"\0"
    if status_subindex.phys == OSCommandReply.excuting.value:
        sleep(1)
    assert status_subindex.phys == OSCommandReply.no_error_reply.value
    assert len(reply_subindex.raw.decode("utf-8")) == len(message)+1
    assert reply_subindex.raw.decode("utf-8") == message+"\n"

    network.disconnect()
