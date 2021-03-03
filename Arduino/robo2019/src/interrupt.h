/**
 * @file interrupt.h
 * @brief 割り込み用のクラス定義
 */

#ifndef ROBO2019_INTERRUPT_H
#define ROBO2019_INTERRUPT_H

#ifdef ARDUINO

#include "util.h"

// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo {

#define TMP template<int in_pin, int mode>
#define INTERRUPT Interrupt<in_pin, mode>

/**
 * @brief 割り込み用のテンプレートクラス
 * @tparam in_pin 割り込みで監視するピン番号
 */
template<int in_pin, int mode=RISING>
class Interrupt : public robo::SingletonBase<INTERRUPT>
{
private:
    /**
     * @brief 状態記憶用の変数
     * @details 割り込みが発生するごとにtrue/falseが切り替わる
     */
    static volatile bool _state;

    /**
     * @fn void callback()
     * @brief 割り込み発生時に呼び出される
     * @details _stateを切り替える
     */
    static void callback();

public:
    /**
     * @fn void setup();
     * @brief 割り込みのセットアップを行う
     * @note 全体のsetup内で呼ばないと他の機能が使えない
     */
    void setup();

    /**
     * @fn bool state()
     * @brief 現在保存されている状態を返す
     * @return _stateの値
     */
    inline bool state();

    /**
     * @fn bool changed()
     * @brief 最後の呼び出しから_stateが変化したかどうか
     * @return 変化していたらtrue
     */
    bool changed();
};

TMP volatile bool INTERRUPT::_state;

TMP void INTERRUPT::callback()
{
    INTERRUPT::_state = !INTERRUPT::_state;
}

TMP void INTERRUPT::setup()
{
    pinMode(in_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(in_pin), callback, mode);
}

TMP bool INTERRUPT::state()
{
    return _state;
}

TMP bool INTERRUPT::changed()
{
    static bool pre_state;
    bool ans = pre_state != _state;
    pre_state = _state;
    return ans;
}

#undef INTERRUPT
#undef TMP

} // namespace robo

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */

#endif /* ROBO2019_INTERRUPT_H */