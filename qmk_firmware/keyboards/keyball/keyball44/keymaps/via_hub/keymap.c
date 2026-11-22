/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "os_detection.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                       KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BSPC  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                       KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_ENT   ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                       KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
              KC_LALT  , KC_LGUI  , KC_BTN1  , LT(2,KC_SPC), LSFT_T(KC_TAB),                 RGUI_T(KC_BSPC), LT(3,KC_ENT), XXXXXXX  , XXXXXXX  , KC_RGUI
  ),

  [1] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                       _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , KC_BTN2  , KC_BTN1  , _______  ,                                       _______  , KC_BTN1  , KC_BTN2  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                       _______  , _______  , _______  , _______  , _______  , _______  ,
              _______  , _______  , _______  , _______  , _______  ,                         _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_EXLM  , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC  ,                                       KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_MINS  , KC_UNDS  , _______  ,
    _______  , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                       KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , _______  ,
    KC_F6    , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                       KC_F8    , KC_F9    , KC_F10   , KC_F11   , KC_F12   , KC_F7    ,
              _______  , _______  , _______  , _______  , _______  ,                         KC_ESC   , C(KC_SPC), _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______  , KC_TILD  , KC_EQL   , KC_BSLS  , KC_LPRN  , KC_RPRN  ,                                       _______  , KC_MUTE  , KC_VOLD  , KC_VOLU  , KC_QUOT  , _______  ,
    _______  , KC_GRV   , KC_PLUS  , KC_PIPE  , KC_LCBR  , KC_RCBR  ,                                       KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_DQUO  , _______  ,
    _______  , _______  , _______  , _______  , KC_LBRC  , KC_RBRC  ,                                       _______  , KC_BTN4  , KC_BTN5  , _______  , _______  , _______  ,
              _______  , _______  , KC_BTN2  , _______  , KC_BTN3  ,                         _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    QK_BOOT  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                       _______  , _______  , _______  , _______  , _______  , QK_BOOT  ,
    _______  , _______  , _______  , _______  , _______  , SCRL_DVI ,                                       _______  , _______  , _______  , _______  , _______  , KBC_SAVE ,
    _______  , _______  , _______  , _______  , _______  , SCRL_DVD ,                                       CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_RST  ,
              _______  , _______  , _______  , _______  , _______  ,                         _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, 2, 3, 4);
    keyball_set_scroll_mode(get_highest_layer(state) == 2);
    return state;
}

void keyboard_post_init_user(void) {
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_FREE);
}

static bool is_mac_host(void) {
    os_variant_t os = detected_host_os();
    return os == OS_MACOS || os == OS_IOS;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (is_mac_host()) {
        mouse_report.h = -mouse_report.h;
        mouse_report.v = -mouse_report.v;
    }
    return mouse_report;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
