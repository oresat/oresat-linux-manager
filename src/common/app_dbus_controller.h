#include <systemd/sd-bus.h>
#include <stdbool.h>


typedef struct {
    sd_bus *bus;
    bool loop_running;
} app_dbus_data_t;


int apps_dbus_start();
int apps_dbus_main();
int apps_dbus_end();


