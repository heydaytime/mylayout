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
    CST_LCRLY,  // Custom Left Curly Brace
    CST_RCRLY,  // Custom Right Curly Brace
    VIM_ESC,    // Custom Vim Escape key
    VIM_A,      // Vim insert mode keys
    VIM_I,
    VIM_O,
    VIM_C,
    VIM_S,
    VIM_R,
};

// https://getreuer.info/posts/keyboards/custom-shift-keys/index.html#add-custom-shift-keys-to-your-keymap
const custom_shift_key_t custom_shift_keys[] = {
    {KC_EXLM, KC_1},    // ! -> 1
    {KC_LBRC, KC_2},    // [ -> 2
    {CST_LCRLY, KC_3},  // { -> 3
    {KC_LPRN, KC_4},    // ( -> 4
    {KC_PERC, KC_5},    // % -> 5
    {KC_ASTR, KC_6},    // * -> 6
    {KC_AMPR, KC_7},    // & -> 7
    {KC_RPRN, KC_8},    // ) -> 8
    {CST_RCRLY, KC_9},  // } -> 9
    {KC_RBRC, KC_0},    // ] -> 0
    {KC_COLON, KC_SEMICOLON}, // : -> ;
    {KC_AT, KC_DLR},   // @ -> $
    {KC_HASH, KC_CIRC}, // # -> ^
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// Variables to track layer state and RGB settings
static bool is_mac_fn_layer = false;
static bool vim_mode_active = false;  // Track if we're in vim normal mode vs regular fn layer
static uint8_t saved_rgb_mode = 0;
static uint8_t saved_rgb_hue = 0;
static uint8_t saved_rgb_sat = 0;
static uint8_t saved_rgb_val = 0;
static bool saved_rgb_state = false;
static bool rgb_settings_saved = false;

// clang-format off
// https://docs.qmk.fm/keycodes
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_84(
     KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_TOG,
     KC_GRV,   KC_EXLM, KC_LBRC, CST_LCRLY, KC_LPRN, KC_PERC, KC_ASTR, KC_AMPR, KC_RPRN, CST_RCRLY, KC_RBRC,KC_MINS,KC_EQL,CTL_B,KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_COLON,  KC_AT, KC_HASH,  KC_BSLS,            KC_PGDN,
     KC_BACKSPACE,  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,            KC_ENT,      KC_HOME,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,     KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,           CTL_G,  KC_UP,    KC_END,
     KC_LCTL,  TG(MAC_FN), KC_LCMMD,                               KC_SPC,                                 VIM_ESC,TG(MAC_FN),KC_ROPTN,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_ansi_84(
     _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  RGB_TOG,
     _______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,          RGB_VAI,
     _______,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     VIM_I,     VIM_O,     KC_P,     _______,  _______,  _______,            RGB_VAD,
     _______,  VIM_A,     VIM_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,  KC_K,     KC_L,     KC_COLON,  _______,            _______,            RGB_RMOD,
     _______,            KC_Z,  KC_X,     VIM_C,     KC_V,     KC_B,     KC_N,     KC_M,     _______,  _______,  _______,            _______,  _______,  RGB_MOD,
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______, _______,  _______),




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


// Save current RGB settings
void save_rgb_settings(void) {
    if (!rgb_settings_saved) {
        saved_rgb_mode = rgb_matrix_get_mode();
        saved_rgb_hue = rgb_matrix_get_hue();
        saved_rgb_sat = rgb_matrix_get_sat();
        saved_rgb_val = rgb_matrix_get_val();
        saved_rgb_state = rgb_matrix_is_enabled();
        rgb_settings_saved = true;
    }
}

// Restore saved RGB settings
void restore_rgb_settings(void) {
    if (rgb_settings_saved) {
        if (saved_rgb_state) {
            rgb_matrix_enable();
            rgb_matrix_mode(saved_rgb_mode);
            rgb_matrix_sethsv(saved_rgb_hue, saved_rgb_sat, saved_rgb_val);
        } else {
            rgb_matrix_disable();
        }
        rgb_settings_saved = false;
    }
}

// Set all keys to bright red (function layer)
void set_all_keys_red(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(0, 255, 255);  // Bright red (H=0, S=255, V=255)
}

// Set all keys to white (vim normal mode)
void set_all_keys_white(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(0, 0, 255);  // White (H=0, S=0, V=255)
}

// Layer state callback
layer_state_t layer_state_set_user(layer_state_t state) {
    bool new_is_mac_fn_layer = layer_state_cmp(state, MAC_FN);

    if (new_is_mac_fn_layer != is_mac_fn_layer) {
        is_mac_fn_layer = new_is_mac_fn_layer;

        if (is_mac_fn_layer) {
            // Entering MAC_FN layer - save current settings and set appropriate color
            save_rgb_settings();
            if (vim_mode_active) {
                set_all_keys_white();  // Vim normal mode = white
            } else {
                set_all_keys_red();    // Regular function layer = red
            }
        } else {
            // Exiting MAC_FN layer - restore previous settings and reset vim mode
            restore_rgb_settings();
            vim_mode_active = false;  // Reset vim mode when leaving layer
        }
    }

    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_shift_keys(keycode, record)) { return false; }

    // If we're in MAC_FN layer, intercept RGB commands to only affect base layer
    if (is_mac_fn_layer) {
        switch (keycode) {
            case RGB_TOG:
            case RGB_MOD:
            case RGB_RMOD:
            case RGB_VAI:
            case RGB_VAD:
            case RGB_HUI:
            case RGB_HUD:
            case RGB_SAI:
            case RGB_SAD:
            case RGB_SPI:
            case RGB_SPD:
                if (record->event.pressed) {
                    // Process the RGB command for the saved settings
                    if (rgb_settings_saved) {
                        switch (keycode) {
                            case RGB_TOG:
                                saved_rgb_state = !saved_rgb_state;
                                break;
                            case RGB_MOD:
                                saved_rgb_mode = (saved_rgb_mode + 1) % RGB_MATRIX_EFFECT_MAX;
                                break;
                            case RGB_RMOD:
                                saved_rgb_mode = (saved_rgb_mode - 1 + RGB_MATRIX_EFFECT_MAX) % RGB_MATRIX_EFFECT_MAX;
                                break;
                            case RGB_VAI:
                                saved_rgb_val = (saved_rgb_val + 8 > 255) ? 255 : saved_rgb_val + 8;
                                break;
                            case RGB_VAD:
                                saved_rgb_val = (saved_rgb_val - 8 < 0) ? 0 : saved_rgb_val - 8;
                                break;
                            case RGB_HUI:
                                saved_rgb_hue = (saved_rgb_hue + 8) % 256;
                                break;
                            case RGB_HUD:
                                saved_rgb_hue = (saved_rgb_hue - 8 + 256) % 256;
                                break;
                            case RGB_SAI:
                                saved_rgb_sat = (saved_rgb_sat + 8 > 255) ? 255 : saved_rgb_sat + 8;
                                break;
                            case RGB_SAD:
                                saved_rgb_sat = (saved_rgb_sat - 8 < 0) ? 0 : saved_rgb_sat - 8;
                                break;
                        }
                    }
                }
                return false; // Don't process the RGB command normally
        }
    }

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

        case CST_LCRLY:
            if (record->event.pressed) {
                SEND_STRING("{");
            }
            return false;

        case CST_RCRLY:
            if (record->event.pressed) {
                SEND_STRING("}");
            }
            return false;

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

        // Vim-specific keycodes
        case VIM_ESC:
            if (record->event.pressed) {
                tap_code(KC_ESC);  // Send ESC
                vim_mode_active = true;  // Mark that we're entering vim normal mode
                layer_on(MAC_FN);  // Switch to MAC_FN layer (QWERTY for normal mode)
            }
            return false;

        case VIM_A:
            if (record->event.pressed) {
                if (vim_mode_active) {  // Only switch back to colemak if in vim mode
                    if (get_mods() & MOD_MASK_SHIFT) {
                        // Shift is held, send 'A' (insert at end of line)
                        tap_code16(S(KC_A));
                    } else {
                        // No shift, send 'a' (insert after cursor)
                        tap_code(KC_A);
                    }
                    layer_off(MAC_FN);  // Switch back to MAC_BASE layer (Colemak DH for insert mode)
                } else {
                    // Regular function layer behavior - just send the key
                    if (get_mods() & MOD_MASK_SHIFT) {
                        tap_code16(S(KC_A));
                    } else {
                        tap_code(KC_A);
                    }
                }
            }
            return false;

        case VIM_I:
            if (record->event.pressed) {
                if (vim_mode_active) {  // Only switch back to colemak if in vim mode
                    if (get_mods() & MOD_MASK_SHIFT) {
                        // Shift is held, send 'I' (insert at beginning of line)
                        tap_code16(S(KC_I));
                    } else {
                        // No shift, send 'i' (insert before cursor)
                        tap_code(KC_I);
                    }
                    layer_off(MAC_FN);  // Switch back to MAC_BASE layer (Colemak DH for insert mode)
                } else {
                    // Regular function layer behavior - just send the key
                    if (get_mods() & MOD_MASK_SHIFT) {
                        tap_code16(S(KC_I));
                    } else {
                        tap_code(KC_I);
                    }
                }
            }
            return false;

        case VIM_O:
            if (record->event.pressed) {
                if (vim_mode_active) {  // Only switch back to colemak if in vim mode
                    if (get_mods() & MOD_MASK_SHIFT) {
                        // Shift is held, send 'O' (open line above)
                        tap_code16(S(KC_O));
                    } else {
                        // No shift, send 'o' (open line below)
                        tap_code(KC_O);
                    }
                    layer_off(MAC_FN);  // Switch back to MAC_BASE layer (Colemak DH for insert mode)
                } else {
                    // Regular function layer behavior - just send the key
                    if (get_mods() & MOD_MASK_SHIFT) {
                        tap_code16(S(KC_O));
                    } else {
                        tap_code(KC_O);
                    }
                }
            }
            return false;

        case VIM_C:
            if (record->event.pressed) {
                if (vim_mode_active) {  // Only switch back to colemak if in vim mode
                    tap_code(KC_C);  // Send 'c'
                    layer_off(MAC_FN);  // Switch back to MAC_BASE layer (Colemak DH for insert mode)
                } else {
                    // Regular function layer behavior - just send the key
                    tap_code(KC_C);
                }
            }
            return false;

        case VIM_S:
            if (record->event.pressed) {
                if (vim_mode_active) {  // Only switch back to colemak if in vim mode
                    tap_code(KC_S);  // Send 's'
                    layer_off(MAC_FN);  // Switch back to MAC_BASE layer (Colemak DH for insert mode)
                } else {
                    // Regular function layer behavior - just send the key
                    tap_code(KC_S);
                }
            }
            return false;

        case VIM_R:
            if (record->event.pressed) {
                if (vim_mode_active) {  // Only switch back to colemak if in vim mode
                    tap_code(KC_R);  // Send 'r'
                    layer_off(MAC_FN);  // Switch back to MAC_BASE layer (Colemak DH for insert mode)
                } else {
                    // Regular function layer behavior - just send the key
                    tap_code(KC_R);
                }
            }
            return false;
    }

    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
