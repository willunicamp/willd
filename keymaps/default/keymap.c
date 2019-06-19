#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layer shorthand
#define _BL 0
#define _LW 1
#define _RS 2
#define _DT 3

bool key_triggered = false;
bool lower_on = false;

enum layer_keycodes {
    QWERTY = SAFE_RANGE, LOWER, RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BL] = LAYOUT(
KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_NO, KC_ENT,
KC_LSFT, TG(_DT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
KC_LCPO, KC_LGUI, KC_LALT, KC_NO, KC_SPC, KC_NO, KC_NO, LOWER, KC_NO, KC_SCLN, RAISE, KC_RAPC
),
	[_LW] = LAYOUT(
KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, 
KC_TILD, KC_MINS, KC_PLUS, KC_S, KC_T, KC_D, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_QUOT, 
KC_LSFT, KC_PAUS, KC_HOME, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS, 
KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KC_DEL, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_QUOT, KC_UNDS, KC_EQL
),
	[_RS] = LAYOUT(
KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS,
KC_LSFT, KC_PSCR, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, RGB_SAD, RGB_SAI, BL_STEP,
KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_MPLY, KC_MPRV, KC_MNXT
            ),
	[_DT] = LAYOUT(
KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_NO, KC_ENT,
KC_LSFT, KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
KC_F1, KC_F2, KC_LALT, KC_NO, KC_SPC, KC_NO, KC_NO, KC_B, KC_NO, KC_MPLY, KC_MPRV, KC_MNXT
            ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
//        if(record->tap.interrupted){
            //key_triggered = true;
        //}
      if(record->event.pressed){
        layer_on(_LW);
        lower_on = true;
      }else{
        layer_off(_LW);
        lower_on = false;
      }
      return false;
      break;
    case RAISE:
      if(record->event.pressed){
        layer_on(_RS);
      } else {
        layer_off(_RS);
      }
      return false;
      break;
  }
  return true;
};


void encoder_update_user(uint8_t index, bool clockwise) {
    if(!lower_on){
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }else{
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
};
