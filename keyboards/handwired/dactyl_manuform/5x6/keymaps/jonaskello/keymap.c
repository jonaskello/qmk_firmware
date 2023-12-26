/* A Swedish XMonad layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

#include "features/achordion.h"

#define RAISE  MO(_RAISE)
#define LOWER  MO(_LOWER)
#define TERM   LGUI(LSFT(KC_ENT))
#define ALTTAB LGUI(KC_TAB)
#define KILL   LGUI(LSFT(KC_C))
#define OPEN   LGUI(KC_P)
#define KC_QSM LSFT(SE_PLUS)

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LSFT_T(KC_D)
#define HOME_F LCTL_T(KC_F)

// Right-hand home row mods
#define HOME_J RCTL_T(KC_J)
#define HOME_K RSFT_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_OD RGUI_T(SE_ODIA)

#define ACHORDION_STREAK

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  // Your macros ...

  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand.
  switch (tap_hold_keycode) {
    case HOME_F:  // CTRL+A, CTRL+S
      if (other_keycode == HOME_A || other_keycode == HOME_A || other_keycode == KC_Z
          || other_keycode == KC_X || other_keycode == KC_C || other_keycode == KC_V) { return true; }
      break;
  }

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

enum dactyl_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
     KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , SE_QUOT,
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
     KC_LSFT, HOME_A , HOME_S , HOME_D , HOME_F , KC_G   ,                        KC_H   , HOME_J , HOME_K , HOME_L , HOME_OD, SE_ADIA,
     KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , SE_SLSH, SE_MINS,
                       KC_EXLM, KC_QSM ,                                                            SE_PLUS, SE_EQL ,
                                                  RAISE  , KC_ENT ,      KC_SPC , LOWER  ,
                                                  _______, KC_BSPC,      KC_BSPC, KC_DEL ,
                                                  _______, _______,      _______, _______
  ),

  [_LOWER] = LAYOUT_5x6(
     SE_TILD, KC_EXLM,  SE_AT , KC_HASH, SE_DLR , KC_PERC,                        SE_CIRC, SE_AMPR, SE_ASTR, SE_SLSH, SE_LPRN, SE_RPRN,
     SE_ACUT, _______, _______, _______, _______, _______,                        _______, _______, KC_UP  , _______, SE_LCBR, SE_RCBR,
     _______, _______, _______, _______, _______, _______,                        _______, KC_LEFT, KC_DOWN, KC_RGHT, SE_LBRC, SE_RBRC,
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, SE_LABK, SE_RABK,
                       _______, _______,                                                            _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______

  ),

  [_RAISE] = LAYOUT_5x6(
     KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
     _______, _______, _______, _______, QK_BOOT, _______,                        KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_MUTE, SE_PIPE,
     _______, KC_PGDN, KC_PGUP, KC_END , _______, _______,                        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLU, SE_BSLS,
     _______, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______,                        _______, _______, _______, _______, KC_VOLD, _______,
                       _______, _______,                                                            _______, _______, 
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______
  ),
};
