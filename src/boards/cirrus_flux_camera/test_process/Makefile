CC= gcc
CFLAGS= -g -Wall -D_GNU_SOURCE
LDFLAGS= $(shell pkg-config --libs libsystemd)

all: oresat-test-cfc

oresat-test-cfc:
	$(CC) oresat-test-cfc.c camera-i2c.c testprucam.c qdbmp.c -o $@ $(CFLAGS) $(LDFLAGS)


install:
	bash -c "cp ./oresat-test-cfc /usr/bin/"
	bash -c "cp ./oresat-test-cfc.service /lib/systemd/system"
	bash -c "cp ./org.OreSat.CirrusFluxCamera.conf /usr/share/dbus-1/system.d/"
	bash -c "systemctl daemon-reload"

run:
	bash -c "systemctl start oresat-test-cfc"

clean:
	rm -f oresat-test-cfc

remove:
	bash -c "systemctl stop oresat-test-cfc"
	bash -c "rm /usr/bin/oresat-test-cfc"
	bash -c "rm /lib/systemd/system/oresat-test-cfc.service"
	bash -c "rm /usr/share/dbus-1/system.d/org.OreSat.CirrusFluxCamera.conf"
	bash -c "systemctl daemon-reload"

help:
	@echo "Options: "
	@echo "  make oresat-test-cfc"
	@echo "  make all"
	@echo "  make clean"
	@echo "  sudo make install"
	@echo "  sudo make run"
	@echo "  sudo make remove"
