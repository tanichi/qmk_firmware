 /* Copyright 2020 Philip Chan
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 
#include QMK_KEYBOARD_H

#include "keymap_japanese.h"

//Layers
enum layer_names {
    WIN_QWERTY,
    WIN_FN,
    MAC_QWERTY,
    MAC_FN,
    LED
};

#define OVR_TGL KO_TOGG

const key_override_t at_key_override  =  ko_make_basic(MOD_MASK_SHIFT, KC_2, JP_AT);        // SHIFT + 2 => "@"
const key_override_t circ_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, JP_CIRC);      // SHIFT + 6 => "^"
const key_override_t amrp_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, JP_AMPR);      // SHIFT + 7 => "&"
const key_override_t astr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, JP_ASTR);      // SHIFT + 8 => "*"
const key_override_t lprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, JP_LPRN);      // SHIFT + 9 => "("
const key_override_t rprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, JP_RPRN);      // SHIFT + 0 => ")"
const key_override_t unds_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, JP_UNDS);   // SHIFT + "-" => "_"
const key_override_t eql_key_override =  ko_make_with_layers_and_negmods(0, KC_EQL, JP_EQL, ~0, (uint8_t) MOD_MASK_SHIFT);      // "="  
const key_override_t plus_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, JP_PLUS);    // SHIFT + "+" => "+"
const key_override_t lbrc_key_override = ko_make_with_layers_and_negmods(0, KC_LBRC, JP_LBRC, ~0, (uint8_t) MOD_MASK_SHIFT);    // "[" 
const key_override_t lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, JP_LCBR);   // SHIFT + "[" => "{"
const key_override_t rbbr_key_override = ko_make_with_layers_and_negmods(0, KC_RBRC, JP_RBRC, ~0, (uint8_t) MOD_MASK_SHIFT);    // "]" 
const key_override_t rcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, JP_RCBR);   // SHIFT + "]" => "}"
const key_override_t bsls_key_override = ko_make_with_layers_and_negmods(0, KC_BSLS, JP_BSLS, ~0, (uint8_t) MOD_MASK_SHIFT);    // "\" 
const key_override_t pipe_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, JP_PIPE);   // SHIFT + "\" => "|"
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, JP_COLN);   // SHIFT + "," => "<"
const key_override_t quot_key_override = ko_make_with_layers_and_negmods(0, KC_QUOT, JP_QUOT, ~0, (uint8_t) MOD_MASK_SHIFT);    // "'"
const key_override_t dquo_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, JP_DQUO);   // SHIFT + "'" => '"'
const key_override_t grv_key_override =  ko_make_with_layers_and_negmods(0, KC_GRAVE, JP_GRV, ~0, (uint8_t) MOD_MASK_SHIFT);    // "`"
const key_override_t tild_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_GRAVE, JP_TILD);  // SHIFT + "`" => "~"

// for Windows JIS map, F19 => Zenkaku/Hankaku 
const key_override_t zkhk_key_override = ko_make_with_layers_and_negmods(0, KC_F19, JP_ZKHK, ~0, (uint8_t) MOD_MASK_SHIFT);

const key_override_t *key_overrides[] = {
    &zkhk_key_override, &at_key_override, &circ_key_override, &amrp_key_override, &astr_key_override,
    &lprn_key_override, &rprn_key_override, &unds_key_override, &eql_key_override, &plus_key_override,
    &lcbr_key_override, &dquo_key_override, &lbrc_key_override, &rbbr_key_override, &rcbr_key_override,
    &bsls_key_override, &pipe_key_override, &coln_key_override, &quot_key_override, &grv_key_override,
    &tild_key_override };

//Custom Keymap Definitions
#define KC_CAD LALT(LCTL(KC_DEL)) // Control-ALT-Delete
#define KC_SS LGUI(LSFT(KC_S))    // Screen-Shot Win-Shift-S
#define KC_MAC_SS LGUI(LCTL(LSFT(KC_4)))  // Mac Screen-Shot Cmd-Ctrl-Shift-4 (selection to clipboard)

// Bottom-left key: hold = FN layer, tap = screenshot.
// LT() can only tap a basic keycode (modifiers are dropped), so the tap is
// replaced with the real shortcut in process_record_user().
// KC_S / KC_4 below are placeholders and are never sent.
#define WIN_SS_FN LT(WIN_FN, KC_S)
#define MAC_SS_FN LT(MAC_FN, KC_4)

enum custom_keycodes {
   LARROW = SAFE_RANGE ,
   RARROW
};

// OS detection: called once the host OS has been detected (see OS_DETECTION_SINGLE_REPORT in config.h).
//   Windows      -> Win layer, JIS conversion ON  (the PC is set to the JIS layout)
//   macOS / iOS  -> Mac layer, JIS conversion OFF (the Mac is set to the US layout)
//   Linux/unsure -> leave as is
// Neither change is saved to EEPROM; it is detected again on every connection.
// The manual switch (FN + bottom-right, OVR_TGL) still works afterwards.
bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_WINDOWS:
            set_single_default_layer(WIN_QWERTY);
            key_override_on();
            break;
        case OS_MACOS:
        case OS_IOS:
            set_single_default_layer(MAC_QWERTY);
            key_override_off();
            break;
        default:
            break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        case WIN_SS_FN:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_SS);      // tapped: send Win+Shift+S instead of the placeholder
                return false;
            }
            break;                      // held: let QMK handle the layer switch
        case MAC_SS_FN:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_MAC_SS);  // tapped: send Cmd+Ctrl+Shift+4 instead of the placeholder
                return false;
            }
            break;                      // held: let QMK handle the layer switch
        case LARROW:
            if(record->event.pressed){
                //pressed
                SEND_STRING("<-");
            } else {
                //released
            }
            break;
        case RARROW:
            if(record->event.pressed){
                //pressed
                SEND_STRING("->");
            } else {
                //released
            }
            break;
    }

    // when return true, send a keycode based Keymap
    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_QWERTY] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_ESC ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,   KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_MINS, KC_EQL, KC_BSLS, KC_GRAVE,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
           KC_TAB ,    KC_Q ,   KC_W ,   KC_E ,   KC_R ,   KC_T ,   KC_Y ,   KC_U ,   KC_I ,   KC_O ,   KC_P, KC_LBRC, KC_RBRC ,  KC_BSPC    ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
            KC_LCTL  ,   KC_A ,   KC_S ,   KC_D ,   KC_F ,   KC_G ,   KC_H ,   KC_J ,   KC_K ,   KC_L, KC_SCLN, KC_QUOT ,       KC_ENT       ,
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
            KC_LSFT      ,   KC_Z ,   KC_X ,   KC_C ,   KC_V ,   KC_B ,   KC_N ,   KC_M, KC_COMM , KC_DOT, KC_SLSH,  KC_NO,KC_RSFT  , MO(WIN_FN),
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
       WIN_SS_FN ,  KC_LGUI ,  KC_LALT ,          KC_SPC        ,  KC_ENT  ,         KC_F19     , LARROW , RARROW ,  KC_NO ,  KC_NO , KC_NO
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    ),

    [WIN_FN] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_NO ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 , KC_F12 ,  KC_NO ,  KC_INS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
           KC_NO   ,  KC_NO ,   KC_7 ,   KC_8 ,   KC_9 ,  KC_NO , KC_DEL , KC_HOME,  KC_UP , KC_END ,  KC_NO ,  KC_UP ,  KC_NO ,    KC_DEL   ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
           KC_CAPS   ,  KC_NO ,   KC_4 ,   KC_5 ,   KC_6 ,  KC_NO , KC_BSPC, KC_LEFT, KC_RGHT,  KC_NO , KC_LEFT, KC_RGHT,       DF(LED)      ,
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
              _______    ,  KC_0  ,   KC_1 ,   KC_2 ,   KC_3 ,  KC_NO ,  KC_NO , KC_DOWN, _______, _______, KC_DOWN, KC_NO ,  KC_NO ,  KC_NO ,
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
         _______ ,  _______ ,  _______ ,         KC_NO          ,  _______ ,        KC_NO       , OVR_TGL,DF(MAC_QWERTY),  KC_NO ,  KC_NO ,  KC_NO
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    ),

    [MAC_QWERTY] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_ESC ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,   KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_MINS,  KC_EQL, KC_BSLS,KC_GRAVE,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
            KC_TAB ,   KC_Q ,   KC_W ,   KC_E ,   KC_R ,   KC_T ,   KC_Y ,   KC_U ,   KC_I ,   KC_O ,   KC_P , KC_LBRC, KC_RBRC,    KC_BSPC  ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
           KC_LCTL   ,   KC_A ,   KC_S ,   KC_D ,   KC_F ,   KC_G ,   KC_H ,   KC_J ,   KC_K ,   KC_L , KC_SCLN, KC_QUOT,       KC_ENT       ,
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
             KC_LSFT     ,   KC_Z ,   KC_X ,   KC_C ,   KC_V ,   KC_B ,   KC_N ,   KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_NO, KC_RSFT ,MO(MAC_FN),
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
       MAC_SS_FN ,  KC_LALT ,  KC_LGUI ,         KC_SPC         ,  KC_ENT  ,     LGUI(KC_SPC)   , LARROW , RARROW ,  KC_NO ,  KC_NO , KC_NO
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    ),
    
    [MAC_FN] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_NO ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 , KC_F12 ,  KC_NO ,  KC_INS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
           KC_NO   ,  KC_NO ,   KC_7 ,   KC_8 ,   KC_9 ,  KC_NO , KC_DEL , KC_HOME,  KC_UP , KC_END ,  KC_NO ,  KC_UP ,  KC_NO ,    KC_DEL   ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
           KC_CAPS   ,  KC_NO ,   KC_4 ,   KC_5 ,   KC_6 ,  KC_NO , KC_BSPC, KC_LEFT, KC_RGHT,  KC_NO , KC_LEFT, KC_RGHT,       DF(LED)      ,
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
              _______    ,  KC_0  ,   KC_1 ,   KC_2 ,   KC_3 ,  KC_NO ,  KC_NO , KC_DOWN, _______, _______, KC_DOWN, KC_NO ,  KC_NO ,  KC_NO ,
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
         _______ ,  _______ ,  _______ ,          KC_NO         ,  _______ ,         KC_NO      ,  KC_NO ,DF(WIN_QWERTY),KC_NO,  KC_NO ,  KC_NO 
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    ),
    
// original func layer
    [LED] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_NO ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12,   KC_NO,  KC_INS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
             KC_NO , UG_TOGG, UG_HUEU, UG_SATU, UG_VALU,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UP,   KC_NO,    KC_NO    ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
            KC_CAPS  ,  KC_NO , UG_HUED, UG_SATD, UG_VALD,  KC_NO ,  KC_NO ,  KC_NO ,  KC_NO ,  KC_NO , KC_LEFT, KC_RGHT,       DF(WIN_QWERTY),
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
            _______      , RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO,   KC_DOWN, KC_NO ,  KC_NO ,  KC_NO ,
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
        _______  ,   _______,   _______,            KC_NO       ,   _______,         KC_NO      ,  KC_NO ,  KC_NO ,  KC_NO ,  KC_NO ,  KC_NO 
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    )
};
