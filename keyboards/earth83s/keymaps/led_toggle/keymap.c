// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "eeconfig_user.h"

// ▼ カスタムキーコード定義
enum custom_keycodes {
    TOGGLE_LED_MODE = SAFE_RANGE,
};

// ▼ RGB設定保存用変数定義
uint8_t saved_mode = 0;
HSV saved_hsv = { .h = 0, .s = 0, .v = 0 };

// ▼ モード管理用フラグ
bool led_deco_mode = false;  // false = インジケーター, true = 装飾

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
                 KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL ,

                 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_INT3, KC_BSPC,
                 KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT,
    			 LT(4, KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,
    	         KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_INT1, KC_UP,   KC_RSFT,
    			 KC_LCTL, KC_LGUI, KC_LALT, KC_INT5, KC_DEL, KC_SPC,          KC_ENT,  KC_BSPC, KC_INT4, KC_INT2, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	
    [1] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        		 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	
    [2] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        		 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
		
    [3] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        		 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
	
		
    [4] = LAYOUT(
                 KC_TRNS, TO(0)  , TO(1)  , TO(2)  , TO(3)  , TO(4)  ,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

         TOGGLE_LED_MODE, RGB_MOD, RGB_RMOD,KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 RGB_TOG, RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        		 KC_TRNS, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    			 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

// ▼ レイヤー変更時のLED処理
layer_state_t layer_state_set_user(layer_state_t state) {
    if (led_deco_mode) {
        return state;  // 装飾モード中は変更しない
    }

    switch (get_highest_layer(state)) {
        case 0:
            rgblight_sethsv_noeeprom(127, 255, 60);  // ブルー
            break;
        case 1:
            rgblight_sethsv_noeeprom(0, 255, 60);    // レッド
            break;
        case 2:
            rgblight_sethsv_noeeprom(85, 255, 60);   // グリーン
            break;
        case 3:
            rgblight_sethsv_noeeprom(191, 255, 60);  // パープル
            break;
        case 4:
            rgblight_sethsv_noeeprom(0, 0, 60);      // ホワイト
            break;
        default:
            rgblight_sethsv_noeeprom(0, 0, 0);       // OFF
            break;
    }
    return state;
}

// ▼ 起動時のLED復元処理
void keyboard_post_init_user(void) {
	// eeconfig_init();                 // EEPROM初期化（必要であれば）
    rgblight_enable();              // EEPROMから設定を復元
	led_deco_mode = (eeconfig_read_user() != 0);
	
    if (!led_deco_mode) {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);  // アニメーション停止
        layer_state_set_user(layer_state);                   // レイヤーに応じた色に設定
    }
}

// ▼ キー押下時処理（LED復帰・モード切替）
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case TOGGLE_LED_MODE:
                led_deco_mode = !led_deco_mode;
        	
        		// EEPROMにモード状態を保存
			    eeconfig_update_user(led_deco_mode ? 1 : 0);
                
                if (!rgblight_is_enabled()) {
                    rgblight_enable();
                }

                if (led_deco_mode) {
                	rgblight_mode_noeeprom(saved_mode);       // 前回のmodeに戻す
                    rgblight_sethsv_noeeprom(saved_hsv.h, saved_hsv.s, saved_hsv.v);  // 前回の色
                } else {
                	// Decoモードの設定を保存
                    saved_mode = rgblight_get_mode();
                    saved_hsv = rgblight_get_hsv();
                	
                	if (saved_hsv.v == 0) {
					    saved_hsv.v = 128;
					}
                	
                	// インジケーター用に静的モードに切り替えて色反映
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    layer_state_set_user(layer_state);
                }
                return false;
        }
    }
    return true;
}
