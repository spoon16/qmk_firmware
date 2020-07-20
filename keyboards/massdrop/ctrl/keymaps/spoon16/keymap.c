#include "keymap.h"

static uint16_t idle_timer;             // Idle LED timeout timer
static uint8_t idle_second_counter;     // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t key_event_counter;       // This counter is used to check if any keys are being held

static const char * sendstring_commands[] = {
    "git init ",
    "git clone ",
    "git config --global ",
    "git add ",
    "git diff ",
    "git reset ",
    "git rebase ",
    "git branch -b \"",
    "git checkout ",
    "git merge ",
    "git remote add ",
    "git fetch ",
    "git pull ",
    "git push ",
    "git commit ",
    "git status ",
    "git log ",
};

#ifndef ___________
    #define ___________ KC_TRNS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    [DEFAULT] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SLCK, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                            KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    */
    [L_MAC] = LAYOUT(
        //ESC      , F1         , F2         , F3         , F4         , F5         , F6         , F7         , F8         , F9         , F10        , F11        , F12                     , PSCR       , SLCK       , PAUS       ,
        KC_ESC     , KC_F1      , KC_F2      , KC_F3      , KC_F4      , KC_F5      , KC_F6      , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11     , KC_F12                  , NOKEY      , NOKEY      , TG(L_KYBRD), \
        //GRV      , 1          , 2          , 3          , 4          , 5          , 6          , 7          , 8          , 9          , 0          , MINS       , EQL        , BSPC       , INS        , HOME       , PGUP       ,
        KC_GRV     , KC_1       , KC_2       , KC_3       , KC_4       , KC_5       , KC_6       , KC_7       , KC_8       , KC_9       , KC_0       , KC_MINS    , KC_EQL     , KC_BSPC    , KC_INS     , KC_HOME    , KC_PGUP    , \
        //TAB      , Q          , W          , E          , R          , T          , Y          , U          , I          , O          , P          , LBRC       , RBRC       , BSLS       , DEL        , END        , PGDN       ,
        KC_TAB     , KC_Q       , KC_W       , KC_E       , KC_R       , KC_T       , KC_Y       , KC_U       , KC_I       , KC_O       , KC_P       , KC_LBRC    , KC_RBRC    , KC_BSLS    , KC_DEL     , KC_END     , KC_PGDN    , \
        //CAPS     , A          , W          , D          , F          , G          , H          , J          , K          , L          , SCLN       , QUOT       , ENT        ,
        KC_LCTL    , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       , KC_H       , KC_J       , KC_K       , KC_L       , KC_SCLN    , KC_QUOT    , KC_ENT     ,                                                     \
        //LSFT     , Z          , X          , C          , V          , B          , N          , M          , COMM       , DOT        , SLSH       , RSFT                                              , UP         ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_N       , KC_M       , KC_COMM    , KC_DOT     , KC_SLSH    , KC_RSFT                                           , KC_UP      ,              \
        //LCTL     , LALT       , GUI        , SPC                                                                         , RGUI       , RALT       , RCTL                                 , LEFT       , DOWN       , RGHT
        KC_MEH     , KC_LALT    , KC_LGUI    , KC_SPC                                                                      , NOKEY      , KC_RALT    , KC_RCTL    , TG(L_WIN)               , KC_LEFT    , KC_DOWN    , KC_RGHT      \
    ),
    [L_WIN] = LAYOUT(
        //ESC      , F1         , F2         , F3         , F4         , F5         , F6         , F7         , F8         , F9         , F10        , F11        , F12                     , PSCR       , SLCK       , PAUS       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________             , ___________, ___________, ___________, \
        //GRV      , 1          , 2          , 3          , 4          , 5          , 6          , 7          , 8          , 9          , 0          , MINS       , EQL        , BSPC       , INS        , HOME       , PGUP       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, \
        //TAB      , Q          , W          , E          , R          , T          , Y          , U          , I          , O          , P          , LBRC       , RBRC       , BSLS       , DEL        , END        , PGDN       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, \
        //CAPS     , A          , W          , D          , F          , G          , H          , J          , K          , L          , SCLN       , QUOT       , ENT        ,
        KC_LGUI    , ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________,                                                     \
        //LSFT     , Z          , X          , C          , V          , B          , N          , M          , COMM       , DOT        , SLSH       , RSFT                                              , UP         ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________                                       , ___________,              \
        //LCTL     , LALT       , GUI        , SPC                                                                         , RGUI       , RALT       , RCTL                                 , LEFT       , DOWN       , RGHT
        ___________, ___________, KC_LCTL    , ___________                                                                 , ___________, ___________, ___________, ___________             , ___________, ___________, ___________  \
    ),
    [L_KYBRD] = LAYOUT(
        //ESC      , F1         , F2         , F3         , F4         , F5         , F6         , F7         , F8         , F9         , F10        , F11        , F12                     , PSCR       , SLCK       , PAUS       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________             , ___________, ___________, ___________, \
        //GRV      , 1          , 2          , 3          , 4          , 5          , 6          , 7          , 8          , 9          , 0          , MINS       , EQL        , BSPC       , INS        , HOME       , PGUP       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, \
        //TAB      , Q          , W          , E          , R          , T          , Y          , U          , I          , O          , P          , LBRC       , RBRC       , BSLS       , DEL        , END        , PGDN       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, MD_BOOT    , RGB_TOG    , ___________, \
        //CAPS     , A          , W          , D          , F          , G          , H          , J          , K          , L          , SCLN       , QUOT       , ENT        ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________,                                                     \
        //LSFT     , Z          , X          , C          , V          , B          , N          , M          , COMM       , DOT        , SLSH       , RSFT                                              , UP         ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________                                       , ___________,              \
        //LCTL     , LALT       , GUI        , SPC                                                                         , RGUI       , RALT       , RCTL                                 , LEFT       , DOWN       , RGHT
        ___________, ___________, ___________, ___________                                                                 , ___________, ___________, ___________, ___________             , ___________, ___________, ___________  \
    ),
};

