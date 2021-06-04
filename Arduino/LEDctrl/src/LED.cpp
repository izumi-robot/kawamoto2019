/**
 * @file LED.cpp
 * @brief LED.hの実装
 * @version 1.0
 */

// includeについて https://qiita.com/agate-pris/items/1b29726935f0b6e75768
#include "LED.h"

// 以降はclass LEDのメソッド実装

// ::はスコープ解決演算子
// あと、メンバ初期化子リストも確認
LED::LED(uint8_t pin) : _pin(pin), _state(false) {}

LED::LED(uint8_t pin, bool state) : _pin(pin), _state(state) {}

void LED::setup() {
    pinMode(_pin, OUTPUT);
}

uint8_t LED::get_pin() {
    return _pin;
}

bool LED::get_state() {
    return _state;
}

void LED::set_state(bool state) {
    _state = state;
    // digitalWriteの第2引数については「C++ 3項演算」で検索
    digitalWrite(_pin, _state ? HIGH : LOW);
}

void LED::toggle() {
    set_state(!_state);
}

void LED::on() {
    set_state(true);
}

void LED::off() {
    set_state(false);
}
