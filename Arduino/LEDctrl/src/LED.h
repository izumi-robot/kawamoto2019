/**
 * @file LED.h
 * @brief LED操作用のクラス定義
 * @version 1.0
 */

// 2重includeを防ぐ
// マクロについて http://flat-leon.hatenablog.com/entry/cpp_preprocessor
#pragma once

// Arduinoの基本機能を使うために必要
#include <Arduino.h>

/**
 * @brief LED操作用のクラス
 * @note
 *  C++のclassについては
 *  - https://qiita.com/rinse_/items/09b67da4d16488ebea23
 *  - https://qiita.com/yumetodo/items/b0ff58617f2733d4ffa1
 *  を参照
 */
class LED {
private: // Pythonにのっとってプライベート変数は _ で開始
    //! LEDがつながっているピン番号
    uint8_t _pin;
    //! LEDのオン/オフ状態
    bool _state;

public:
    /**
     * @brief Construct a new LED object
     * @param pin LEDのピン番号
     */
    LED(uint8_t pin);

    /**
     * @brief Construct a new LED object
     * @param pin LEDのピン番号
     * @param state LEDの状態(trueでオン、falseでオフ)
     */
    LED(uint8_t pin, bool state);

    /**
     * @brief LEDのセットアップ
     */
    void setup();

    /**
     * @brief LEDのピン番号を取得
     * @return uint8_t LEDのピン番号
     */
    uint8_t get_pin();

    /**
     * @brief LEDの状態を取得
     * @return true オン
     * @return false オフ
     */
    bool get_state();

    /**
     * @brief LEDの状態を設定
     * @param state trueでオン、falseでオフ
     */
    void set_state(bool state);

    /**
     * @brief LEDの状態を切り替える
     * @note set_state(!get_state())と同じ
     */
    void toggle();

    /**
     * @brief LEDをオンにする
     * @note set_state(true)と同じ
     */
    void on();

    /**
     * @brief LEDをオフにする
     * @note set_state(false)と同じ
     */
    void off();
};
