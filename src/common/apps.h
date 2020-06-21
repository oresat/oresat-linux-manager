/**
 * App for the Linux updater dameon.
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef CANDAEMON_APP_H
#define CANDAEMON_APP_H


/**
 * @defgroup    apps CANdaemon Apps
 * @{
 *
 * Apps are as the dbus adaptors for the CANdaemon to commicate with daemons.
 *
 * Apps should call a mix of app_* functions, depending on what the app
 * needs. All functions are optional.
 *
 * @}
 */



/****************************************************************************/


/**
 * @ingroup     apps
 * @defgroup    board_apps Board Apps
 * @{
 *
 * These are apps that are only enabled for a specific board.
 */


/**
 * Used to add board apps for a specific app.
 *
 * @return 1 on success
 */
int board_apps_setup(void);


/** @} */
/****************************************************************************/


/**
 * @ingroup     apps
 * @defgroup    system_apps System Apps
 * @{
 *
 * These are apps that are available on every board.
 */


/**
 * Used to add system apps.
 *
 * @return 1 on success
 */
int system_apps_setup(void);


/** @} */
/****************************************************************************/


/**
 * @ingroup     apps
 * @defgroup    App_Helpers App Helpers
 * @{
 *
 * Useful helper functions for making apps.
 *
 * @}
 */


#endif
