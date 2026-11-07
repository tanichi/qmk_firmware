#include QMK_KEYBOARD_H

#include "keymap_japanese.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// Layer structure is the same as dz60:tanichi (WIN_* / MAC_*), plus the 7skb-only ADJUST layer.
// Switch between Win and Mac with FN + bottom-right key (DF).
enum layer_number {
  WIN_QWERTY = 0,
  WIN_FN,
  MAC_QWERTY,
  MAC_FN,
  ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  LARROW,   // types "<-" (same as dz60)
  RARROW    // types "->" (same as dz60)
};

// ---- JIS conversion (same as dz60:tanichi) --------------------------------
// The keycaps are US layout, but the OS is set to the JIS layout.
// These overrides send the JIS key that produces the symbol printed on the US keycap.
// Toggle all of them on/off with OVR_TGL (e.g. on a PC/Mac set to the US layout).
#define OVR_TGL KO_TOGG

const key_override_t at_key_override   = ko_make_basic(MOD_MASK_SHIFT, KC_2, JP_AT);        // SHIFT + 2 => "@"
const key_override_t circ_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, JP_CIRC);      // SHIFT + 6 => "^"
const key_override_t amrp_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, JP_AMPR);      // SHIFT + 7 => "&"
const key_override_t astr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, JP_ASTR);      // SHIFT + 8 => "*"
const key_override_t lprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, JP_LPRN);      // SHIFT + 9 => "("
const key_override_t rprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, JP_RPRN);      // SHIFT + 0 => ")"
const key_override_t unds_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, JP_UNDS);   // SHIFT + "-" => "_"
const key_override_t eql_key_override  = ko_make_with_layers_and_negmods(0, KC_EQL, JP_EQL, ~0, (uint8_t) MOD_MASK_SHIFT);      // "=" (without SHIFT)
const key_override_t plus_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, JP_PLUS);    // SHIFT + "=" => "+"
const key_override_t lbrc_key_override = ko_make_with_layers_and_negmods(0, KC_LBRC, JP_LBRC, ~0, (uint8_t) MOD_MASK_SHIFT);    // "[" (without SHIFT)
const key_override_t lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, JP_LCBR);   // SHIFT + "[" => "{"
const key_override_t rbbr_key_override = ko_make_with_layers_and_negmods(0, KC_RBRC, JP_RBRC, ~0, (uint8_t) MOD_MASK_SHIFT);    // "]" (without SHIFT)
const key_override_t rcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, JP_RCBR);   // SHIFT + "]" => "}"
const key_override_t bsls_key_override = ko_make_with_layers_and_negmods(0, KC_BSLS, JP_BSLS, ~0, (uint8_t) MOD_MASK_SHIFT);    // "\" (without SHIFT)
const key_override_t pipe_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, JP_PIPE);   // SHIFT + "\" => "|"
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, JP_COLN);   // SHIFT + ";" => ":"
const key_override_t quot_key_override = ko_make_with_layers_and_negmods(0, KC_QUOT, JP_QUOT, ~0, (uint8_t) MOD_MASK_SHIFT);    // "'" (without SHIFT)
const key_override_t dquo_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, JP_DQUO);   // SHIFT + "'" => '"'
const key_override_t grv_key_override  = ko_make_with_layers_and_negmods(0, KC_GRAVE, JP_GRV, ~0, (uint8_t) MOD_MASK_SHIFT);    // "`" (without SHIFT)
const key_override_t tild_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_GRAVE, JP_TILD);  // SHIFT + "`" => "~"

// for Windows JIS map, F19 => Zenkaku/Hankaku
const key_override_t zkhk_key_override = ko_make_with_layers_and_negmods(0, KC_F19, JP_ZKHK, ~0, (uint8_t) MOD_MASK_SHIFT);