#undef ___________
#define ___________ {0, 0, 0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [L_KYBRD] = {
        //ESC      , F1         , F2         , F3         , F4         , F5         , F6         , F7         , F8         , F9         , F10        , F11        , F12                     , PSCR       , SLCK       , PAUS       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________             , RED        , RED        , RED        , \
        //GRV      , 1          , 2          , 3          , 4          , 5          , 6          , 7          , 8          , 9          , 0          , MINS       , EQL        , BSPC       , INS        , HOME       , PGUP       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, RED        , RED        , RED        , \
        //TAB      , Q          , W          , E          , R          , T          , Y          , U          , I          , O          , P          , LBRC       , RBRC       , BSLS       , DEL        , END        , PGDN       ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, RED        , RED        , RED        , \
        //CAPS     , A          , W          , D          , F          , G          , H          , J          , K          , L          , SCLN       , QUOT       , ENT        ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________,                                                     \
        //LSFT     , Z          , X          , C          , V          , B          , N          , M          , COMM       , DOT        , SLSH       , RSFT                                              , UP         ,
        ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________, ___________                                       , RED        ,              \
        //LCTL     , LALT       , GUI        , SPC                                                                         , RGUI       , RALT       , RCTL                                 , LEFT       , DOWN       , RGHT
        ___________, ___________, ___________, ___________                                                                 , ___________, ___________, ___________, ___________             , RED        , RED        , RED          \
    },
};

#undef ___________
#define ___________ KC_TRNS

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    idle_second_counter = 0;                            // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                              // Counter to determine if keys are being held, neutral at 0.
    rgb_time_out_seconds = RGB_DEFAULT_TIME_OUT;        // RGB timeout initialized to its default configure in keymap.h
    rgb_time_out_enable = false;                        // Disable RGB timeout by default. Enable using toggle key.
    rgb_time_out_user_value = false;                    // Has to have the same initial value as rgb_time_out_enable.
    rgb_enabled_flag = true;                            // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
    rgb_time_out_fast_mode_enabled = false;             // RGB timeout fast mode disabled initially.
    rgb_time_out_saved_flag = rgb_matrix_get_flags();   // Save RGB matrix state for when keyboard comes back from ide.
};

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=false;
    debug_keyboard=false;
    debug_mouse=false;

    rgb_matrix_enable();

#ifdef CONSOLE_ENABLE
    dprintf("---\n");
    dprint("  layer_state: ");
    layer_debug();
    dprint("\n");
    dprint("  default_layer_state: ");
    default_layer_debug();
    dprint("\n");
    dprintf("  layer mac: %s\n", layer_state_cmp(layer_state, L_MAC) ? "true" : "false");
    dprintf("  layer win: %s\n", layer_state_cmp(layer_state, L_WIN) ? "true" : "false");
    dprintf("  layer kybrd: %s\n", layer_state_cmp(layer_state, L_KYBRD) ? "true" : "false");
#endif
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    if(rgb_time_out_enable && rgb_enabled_flag) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= rgb_time_out_seconds) {
            rgb_time_out_saved_flag = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            rgb_enabled_flag = false;
            idle_second_counter = 0;
        }
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Increment key event counter for every press and decrement for every release.
    if (record->event.pressed) {
        key_event_counter++;
    } else {
        key_event_counter--;
    }

    if (rgb_time_out_enable) {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!rgb_enabled_flag) {
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_flags(rgb_time_out_saved_flag);
            rgb_enabled_flag = true;
        }
    }

    static uint32_t key_timer;

    switch (keycode) {
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }

		    return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case RGB_TOG:
                rgb_time_out_enable = rgb_time_out_user_value;
                rgb_matrix_set_color_all(0, 0, 0);
                return false;
            // ======================================================== CUSTOM KEYCOADS BELOW ========================================================
            case COPY_ALL:
                // Selects all and text and copy
                SEND_STRING(SS_LCTRL("ac"));
                return false;
            case SEL_CPY:
                // Select word under cursor and copy. Double mouse click then ctrl+c
                tap_code16(KC_BTN1);
                tap_code16(KC_BTN1);
                tap_code16(C(KC_C));
                return false;
            case G_INIT ... G_LOG:
                send_string_with_delay(sendstring_commands[keycode - G_INIT], 5);
                return false;
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_SPOON16_MAC);

    if (layer_state_cmp(state, L_WIN)) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_SPOON16_WIN);
#ifdef CONSOLE_ENABLE
    dprintf("L_WIN RGB MATRIX\n");
#endif
    }

    return state;
}

void set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void rgb_matrix_indicators_user(void) {
    if (g_suspend_state || disable_layer_color ||
        rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return;
        }

    if (layer_state_cmp(layer_state, L_KYBRD)) {
        set_layer_color(L_KYBRD);
    }
}
