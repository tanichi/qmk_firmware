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
    _QWERTY,
    _FN,
    _MAC,    
    MAC_FN,
};

#define OVR_TGL KEY_OVERRIDE_TOGGLE

const key_override_t at_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, JP_AT);          //def
const key_override_t circ_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, JP_CIRC);
const key_override_t and_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, JP_AMPR);
const key_override_t lkakko_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, JP_ASTR);
const key_override_t rkakko_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, JP_LPRN);
const key_override_t rprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, JP_RPRN);      //def
const key_override_t uscore_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, JP_UNDS);
const key_override_t eq_key_override = ko_make_with_layers_and_negmods(0, KC_EQL, JP_EQL, ~0, (uint8_t) MOD_MASK_SHIFT); 
const key_override_t plus_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, JP_PLUS);
const key_override_t lbrc_key_override = ko_make_with_layers_and_negmods(0, KC_LBRC, JP_LBRC, ~0, (uint8_t) MOD_MASK_SHIFT);    //def
const key_override_t lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, JP_LCBR);   //def
const key_override_t rbbr_key_override = ko_make_with_layers_and_negmods(0, KC_RBRC, JP_RBRC, ~0, (uint8_t) MOD_MASK_SHIFT); 
const key_override_t rcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, JP_RCBR); 
const key_override_t bsls_key_override = ko_make_with_layers_and_negmods(0, KC_BSLS, JP_BSLS, ~0, (uint8_t) MOD_MASK_SHIFT); 
const key_override_t pipe_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, JP_PIPE);     
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, JP_COLN); 
const key_override_t quot_key_override = ko_make_with_layers_and_negmods(0, KC_QUOT, JP_QUOT, ~0, (uint8_t) MOD_MASK_SHIFT);    //def
const key_override_t dquo_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, JP_DQUO);   //def
const key_override_t grv_key_override = ko_make_with_layers_and_negmods(0, KC_GRAVE, JP_GRV, ~0, (uint8_t) MOD_MASK_SHIFT);    //def
const key_override_t tild_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_GRAVE, JP_TILD);   //def
const key_override_t znhn_key_override = ko_make_with_layers_and_negmods(0, KC_F19, JP_ZKHK, ~0, (uint8_t) MOD_MASK_SHIFT);

const key_override_t **key_overrides = (const key_override_t *[]){
    &znhn_key_override,
    &at_key_override,
    &circ_key_override,
    &and_key_override,
    &lkakko_key_override,
    &rkakko_key_override,
    &rprn_key_override,
    &uscore_key_override,    
    &eq_key_override,
    &plus_key_override,
    &lcbr_key_override,
    &dquo_key_override,
    &lbrc_key_override,
    &rbbr_key_override,
    &rcbr_key_override,
    &bsls_key_override,
    &pipe_key_override,
    &coln_key_override,
    &quot_key_override,
    &grv_key_override,
    &tild_key_override,
    NULL
};

//Custom Keymap Definitions
#define KC_CAD LALT(LCTL(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty Base layer
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   BS   |
 * |-----------------------------------------------------------------------------------------+
 * | `/_Media|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   SHIFT   |  Fn |
 * |-----------------------------------------------------------------------------------------+
 * | LCtrl | LGui  | LAlt  |     Space     |  Fn  |    Space   | F7  | F10 |Left |Down |Right|
 *  `----------------------------------------------------------------------------------------'
 */

    [_QWERTY] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_ESC ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,   KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0, KC_MINS , KC_EQL, KC_BSLS, KC_GRAVE,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
           KC_TAB ,    KC_Q ,   KC_W ,   KC_E ,   KC_R ,   KC_T ,   KC_Y ,   KC_U ,   KC_I ,   KC_O ,   KC_P, KC_LBRC, KC_RBRC ,  KC_BSPC    ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
            KC_LCTL  ,   KC_A ,   KC_S ,   KC_D ,   KC_F ,   KC_G ,   KC_H ,   KC_J ,   KC_K ,   KC_L, KC_SCLN, KC_QUOT ,       KC_ENT       ,
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
            KC_LSFT      ,   KC_Z ,   KC_X ,   KC_C ,   KC_V ,   KC_B ,   KC_N ,   KC_M, KC_COMM , KC_DOT, KC_SLSH,  KC_NO,KC_RSFT  , MO(_FN),
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
         KC_LCTL ,  KC_LGUI ,  KC_LALT ,         KC_SPC         ,  MO(_FN) ,         KC_F19     ,  KC_NO ,  KC_NO ,  KC_NO ,DF(_MAC), OVR_TGL
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    ),

