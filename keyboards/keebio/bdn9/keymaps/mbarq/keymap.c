/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
#include QMK_KEYBOARD_H

enum custom_keycodes {
    ADD_VAL = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ADD_VAL:
            if (record->event.pressed) {
                //when keycode ADD_VAL is pressed,
                //goes home, adds value ".1" and enters it
                SEND_STRING(SS_TAP(X_END)"+.1" SS_TAP(X_ENTER));
            } else {
                //when keycode ADD_VAL is released
            }
            break;
        }
        return true;
    };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [0] = LAYOUT(
        KC_MUTE, KC_HOME, KC_MPLY,
        MO(1)  , KC_UP, RGB_MOD,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            SEND_STRING(SS_TAP(X_END)"+.1" SS_TAP(X_ENTER) SS_TAP(X_ENTER));
        } else {
            SEND_STRING(SS_TAP(X_END)"-.1" SS_TAP(X_ENTER) SS_TAP(X_ENTER));
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
