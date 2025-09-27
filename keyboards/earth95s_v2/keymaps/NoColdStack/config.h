#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

//rp2040ボードで起動時にコールドスタックする事象に対する対応
#define SPLIT_USB_TIMEOUT 5000 // default 2000
#define SPLIT_USB_TIMEOUT_POLL 25 // default 10