# Design guide for candaemon apps

## Required functions
All candaemon apps require two functions `int <app_name>_app_setup()` and `int <app_name>_app_main)`.
**NOTE:** The linux updater app uses `linux_updater_app_setup()` and `linux_updater_app_main()`, the systemd app uses `systemd_app_setup()` and `systemd_app_main()`, the board's main process app uses `main_process_app_setup()` and `main_process_app_main()`.
- `<app_name>_app_setup()` is used to set up any OD functions needed by candaemon to use the app and to tell the systemd app what daemon to control. ie: register any object dictionary functions with `app_app_configure()` and associate daemon with app with `app_add_daemon()`.
- `<app_name>_app_main()` is a thread supplied by the candaemon for the app to use, AKA the `main()` for the app.

### Error handling in apps
- Use `app_log_message(char* app_name, int prio, char *message)`
    - *It will save to syslog with a nice format*
- If an error occurs (like the app failing to connect to the systemd bus), **clean** your app's memory and call return.
    - *The candaemon will note it and may try to run the app main again later.*
- **Don't ever call** `exit()`.
    - *The candaemon must continue to run even if the app fails.*

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
    - *It is an opensource and useful CANopen object dictionary editor.*
    - *Dependency is only mono if you use a release.*


[libedssharp]:https://github.com/robincornelius/libedssharp

