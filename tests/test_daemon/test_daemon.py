#!/usr/bin/env python3


from pydbus import SystemBus
from gi.repository import GLib
import threading
import time


INTERFACE_NAME = "org.OreSat.Example"


class Test_Server(object):
    dbus = """
    <node>
        <interface name="org.OreSat.Example">
            <property name="Mode" type="d" access="read"/>
            <property name="Test2" type="u" access="readwrite"/>
        </interface>
    </node>
    """

    def __init__(self):
        self._Test1 = 12.3
        self._Test2 = 1
        self._running = True
        self._working_thread = threading.Thread(target=self._working_loop)
        self._working_thread.start()  # start working thread

    @property
    def Mode(self):
        return self._Test1

    @Test2.setter
    def Test2(self, value):
        self._Test2 = value

    def _working_loop(self):
        while (self._running is True):
            self._Test1 += 1.0
            time.sleep(1)

    def quit(self):
        self._running = False

if __name__ == "__main__":
    bus = SystemBus()  # connect to bus
    loop = GLib.MainLoop()  # only used by server

    # Setup server to emit signals over the DBus
    test_server = Test_Server()
    bus.publish(INTERFACE_NAME, test_server)

    # Run loop with graceful ctrl C exiting.
    try:
        loop.run()
    except KeyboardInterrupt as e:
        loop.quit()
        test_server.quit()

