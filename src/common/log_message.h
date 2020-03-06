#include <syslog.h>

/*
 * Logs the message in syslog and will output to stderr/stdout, if available.
 * see man vsyslog for prioprity levels
 */
void log_message(int priority, const char *fmt, ...);


/**
 * A nice function for a app to log message in syslogs with a standard format.
 *
 * @param app_name: for application name
 * @param priority: for log proprity
 * @param message: the message to log
 */
void app_log_message(const char *app_name, int priority, const char *message);

