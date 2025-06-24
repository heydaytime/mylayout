/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "keycodes.h"
#include "keymap_us.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "features/custom_shift_keys.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};


enum custom_keycodes {
    CTL_B = SAFE_RANGE,
    CTL_G,
    MACRO_J,  // Custom J macro
    MACRO_Z   // Custom Z macro
};

// https://getreuer.info/posts/keyboards/custom-shift-keys/index.html#add-custom-shift-keys-to-your-keymap
const custom_shift_key_t custom_shift_keys[] = {
    {KC_EXLM, KC_1},    // ! -> 1 when Shift is held
    {KC_AT,   KC_2},    // @ -> 2
    {KC_HASH, KC_3},    // # -> 3
    {KC_DLR,  KC_4},    // $ -> 4
    {KC_PERC, KC_5},    // % -> 5
    {KC_CIRC, KC_6},    // ^ -> 6
    {KC_AMPR, KC_7},    // & -> 7
    {KC_ASTR, KC_8},    // * -> 8
    {KC_LPRN, KC_9},    // ( -> 9
    {KC_RPRN, KC_0},    // ) -> 0
    {KC_COLON, KC_SEMICOLON} // : -> ;
};


uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// clang-format off
// https://docs.qmk.fm/keycodes
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_84(
     KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_MOD,
     KC_GRV,KC_EXCLAIM,KC_AT,KC_HASH,KC_DOLLAR,KC_PERCENT,KC_CIRCUMFLEX,KC_AMPERSAND,KC_ASTERISK,KC_LEFT_PAREN,KC_RIGHT_PAREN,KC_MINS,KC_EQL,CTL_B,KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_COLON,  KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     KC_BACKSPACE,  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,            KC_ENT,      KC_HOME,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,     KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,           CTL_G,  KC_UP,    KC_END,
     KC_LCTL,  MO(MAC_FN), KC_LCMMD,                               KC_SPC,                                 KC_ESC,MO(MAC_FN),KC_ROPTN,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_ansi_84(
     _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  RGB_TOG,
     _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     RGB_TOG,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     _______,  _______,  _______,            _______,
     _______,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     MACRO_J,  KC_K,     KC_L,     KC_SCLN,  _______,            _______,            _______,
     _______,            MACRO_Z,  KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     _______,  _______,  _______,            _______,  _______,  _______,
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

[WIN_BASE] = LAYOUT_ansi_84(
     KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     KC_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_ansi_84(
     _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
     _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
     _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______)
};

// clang-format on

// Track whether Left Shift is currently held
static bool lshift_held = false;

// Variables for macro key repeat functionality
static bool macro_j_pressed = false;
static bool macro_z_pressed = false;
static uint16_t macro_j_timer = 0;
static uint16_t macro_z_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_shift_keys(keycode, record)) { return false; }

    switch (keycode) {
        case KC_LSFT:
            lshift_held = record->event.pressed;
            break;

        case KC_RSFT:
            if (record->event.pressed) {
                if (lshift_held) {
                    // If Left Shift is held, send Ctrl+Y instead of RShift
                    SEND_STRING(SS_LCTL("y"));
                    return false; // suppress default RShift
                }
            }
            break; // allow RShift to work normally if LShift not held

        case CTL_B:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("b"));  // Sends Ctrl+B
            }
            return false;

        case CTL_G:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("g"));  // Sends Ctrl+G
            }
            return false;

        case MACRO_J:
            if (record->event.pressed) {
                // Key pressed
                macro_j_pressed = true;
                macro_j_timer = timer_read();
                register_code(KC_J);  // Register J key
            } else {
                // Key released
                macro_j_pressed = false;
                unregister_code(KC_J);  // Unregister J key
            }
            return false;

        case MACRO_Z:
            if (record->event.pressed) {
                // Key pressed
                macro_z_pressed = true;
                macro_z_timer = timer_read();
                register_code(KC_Z);  // Register Z key
            } else {
                // Key released
                macro_z_pressed = false;
                unregister_code(KC_Z);  // Unregister Z key
            }
            return false;
    }

    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}

// Handle key repeat functionality
void matrix_scan_user(void) {
    // Handle J key repeat
    if (macro_j_pressed) {
        if (timer_elapsed(macro_j_timer) > TAPPING_TERM) {
            // Key has been held long enough, enable repeat
            // The register_code above will handle the repeat automatically
        }
    }

    // Handle Z key repeat
    if (macro_z_pressed) {
        if (timer_elapsed(macro_z_timer) > TAPPING_TERM) {
            // Key has been held long enough, enable repeat
            // The register_code above will handle the repeat automatically
        }
    }
}
