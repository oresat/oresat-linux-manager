#!/usr/bin/env python3
"""Test daemon for OLM unit tests"""

import time
import threading
from pydbus import SystemBus
from gi.repository import GLib

INTERFACE_NAME = "org.oresat.test"


class TestServer():
    """ Test D-Bus server for OLM unit tests"""

    dbus = """
    <node>
        <interface name="org.oresat.test">
            <property name="Test1" type="d" access="read"/>
            <property name="Test2" type="u" access="readwrite"/>
        </interface>
    </node>
    """  # can't be in __init__()

    def __init__(self):
        self._test1 = 12.3
        self._test2 = 1
        self._running = True
        self._working_thread = threading.Thread(target=self._working_loop)
        self._working_thread.start()  # start working thread

    def __del__(self):
        self.quit()

    @property
    def Test1(self):
        """Setter for Test2 property"""
        return self._test1

    @property
    def Test2(self):
        """Getter for Test2 property"""
        return self._test2

    @Test2.setter
    def Test2(self, value):
        """Setter for Test2 property"""
        self._test2 = value

    def _working_loop(self):
        """D-Bus server working loop."""

        while self._running is True:
            self._test1 += 1.0
            time.sleep(1)

    def quit(self):
        """Stop thread."""
        self._running = False


if __name__ == "__main__":
    bus = SystemBus()
    loop = GLib.MainLoop()
    test_server = TestServer()
    bus.publish(INTERFACE_NAME, test_server)

    try:
        loop.run()
    except KeyboardInterrupt:
        loop.quit()
        test_server.quit()
