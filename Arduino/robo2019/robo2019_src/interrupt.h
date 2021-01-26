/**
 * @file interrupt.h
 * @brief 割り込み用のクラス定義
 */

#ifndef ROBO_INTERRUPT_H
#define ROBO_INTERRUPT_H

#ifdef ARDUINO

// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

namespace robo {

#define I_TMP template<int in_pin, int mode=RISING>
#define INTERRUPT Interrupt<in_pin, mode>


/**
 * @brief 割り込み用のテンプレートクラス
 * @tparam in_pin 割り込みで監視するピン番号
 */
I_TMP class Interrupt {
private:
    /**
     * @brief 状態記憶用の変数
     * @details 割り込みが発生するごとにtrue/falseが切り替わる
     */
    static volatile bool _state;
    //! シングルトンオブジェクト
    static Interrupt _singleton;

    // シングルトン化
    /**
     * @brief デフォルトコンストラクタ
     */
    Interrupt() {}
    /**
     * @brief コピーコンストラクタ
     */
    Interrupt(const Interrupt &) {}
    /**
     * @brief デストラクタ
     */
    ~Interrupt() {}
    /**
     * コピー代入
     */
    Interrupt& operator=(const Interrupt &) {}

    /**
     * @fn void callback()
     * @brief 割り込み発生時に呼び出される
     * @details _stateを切り替える
     */
    static void callback();

public:
    /**
     * @fn Interrupt& instance()
     * @brief シングルトンオブジェクトを返す
     * @return シングルトンオブジェクトの参照
     */
    static Interrupt& instance();
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

I_TMP void INTERRUPT::callback()
{
    INTERRUPT::_state = !INTERRUPT::_state;
}

I_TMP INTERRUPT& INTERRUPT::instance()
{
    return INTERRUPT::_singleton;
}

I_TMP void INTERRUPT::setup()
{
    pinMode(in_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(in_pin), callback, mode);
}

I_TMP bool INTERRUPT::state()
{
    return _state;
}

I_TMP bool INTERRUPT::changed()
{
    static bool pre_state;
    bool ans = pre_state != _state;
    pre_state = _state;
    return ans;
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_INTERRUPT_H */