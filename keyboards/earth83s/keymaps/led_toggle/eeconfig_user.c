#include "eeconfig_user.h"
#include <stdint.h>
#include "eeprom.h"

// EEPROMのカスタム保存アドレス（例: 32以降の空き領域）
#define USER_EEPROM_ADDR 32

void eeconfig_update_user(uint8_t val) {
    eeprom_update_byte((uint8_t*)USER_EEPROM_ADDR, val);
}

uint8_t eeconfig_read_user(void) {
    return eeprom_read_byte((uint8_t*)USER_EEPROM_ADDR);
}