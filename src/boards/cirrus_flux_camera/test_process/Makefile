CC= gcc
CFLAGS= -g -Wall
LDFLAGS= $(shell pkg-config --libs libsystemd)

all: camera_dbus_test_server

camera_dbus_test_server:
	$(CC) camera_dbus_test_server.c camera-i2c.c testprucam.c -o $@ $(CFLAGS) $(LDFLAGS)

run:
	sudo nohup ./camera_dbus_test_server &

clean:
	rm -f camera_dbus_test_server
