/* A Swedish XMonad layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

// https://getreuer.info/posts/keyboards/achordion/index.html
#include "features/achordion.h"

#define RAISE  MO(_RAISE)
#define LOWER  MO(_LOWER)
#define TERM   LGUI(LSFT(KC_ENT))
#define KC_QSM LSFT(SE_PLUS)

// Left-hand home row mods - base layer
#define HM_A LGUI_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LSFT_T(KC_D)
#define HM_F LCTL_T(KC_F)
// Right-hand home row mods - base layer
#define HM_J RCTL_T(KC_J)
#define HM_K RSFT_T(KC_K)
#define HM_L LALT_T(KC_L)
#define HM_OD RGUI_T(SE_ODIA)

// // Left-hand home row mods - raise layer
// #define HM_1 LGUI_T(KC_1)
// #define HM_2 LALT_T(KC_2)
// #define HM_3 LSFT_T(KC_3)
// #define HM_4 LCTL_T(KC_4)
// Right-hand home row mods - raise layer
#define HM_4 RCTL_T(KC_4)
#define HM_5 RSFT_T(KC_5)
#define HM_6 LALT_T(KC_6)
#define HM_0 RGUI_T(KC_0)

#define ACHORDION_STREAK

enum {
    UD_GRV = QK_USER,
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  // Your macros ...
    switch (keycode) {
        case UD_GRV:
            if (record->event.pressed) {
                tap_code16(SE_GRV);
                tap_code16(KC_SPC);
            }
            return false;

        default:
            return true;
    }

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
    case HM_F:  // CTRL+A, CTRL+S
      if (other_keycode == HM_A || other_keycode == HM_S || other_keycode == KC_Z
          || other_keycode == KC_X || other_keycode == KC_C || other_keycode == KC_V) { return true; }
      break;
  }

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LCTL:
    case MOD_RCTL:
      return true;  // Eagerly apply Shift and Ctrl mods.

    default:
      return false;
  }
}

enum dactyl_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_5x6(
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
     KC_BSPC, HM_A   , HM_S   , HM_D   , HM_F   , KC_G   ,                        KC_H   , HM_J   , HM_K   , HM_L   , HM_OD  , SE_ADIA,
     SE_QUOT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , SE_MINS, SE_PLUS,
                       _______, _______,                                                            _______, _______,
                                                  RAISE  , KC_ENT ,      KC_SPC , LOWER  ,
                                                  _______, KC_DEL ,      KC_TAB , _______,
                                                  _______, _______,      _______, _______
  ),

  // [_RAISE] = LAYOUT_5x6(
  //    _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
  //    SE_PIPE, SE_EXLM, SE_DQUO, SE_HASH, SE_CURR, SE_PERC,                        SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL , _______,
  //    SE_LABK, HM_1   , HM_2   , HM_3   , HM_4   , KC_5   ,                        KC_6   , HM_7   , HM_8   , HM_9   , HM_0   , UD_GRV ,
  //    SE_RABK, _______, SE_AT  , SE_TILD, SE_DLR, SE_BSLS ,                        _______, SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, _______,
  //                      _______, _______,                                                            _______, _______,
  //                                                 _______, _______,      _______, _______,
  //                                                 _______, _______,      _______, _______,
  //                                                 _______, _______,      _______, _______
  // ),

  [_RAISE] = LAYOUT_5x6(
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     SE_PIPE, SE_EXLM, SE_DQUO, SE_HASH, SE_CURR, SE_PERC,                        _______, KC_7   , KC_8   , KC_9   , _______, UD_GRV ,
     SE_AMPR, SE_LCBR, SE_RCBR, SE_LBRC, SE_RBRC, _______,                        KC_0   , HM_4   , HM_5   , HM_6   , _______, _______,
     SE_SLSH, SE_LABK, SE_RABK, SE_LPRN, SE_RPRN, SE_EQL ,                        SE_LABK, KC_1   , KC_2   , KC_3   , _______, _______,
                       _______, _______,                                                            _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______
  ),


  [_LOWER] = LAYOUT_5x6(
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                        KC_PGUP, KC_HOME, KC_UP  , KC_END , _______, _______,
     KC_F11 , KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_F12 ,                        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
     _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                        _______, _______, _______, _______, _______ , _______,
                       _______, _______,                                                            _______, _______, 
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______
  ),

};
