/**
 * @file echo.h
 * @brief 超音波センサーHC-SR04操作用のクラス定義
 */

#ifndef ROBO2019_ECHO_H
#define ROBO2019_ECHO_H

#ifdef ARDUINO

#include "util.h"

namespace robo {

/**
 * @brief 超音波センサーHC-SR04操作用のクラス
 */
class EchoSensor : public robo::Sensor
{
public: // variables
    //! Echo pinの番号
    const int input_pin;
    //! Trig pinの番号
    const int order_pin;

public: // functions
    /**
     * @brief コンストラクタ
     * @param[in] i Echo pinの番号
     * @param[in] o Trig pinの番号
     */
    EchoSensor(int i, int o)
        : input_pin(i), order_pin(o) {}

    void setup() override;
    int read() override;
};

void EchoSensor::setup()
{
    pinMode(input_pin, INPUT);
    pinMode(order_pin, OUTPUT);
}

int EchoSensor::read() {
    digitalWrite(order_pin, LOW);
    delayMicroseconds(10);
    digitalWrite(order_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(order_pin, LOW);
    // pulseIn(pin, state, timeout)
    return pulseIn(input_pin, HIGH) / 59;
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_ECHO_H */