# Design guide for candaemon apps

## Required functions
All candaemon apps require two functions `void <app>_OD_setup()` and `void <app>_dbus_run()`.
**NOTE:** The linux updater app uses `LU_OD_setup()` and `LU_dbus_run()`, the systemd app uses `systemd_OD_setup()` and `systemd_dbus()`, the board's main process app uses `BMP_OD_setup()` and `BMP_dbus_run()`.
- `<app>_OD_setup()` is used to set up any OD stuff need by candaemon to use the app. ie: register any object dictionary functions with  `CO_OD_configure()`.
- `<app>_dbus_run()` is a thread supplied by the candaemon for the board's main process app to use, AKA `the main()` for the app.

### Error handling in apps
- Use `log_message(in prio, char *message)`
    - *It will save to syslog*
- If an error occurs (like the app failing to connect to the systemd bus), **clean** your app's memory and call return. **Don`t ever call** `exit(EXIT_FAILURE)`.
    - *The candaemon must continue to run even if your app fails.*
    - *The candaemon will note it and may try to run function again later.*

### App CANopen Object Dictionary entries
- The candaemon, systemd, and linux updater will all use indexes in 0x3000 to 0x30FF in the OD.
    - *A nice way to group all system level stuff together .*
    - *Leaves more than enough indexes for the board's main process.*
- The Board's Main process app can freely use 0x3100 to 0x8000.
    - *More than enough indexes for the board's main process.*

## Making an new board main process app
- `cp -r src/boards/template src/boards/<new_board_name>`
- modify `src/boards/<new_board_name>/appilcation.*` as needed
- modify `src/boards/<new_board_name>/object_dictionary/*` with [libedssharp] as needed

## Editing App's Object Dictionary
- Use [libedssharp] to edit *.eds, *.xml, *.xdd, and CO_OD.* files.
    - *An opensource and useful CANopen object dictionary editor.*
    - *Dependency is only mono if you usea a release.*


[libedssharp]:https://github.com/robincornelius/libedssharp

