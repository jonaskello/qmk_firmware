/* A Swedish XMonad layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

enum dactyl_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define RAISE  MO(_RAISE)
#define LOWER  MO(_LOWER)
#define KC_QSM LSFT(SE_PLUS)

#define LSH_ENT LSFT_T(KC_ENT)
#define RSH_SPC RSFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
     KC_BSPC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , SE_ODIA, SE_ADIA,
     KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , SE_MINS, KC_LGUI,
                       _______, _______,                                                            _______, _______,
                                                  RAISE  , LSH_ENT,      RSH_SPC, LOWER  ,
                                                  _______, KC_LALT,      KC_TAB , _______,
                                                  _______, _______,      _______, _______
  ),
  
  [_RAISE] = LAYOUT_5x6(
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
     _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
     _______, KC_F11 , KC_F12 , SE_LBRC, SE_RBRC, _______,                        _______, SE_LCBR, SE_RCBR, SE_SLSH, SE_MINS, _______,
                       _______, _______,                                                            _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______

  ),

  [_LOWER] = LAYOUT_5x6(
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                        KC_PGUP, KC_HOME, KC_UP  , KC_END , _______, _______,
     _______, _______, _______, _______, _______, _______,                        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
                       _______, _______,                                                            _______, _______, 
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______
  ),


};
