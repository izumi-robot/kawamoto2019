/**
 * @file dsrlcd.h
 * @brief ダイセンのLCD操作用の関数群
 */

#ifndef ROBO2019_DSRLCD_H
#define ROBO2019_DSRLCD_H

#ifdef ARDUINO

#include <Wire.h>
#include "util.h"

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo {

namespace dsr_lcd {

    void setup();
    void put(uint8_t, const String&);

    void setup() {
        Wire.begin();
        String n = "";
        put(1, n);
        delay(5);
        put(2, n);
    }

    void put(uint8_t line, const String &str) {
        int len = str.length();

        // 通信開始
        Wire.beginTransmission(0x16 >> 1);
        // 行選択
        Wire.write(line);
        // 文字列を書き込み
        for (int i = 0; i < 16; ++i) {
            if (i < len) {
                Wire.write(str[i]);
            } else {
                Wire.write(' ');
            }
        }
        Wire.endTransmission();
    }

} // namespace dsr_lcd

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_DSRLCD_H */