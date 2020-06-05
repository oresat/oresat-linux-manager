/*
 * Main function for adding board apps.
 *
 * Board apps should call a mix of these function, depending on what the app
 * needs. All functions are optional.
 *
 *  app_OD_configure()
 *      - Used to add an app's CANopen ODF (Object Fictionary Function) for a
 *      index in the OD(Object Dictionary).
 *      - Defined in app_OD_helpers.*
 *
 *  app_register_daemon()
 *      - Used to let the CANdameon know it should be controll the add witht
 *      this fuction daemon.
 *      - Defined in daemon_controller.*
 *
 *  app_add_request_recv_file()
 *      - When the CANdaemon recieve file over CAN the file transfer ODF will
 *      check it's list of regex recv file name and will copy that file to
 *      where the app has requested.
 *      - This function is used to add a apps request for add a regex string
 *      - Uses PCRE2 regex.
 *      - Defined in file_transfer.*
 *
 *  <APP>_dbus_signal_match();
 *      - This is mostly for readablity in system_app.c as it is just a wrapper
 *      for all signal match calls to sd-bus for that app.
 *      - Replace <APP> with the apps name (ie: gps_dbus_signal_match())
 *      - Should be define in the app c/h files.
 *
 */
int setup_board_apps();
