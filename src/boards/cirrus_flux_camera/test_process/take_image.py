#!/usr/bin/env python3

from pydbus import SystemBus
from gi.repository import GLib

INTERFACE_NAME = "org.OreSat.CirrusFluxCamera"

if __name__=="__main__":
    bus = SystemBus() # connect to bus
    the_object = bus.get(INTERFACE_NAME)

    print("Calling LatestImage method")
    reply = the_object.LatestImage()
    print("Returned: %s\n" % reply)