/* F-Key/Lighting/whatever layer
 * ,-----------------------------------------------------------------------------------------.
 * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F0  | F11 | F12 |     | Ins |
 * |-----------------------------------------------------------------------------------------+
 * |       |R_Tog|  7  |  8  |  9  |     |     |     |  U  |     |     |  U  |     |  KC_CAD |
 * |-----------------------------------------------------------------------------------------+
 * |  Caps  |     |  4  |  5  |  6  |      | BSP |  L  |  R  |     |  L  |  R  | Print Screen|
 * |-----------------------------------------------------------------------------------------+
 * |          |R_M_P|  1  |  2  |  3  |R_M_S|R_M_K|  D  |R_M_G|     |  D  |PgUp  BLUP |PgDn |
 * |-----------------------------------------------------------------------------------------+
 * |       |       |       |               |      |            |     |     |BLTog|BLDN |BLInc|
 *  `----------------------------------------------------------------------------------------'
 */

    [_FN] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_NO ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 , KC_F12 ,  KC_NO ,  KC_INS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
            KC_NO  , RGB_TOG,  KC_7  ,  KC_8  ,  KC_9  ,  KC_NO  , KC_DEL,  KC_NO ,  KC_UP ,  KC_NO ,  KC_NO ,  KC_UP ,  KC_NO ,   KC_DEL    ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
           KC_CAPS   ,  KC_NO ,   KC_4 ,   KC_5 ,   KC_6 ,  KC_NO , KC_BSPC, KC_LEFT, KC_RGHT,  KC_NO , KC_LEFT, KC_RGHT,       KC_PSCR      ,
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
        _______, RGB_M_P,    KC_1 ,   KC_2 ,   KC_3 ,RGB_M_SN, RGB_M_K, KC_DOWN, RGB_M_G,  KC_NO , KC_DOWN,  KC_NO ,      BL_INC    , KC_PGDN,
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
         _______ ,  _______ ,  _______ ,         KC_NO          ,  _______ ,        KC_NO       ,  KC_NO ,  KC_NO , BL_TOGG, BL_DEC , BL_STEP
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    ),

/* MAC Base layer
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   BS   |
 * |-----------------------------------------------------------------------------------------+
 * | `/_Media|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   SHIFT   |  Fn |
 * |-----------------------------------------------------------------------------------------+
 * | LCtrl | LGui  | LAlt  |     Space     |  Fn  |    Space   | F7  | F10 |Left |Down |Right|
 *  `----------------------------------------------------------------------------------------'
 */

    [_MAC] = LAYOUT_directional(
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
         KC_LCTL ,  KC_LALT ,  KC_LGUI ,          KC_SPC        ,  MO(_FN) ,     LGUI(KC_SPC)   ,  KC_NO ,  KC_NO ,  KC_NO ,DF(_QWERTY),OVR_TGL
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    ),
    
    [MAC_FN] = LAYOUT_directional(
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_NO ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 , KC_F12 ,  KC_NO ,  KC_INS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
           KC_NO   ,RGB_TOG ,   KC_7 ,   KC_8 ,   KC_9 ,  KC_NO , KC_DEL ,  KC_NO ,  KC_UP ,  KC_NO ,  KC_NO ,  KC_UP ,  KC_NO ,    KC_DEL   ,
    //|------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------------|
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
           KC_CAPS   ,  KC_NO ,   KC_4 ,   KC_5 ,   KC_6 ,  KC_NO , KC_BSPC, KC_LEFT, KC_RGHT,  KC_NO , KC_LEFT, KC_RGHT,       KC_PSCR      ,
    //|--------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------|
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
              _______    , RGB_M_P,   KC_1 ,   KC_2 ,   KC_3 , RGB_M_SN,RGB_M_K, KC_DOWN, RGB_M_G,  KC_NO , KC_DOWN, KC_NO , BL_INC , KC_PGDN,
    //|------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------|
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
         _______ ,  _______ ,  _______ ,          KC_NO         ,  _______ ,         KC_NO      ,  KC_NO ,  KC_NO , BL_TOGG, BL_DEC , BL_STEP
    //|----------+----------+----------+------------------------+----------+--------------------+--------+--------+--------+--------+--------|
    )

/* original func layer
  [_FN] = LAYOUT_directional(
        KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO, KC_INS,
        KC_NO, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_UP, KC_NO, KC_CAD,
        KC_CAPS, KC_NO, RGB_HUD, RGB_SAD, RGB_VAD,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_RGHT, KC_PSCR,
        _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_DOWN, KC_NO, BL_INC,  KC_PGDN,
        _______, _______, _______, KC_NO, _______,  KC_NO,  KC_NO, KC_NO, BL_TOGG, BL_DEC,  BL_STEP
        ),
*/


};
