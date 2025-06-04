#include QMK_KEYBOARD_H
#include <stdlib.h>

#define MAX_INTERVAL_MS 300000  // 5分
#define STEP_INTERVAL_MS 1000
#define MOVE_AMOUNT 10

static uint32_t last_check = 0;
static uint32_t last_move = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A
    )
};

void matrix_scan_user(void) {
    uint32_t now = timer_read32();

    if (timer_elapsed32(last_check) < STEP_INTERVAL_MS) return;
    last_check = now;

    uint32_t elapsed = now - last_move;
    if (elapsed > MAX_INTERVAL_MS) elapsed = MAX_INTERVAL_MS;

    float probability = (float)elapsed / MAX_INTERVAL_MS;

    if ((float)rand() / RAND_MAX < probability) {
        int8_t dx = 0;
        int8_t dy = 0;

        switch (rand() % 4) {
            case 0: dx = MOVE_AMOUNT; break;
            case 1: dx = -MOVE_AMOUNT; break;
            case 2: dy = MOVE_AMOUNT; break;
            case 3: dy = -MOVE_AMOUNT; break;
        }

        // マウスレポート構造体（QMK従来型）
        report_mouse_t mouse_report = {};
        mouse_report.x = dx;
        mouse_report.y = dy;
        host_mouse_send(&mouse_report);

        // Aキーを送信（テスト用）
        // register_code(KC_A);
        // unregister_code(KC_A);

        last_move = now;
    }
}
