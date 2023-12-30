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
// #define RAI_DEL LT(_RAISE, KC_DEL)
// #define LOW_BSP LT(_LOWER, KC_BSPC)
// #define RAI_BSP LT(_RAISE, KC_BSPC)
// #define LOW_DEL LT(_LOWER, KC_DEL)
// #define LSH_ENT LSFT_T(KC_ENT)
// #define RSH_SPC RSFT_T(KC_SPC)
#define LSH_ENT LSFT_T(KC_ENT)
#define RSH_SPC RSFT_T(KC_SPC)
#define KC_QSM LSFT(SE_PLUS)

// Shift + Backspace for Delete
// Initialize variable holding the binary representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }

    }
    return true;
};

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
     SE_PIPE, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , SE_PLUS,
     SE_LABK, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , SE_QUOT,
     _______, KC_F11 , SE_AT  , SE_TILD, SE_DLR, SE_BSLS ,                        KC_F12 , SE_LCBR, SE_LBRC, SE_RBRC, SE_RCBR, _______,
                       _______, _______,                                                            _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______,
                                                  _______, _______,      _______, _______

  ),

//SE_PND SE_EURO

// <> | ?+ ~ @$£€ `^ ¨´§½

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