const key_override_t *key_overrides[] = {
    &zkhk_key_override, &at_key_override, &circ_key_override, &amrp_key_override, &astr_key_override,
    &lprn_key_override, &rprn_key_override, &unds_key_override, &eql_key_override, &plus_key_override,
    &lcbr_key_override, &dquo_key_override, &lbrc_key_override, &rbbr_key_override, &rcbr_key_override,
    &bsls_key_override, &pipe_key_override, &coln_key_override, &quot_key_override, &grv_key_override,
    &tild_key_override };
// ---------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Windows base: GUI, Alt order / F19 = Zenkaku-Hankaku (via JIS conversion)
  [WIN_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, MO(WIN_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LGUI, KC_LALT,  KC_SPC,  KC_SPC,               KC_ENT,  KC_F19,           LARROW,  RARROW 
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  // FN (same as dz60): left = numpad, right = arrows / Home / End / Del / BS
  [WIN_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
   TG(ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_NO,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,    KC_7,    KC_8,    KC_9,   KC_NO,      KC_DEL, KC_HOME,   KC_UP,  KC_END,   KC_NO,   KC_UP,   KC_NO,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      KC_CAPS,   KC_NO,    KC_4,    KC_5,    KC_6,   KC_NO,     KC_BSPC, KC_LEFT, KC_RGHT,   KC_NO, KC_LEFT, KC_RGHT,TG(ADJUST),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______,    KC_0,    KC_1,    KC_2,    KC_3,   KC_NO,       KC_NO, KC_DOWN, _______, _______, KC_DOWN,   KC_NO, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______,   KC_NO,   KC_NO,              _______,   KC_NO,          OVR_TGL, DF(MAC_QWERTY)
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  // Mac base: Alt(Option), GUI(Command) order / IME switch = Cmd+Space at the F19 position
  [MAC_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, MO(MAC_FN),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LALT, KC_LGUI,  KC_SPC,  KC_SPC,               KC_ENT,LGUI(KC_SPC),       LARROW,  RARROW
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  // Mac FN: same as WIN_FN except the bottom-right key switches back to Windows.
  // (dz60's MAC_FN has no OVR_TGL; 7skb has it here too so the JIS conversion can be toggled on Mac.)
  [MAC_FN] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
   TG(ADJUST),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_NO,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,    KC_7,    KC_8,    KC_9,   KC_NO,      KC_DEL, KC_HOME,   KC_UP,  KC_END,   KC_NO,   KC_UP,   KC_NO,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      KC_CAPS,   KC_NO,    KC_4,    KC_5,    KC_6,   KC_NO,     KC_BSPC, KC_LEFT, KC_RGHT,   KC_NO, KC_LEFT, KC_RGHT,TG(ADJUST),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______,    KC_0,    KC_1,    KC_2,    KC_3,   KC_NO,       KC_NO, KC_DOWN, _______, _______, KC_DOWN,   KC_NO, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______,   KC_NO,   KC_NO,              _______,   KC_NO,          OVR_TGL, DF(WIN_QWERTY)
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  // 7skb only: LED settings / QK_BOOT (unchanged)
  [ADJUST] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
   TG(ADJUST), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     UG_TOGG, UG_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     UG_VALD, UG_VALU, UG_HUED, UG_HUEU, UG_SATD, UG_SATU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX,          KC_STOP, XXXXXXX 
          //`---------------------------------------------|   |--------------------------------------------'
  )
};


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case WIN_FN:
    case MAC_FN:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case ADJUST:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      break;
    }
    rgblight_set_effect_range( 1, 11);
#endif
return state;
}

// OS detection (same as dz60): called once the host OS has been detected
// (see OS_DETECTION_SINGLE_REPORT in config.h).
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

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  switch (keycode) {
    case LARROW:
        if (record->event.pressed) {
          SEND_STRING("<-");
        }
      break;
    case RARROW:
        if (record->event.pressed) {
          SEND_STRING("->");
        }
      break;
    #ifdef RGBLIGHT_ENABLE
      case UG_NEXT:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}
