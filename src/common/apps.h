/**
 * App for the Linux updater dameon.
 *
 * @file        apps.h
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef OLM_APP_H
#define OLM_APP_H


/**
 * @defgroup    apps OLM Apps
 * @{
 *
 * Apps are as the dbus adaptors for OLM to commicate with daemons.
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
