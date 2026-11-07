#pragma once

/*
 * Settings for my PCB: DZ60 V2 Flex cut Soldered PCB.
 * Its pin assignments differ from the stock DZ60 defined in keyboards/dz60/keyboard.json.
 *
 * This file is included after the config generated from keyboard.json,
 * so each value is #undef'd before being redefined.
 * Values not listed here (diode direction, RGB steps/animations, sleep, locking, ...)
 * are the same as keyboard.json and are inherited from it.
 */

/* Key matrix */
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { F0, B3, F6, F4, F5 }
#define MATRIX_COL_PINS { F1, D0, D1, D2, D3, D5, D4, D6, D7, B4, F7, C7, C6, B6, B5 }

/* Caps Lock LED (stock: B2, active low) */
#undef LED_CAPS_LOCK_PIN
#undef LED_PIN_ON_STATE
#define LED_CAPS_LOCK_PIN E6
#define LED_PIN_ON_STATE 1

/* RGB underglow data pin (stock: E2) */
#undef WS2812_DI_PIN
#define WS2812_DI_PIN B2
