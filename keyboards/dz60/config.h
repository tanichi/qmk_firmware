#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */

/*
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { F0, F1, E6, C7, C6, B7, D4, B1, B0, B5, B4, D7, D6, B3, F4 }
*/

// for my PCB; DZ60 V2 Flex cut Soldered PCB
#define MATRIX_ROW_PINS { F0, B3, F6, F4, F5}
#define MATRIX_COL_PINS { F1, D0, D1, D2, D3, D5, D4, D6, D7, B4, F7, C7, C6, B6, B5}


/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

// #define LED_CAPS_LOCK_PIN B2
#define LED_CAPS_LOCK_PIN E6
#define LED_PIN_ON_STATE 1

// No BackLIGHT for my PCB, un use pin B0
#define BACKLIGHT_PIN B0
#define BACKLIGHT_LEVELS 5

#define RGB_DI_PIN B2
#ifdef RGB_DI_PIN
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 16
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* VIA related config */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
