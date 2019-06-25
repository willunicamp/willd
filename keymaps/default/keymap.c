#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layer shorthand
#define _BL 0
#define _LW 1
#define _RS 2
#define _DT 3

enum layer_keycodes {
    QWERTY = SAFE_RANGE, LOWER, RAISE, DOTA, ENCODER
};

typedef enum  {
   MUSIC=0,PGSCROLL=1,WHEEL=2,ARROWS=3
}encoder_states;

encoder_states state = MUSIC;
bool dota_layer = false;
bool tap = false;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BL] = LAYOUT(
KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_NO, KC_ENT,
KC_LSFT, DOTA, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
KC_LCPO, KC_LGUI, KC_LALT, KC_MPLY, KC_SPC, KC_NO, KC_NO, LOWER, KC_NO, KC_SCLN, RAISE, KC_RAPC
),
	[_LW] = LAYOUT(
KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, 
KC_TILD, KC_MINS, KC_PLUS, KC_S, KC_T, KC_D, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_QUOT, 
KC_LSFT, KC_MPRV, KC_HOME, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS, 
KC_LCTL, KC_LGUI, KC_LALT, KC_MNXT, KC_QUOT , KC_NO, KC_NO, KC_TRNS, KC_NO, KC_QUOT, KC_UNDS, KC_EQL
),
	[_RS] = LAYOUT(
KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
ENCODER, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS,
KC_LSFT, KC_PSCR, BL_TOGG, BL_INC, BL_DEC, BL_BRTG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_STEP,
KC_LCTL, KC_LGUI, KC_LALT, RESET, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_MPRV, KC_TRNS, KC_MNXT
            ),
	[_DT] = LAYOUT(
KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_NO, KC_ENT,
KC_LSFT, DOTA, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
KC_F1, KC_F2, KC_LALT, KC_F9, KC_SPC, KC_NO, KC_NO, KC_B, KC_NO, KC_MPLY, KC_MPRV, KC_MNXT
            ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    static uint16_t side_key_timer, lower_timer;

    case LOWER:
      if(record->event.pressed){
        lower_timer = timer_read();
        layer_on(_LW);
        writePinHigh(B4);
        tap=false;
      }else{
        layer_off(_LW);
        //if I release  the layer key without pressing any other key,
        //the tap flag will still be false
        if((tap==false)&&(timer_elapsed(lower_timer) < TAPPING_TERM)){
            tap_code(KC_SPC);
        }
        writePinLow(B4);
      }
      return false;
      break;
    case RAISE:
      if(record->event.pressed){
        layer_on(_RS);
        writePinHigh(B5);
      } else {
        layer_off(_RS);
        writePinLow(B5);
      }
      return false;
      break;
    case DOTA:
      if(record->event.pressed){
        side_key_timer = timer_read();
        if(!dota_layer){
            dota_layer=true;
            layer_on(_DT);
            writePinHigh(B6);
            writePinHigh(B5);
            writePinHigh(B4);
        }else{
            tap_code(KC_X);
        }
      }else{
        if (timer_elapsed(side_key_timer) > 300) {  
            dota_layer=false;
            layer_off(_DT);
            writePinLow(B6);
            writePinLow(B5);
            writePinLow(B4);
        }
      }
      return false;
      break;
    case ENCODER:
      if(record->event.pressed){
       switch(state){
        case MUSIC:
            state = PGSCROLL;
            break;
        case PGSCROLL:
            state = WHEEL;
            break;
        case WHEEL:
            state = ARROWS;
            break;
        case ARROWS:
            state = MUSIC;
            break;
       }
      }
      return false;
      break;
    default:
        tap = true;//if tap something, tap is true
      break;
  }
  return true;
};


void encoder_update_user(uint8_t index, bool clockwise) {
        uint16_t key1=0,key2=0;
       switch(state){
        case MUSIC:
            key1 = KC_VOLD;
            key2 = KC_VOLU;
            break;
        case PGSCROLL:
            key1 = KC_PGDN;
            key2 = KC_PGUP;
            break;
        case WHEEL:
            key1 = KC_WH_D;
            key2 = KC_WH_U;
            break;
        case ARROWS:
            key1 = KC_DOWN;
            key2 = KC_UP;
            break;
       }
        if (clockwise) {
            tap_code(key1);
            writePinHigh(B6);
            writePinLow(B6);
        } else {
            tap_code(key2);
            writePinHigh(B6);
            writePinLow(B6);
        }
};
