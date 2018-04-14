/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "whitefox.h"

LEADER_EXTERNS();

enum layer_names {
    DEFAULT,
    FUNCTION,
    SPACEFN
};

enum function_codes {
    F_SPCFN = 0,
    F_L1,
};

enum tapdance_codes {
  TD_SS = 0,
  L_SPACEFN,
};

enum macro_keycodes {
    M_HW = SAFE_RANGE,
    M_ELLEE,
};

enum tapdance_tap_counts {
  SINGLE_TAP = 1,
  DOUBLE_TAP = 2,
  TRIPLE_TAP = 3,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case M_HW:
                SEND_STRING("Hello, world!");
                return false;
            case M_ELLEE:
                SEND_STRING("Ellee ");
                return false;
        }
    }
    return true;
};

void tap(uint16_t code)
{
  register_code(code);
  unregister_code(code);
};

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_TWO_KEYS(KC_H, KC_W) {
      SEND_STRING("Hello, world!");
    }
  }
};

const uint16_t fn_actions[] = {
    // L1 when held, SPC when tapped
    [F_SPCFN] = ACTION_LAYER_TAP_KEY(2 , KC_SPC),
    [F_L1] = ACTION_LAYER_TOGGLE(FUNCTION),
};

// screenshot tap dance
void td_fn_ss(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case SINGLE_TAP:
            // selection, clipboard
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            tap(KC_4);
            unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            break;
        case DOUBLE_TAP:
            // selection, file in ~/Desktop
            register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            tap(KC_4);
            unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            break;
        default:
            // full screen, file in ~/Desktop
            register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            tap(KC_3);
            unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            break;
    }
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SS] = ACTION_TAP_DANCE_FN(td_fn_ss),
};

#define KC_SPCFN KC_FN0
#define KC_L1 KC_FN1
#define KC_SS TD(TD_SS)
#define NOKEY KC_NO
#define __________ KC_TRNS

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = KEYMAP( \
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_GRV,     KC_BSLS,    KC_SS, \
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSPC,    KC_DEL, \
        KC_LCTL,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_NUHS,    KC_ENT,     KC_HOME, \
        KC_LSFT,    NOKEY,      KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,    KC_UP,      KC_END, \
        KC_MEH,     KC_LALT,    KC_LGUI,    KC_SPCFN,   KC_L1,      KC_NO,      NOKEY,      KC_LEFT,    KC_DOWN,    KC_RGHT \
    ),
    [FUNCTION] = KEYMAP( \
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, KC_LEAD,    M_ELLEE,    __________, __________, __________, __________ \
    ),
    [SPACEFN] = KEYMAP( \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, KC_SPC, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________ \
    ),
};