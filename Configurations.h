#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

/*
 * File Name --> Configurations.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> It includes configuration of application.
 * */

/*Define path of Keypad linux device driver file path.*/
#define CONFIG_KEYPAD_FILE_PATH                             "/dev/Keypad"

/*Define path of scrolling device linux device driver file path.*/
#define CONFIG_SCROLLING_DEVICE_FILE_PATH                   "/dev/ScrollingDevice"

/*Define path of available user led indicator linux device driver file path.*/
#define CONFIG_AVAILABLE_USER_LED_FILE_PATH                 "/dev/AvailableUserLed"

/*Define path of buzzer linux device driver file path.*/
#define CONFIG_BUZZER_FILE_PATH                 "/dev/PulseBuzzer"

/*Define path of reservation push button linux device driver file path.*/
#define CONFIG_RESERVATION_PUSH_BUTTON_DEVICE_FILE_PATH     "/dev/Pushbutton"

/*Define path of seven segment module linux device driver file path.*/
#define CONFIG_SEVEN_SEGMENT_MODULE_DEVICE_FILE_PATH        "/dev/SevenSegmentDisplayModule"
#define CONFIG_SEVEN_SEGMENT_MODULE_DISPLAY_UNITS           2
#define CONFIG_SEVEN_SEGMENT_MODULE_DIGITS_PER_UNIT         3
/*Database*/
/*
 * Definition of SQLite-Database file path & loader path.
 */
// Configuration for My PC
//#define CONFIG_DATABASE_PATH                    "/home/ahmed/Desktop/MyFiles/MyProjects/GUI/ATM-Machine-GUI/ATM-Database.db"
//#define CONFIG_LOADER_PATH                      "/opt/Qt5.12.12/5.12.12/gcc_64/plugins/sqldrivers/libqsqlite.so"

// Configuration for YOCTO-Image
#define CONFIG_DATABASE_PATH                    "/etc/ATM-Database.db"
#define CONFIG_LOADER_PATH                      "/usr/lib/plugins/sqldrivers/libqsqlite.so"

// Configuration for My Raspberry-PI
//#define CONFIG_DATABASE_PATH                    "ATM-Database.db"
//#define CONFIG_LOADER_PATH                      "/usr/lib/aarch64-linux-gnu/qt5/plugins/sqldrivers/libqsqlite.so"

/*Define time of checking of keypad pressed button.*/
#define CONFIG_KEYPAD_INTERVAL_TIME_IN_MS                         10

/*Define flashing time of avilable user led indicator.*/
#define CONFIG_AVAILABLE_USER_LED_FLASH_INTERVAL_TIME_IN_MS       500

/* Define time between two consecutive pressed of reservation push button
 * To avaid the same user request many numbers to use.
 */
#define CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_IN_SECONDS  2

#define CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_FOR_SCROLLING_DEVICE_S_IN_ms 250

#define CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_FOR_KEYPAD_IN_ms             250

#define CONFIG_CLICK_BUZZER_PULESE_TIME_IN_ms      40


#endif // CONFIGURATIONS_H
