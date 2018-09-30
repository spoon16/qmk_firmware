#include QMK_KEYBOARD_H

enum layer_names {
  L_DEFAULT = 0,
  L_FN,
};

enum function_codes {
  F_SPCFN = 0,
  F_FN,
};

enum tapdance_codes {
  TD_SS = 0,
};

enum tapdance_tap_counts {
  TD_SINGLE_TAP = 1,
  TD_DOUBLE_TAP = 2,
  TD_TRIPLE_TAP = 3,
};

void tap(uint16_t code)
{
  register_code(code);
  unregister_code(code);
};

const uint16_t fn_actions[] = {
    // L1 when held, SPC when tapped
    [F_SPCFN] = ACTION_LAYER_TAP_KEY(L_FN, KC_SPC),
    [F_FN] = ACTION_LAYER_TOGGLE(L_FN),
};

// screenshot tap dance
void td_fn_ss(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
        case TD_SINGLE_TAP:
            // selection, clipboard
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            tap(KC_4);
            unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_TAP:
            // selection, file in ~/Desktop
            register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            tap(KC_4);
            unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            break;
        case TD_TRIPLE_TAP:
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
#define KC_LFN KC_FN1
#define KC_SS TD(TD_SS)
#define NOKEY KC_NO
#define __________ KC_TRNS

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_DEFAULT] = LAYOUT( \
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_GRV,     KC_BSPC,    KC_DEL, \
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_SS, \
        KC_LCTL,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_NUHS,    KC_ENT,     KC_PGUP, \
        KC_LSFT,    NOKEY,      KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,    KC_UP,      KC_PGDN, \
        KC_MEH,     KC_LALT,    KC_LGUI,    KC_SPCFN,   KC_LFN,     NOKEY,      NOKEY,      KC_LEFT,    KC_DOWN,    KC_RGHT \
    ),
    [L_FN] = LAYOUT( \
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, KC_SPC, __________, __________, \
        __________, __________, __________, __________, __________, __________, __________, __________, __________, __________ \
    ),
};
