#ifndef DISABLE_RGB_MATRIX_CYCLE_DOWN_UP
RGB_MATRIX_EFFECT(SPOON16_MAC)

RGB_MATRIX_EFFECT(SPOON16_WIN)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool SPOON16_MAC(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB underglow_rgb = {0x26, 0x26, 0x26};
    RGB modifier_rgb = {0xAA, 0xAA, 0xAA};
    RGB finger_rgb = {0xFF, 0xFF, 0xFF};
    RGB keylight_rgb = {0, 0, 0};

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, modifier_rgb.r, modifier_rgb.g, modifier_rgb.b);
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, underglow_rgb.r, underglow_rgb.g, underglow_rgb.b);
        } else {
            rgb_matrix_set_color(i, keylight_rgb.r, keylight_rgb.g, keylight_rgb.b);
        }
    }

    rgb_matrix_set_color(54, finger_rgb.r, finger_rgb.g, finger_rgb.b);
    rgb_matrix_set_color(57, finger_rgb.r, finger_rgb.g, finger_rgb.b);

    return led_max < DRIVER_LED_TOTAL;
}

bool SPOON16_WIN(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB underglow_rgb = {0x00, 0x00, 0x26};
    RGB modifier_rgb = {0xAA, 0xAA, 0xAA};
    RGB finger_rgb = {0x00, 0x00, 0xFF};
    RGB keylight_rgb = {0, 0, 0};

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, modifier_rgb.r, modifier_rgb.g, modifier_rgb.b);
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, underglow_rgb.r, underglow_rgb.g, underglow_rgb.b);
        } else {
            rgb_matrix_set_color(i, keylight_rgb.r, keylight_rgb.g, keylight_rgb.b);
        }
    }

    rgb_matrix_set_color(54, finger_rgb.r, finger_rgb.g, finger_rgb.b);
    rgb_matrix_set_color(57, finger_rgb.r, finger_rgb.g, finger_rgb.b);

    return led_max < DRIVER_LED_TOTAL;
}

#endif
#endif
