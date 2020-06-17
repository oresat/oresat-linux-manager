# Oresat Linux CANdaemon

The CANdaemon is the Linux board controller / CAN interface program for all Linux boards on OreSat.
It is built ontop of [CANopenNode] and interfaces with [Systemd], allowing the master CAN node to control everything on the board over CAN. 
The CANdaemon is ment to be a node on the CANbus, not the master node.

![](docs/OreSatLinuxDiagram.jpg)

## Features
- Built on top of the [CANopenNode], therefor it follows the [CANopen-Specifcations] by CiA ([CAN-in-Automation]).
- Follows the [ECSS-CANBus-Extended-Protocal] on top of CiA specs.
- Allows the CAN Network Manager to control any [daemons] on the Linux board thru [Systemd].
- Has a app based system that uses sd-bus (systemd dbus) for DBus communication to OreSat [daemons].
- Allows other daemons with candaemon apps to read/write to the CAN object dictionary over dbus.
- Allows the other processes/daemons to be written in any language that has a DBus library or a DBus binding. A lot of languages do have DBus support, See [freedesktop DBus Bindings](https://www.freedesktop.org/wiki/Software/DBusBindings/) for a DBus supported languague list.

## Directory Layout 
- **src** - Holds an CANdaemon app for each OreSat Linux board
    - **boards** - Holds boards apps and CANopen Object Dictionary for each OreSat Linux board.
    - **CANopenNode** - The git submodule for CANopenNode
    - **common** - Common source code, regardless of which board is enabled.
    - **socketCAN** - CANopenNode SocketCAN driver
    - **system_apps** - Apps that will be on every board.
    - **test_apps** - Apps that are used fot testing / debugging.
- **docs** - Documentation for CANdaemon

## Dependices
### To compile
- For Debian:`apt install git libsystemd-dev cmake make gcc  libpcre2-dev`
    - optional: `ninja-build`
- For Arch: `pacman -S git systemd-libs cmake make gcc pcre2`
    - optional: `ninja`
### To run
- For Debian: `apt install libsystemd-dev libpcre2-dev`
- For Arch: `pacman -S systemd-libs pcre2`

## How to use
- Compiling
    - `cd build`
    - `cmake -DBOARD=<board> ..` or `cmake -GNinja -DBOARD=<board> ..`
    - `make` or `ninja`
- Optional cmake flags, 1st option in `[ ]` is default when not specified:
    - `-DCMAKE_BUILD_TYPE=[Debug|Release]` to turn the -g -Wall cflags on/off
- Running CANdaemon
    - `./candaemon <device>` as a process
    - `./candaemon <device> -d` as a daemon
- Installing binary and daemon service file (usefull for testing)
    - `sudo make install` or `sudo ninja install`
- Building deb binary package on a beaglebone (or debian based armhf system)
    - `sudo make package` or`sudo ninja package`

## Making a new board
- `cp -r boards/template boards/<new_board_name>`
- modify /boards/NEW_BOARD_NAME/board_apps.* as needed
- modify /boards/NEW_BOARD_NAME/objDict with [libedssharp] as needed

## Useful References
- [CAN-Wikipedia]
- [Daemons]
- [Systemd]
- [Systemd-DBus]
- [DBus-Specifcations]
- [CANopen-Specifcations]
- [ECSS-CANBus-Extended-Protocal]

<!-- Other oresat repos -->
[GPS]:https://github.com/oresat/oresat-gps-software
[StarTracker]:https://github.com/oresat/oresat-star-tracker
[OreSatLive]:https://github.com/oresat/oresat-dxwifi-software

<!-- References -->
[CAN-Wikipedia]:https://en.wikipedia.org/wiki/CAN_bus
[CANopenNode]:https://github.com/CANopenNode/CANopenNode
[Daemons]:https://www.freedesktop.org/software/systemd/man/daemon.html
[Systemd]:https://freedesktop.org/wiki/Software/systemd/
[Systemd-DBus]:https://www.freedesktop.org/wiki/Software/systemd//
[DBus-Specifcations]:https://.freedesktop.org/doc/dbus-specification.html
[CANopen-Specifcations]:https://www.can-cia.org/groups/specifications/
[ECSS-CANBus-Extended-Protocal]:https://ecss.nl/standard/ecss-e-st-50-15c-space-engineering-canbus-extension-protocol-1-may-2015/
[CAN-in-Automation]:https://can-cia.org/

<!-- Other --> 
[libedssharp]:https://github.com/heliochronix/libedssharp
