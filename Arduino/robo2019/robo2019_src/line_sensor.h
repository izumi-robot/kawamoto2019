/**
 * @file line_sensor.h
 * @brief ラインセンサー操作用のクラス定義
 */

#ifndef ROBO2019_LINE_SENSOR_H
#define ROBO2019_LINE_SENSOR_H

#ifdef ARDUINO

#include "util.h"

namespace robo {

/**
 * @brief ラインセンサー操作用のクラス
 */
class LineSensor : public robo::Sensor
{
public:
    //! センサーの値がこれ以上であれば白
    static int white_border;

    //! センサーのピン
    const uint8_t in_pin;

    /**
     * @fb bool iswhite(int c)
     * @brief 値が白色か判別する
     * @param[in] c 検査する値
     * @return 白色かどうか
     */
    static bool iswhite(int);

    LineSensor() = delete;
    /**
     * @brief コンストラクタ
     * @param[in] i ラインセンサーのピン番号
     */
    LineSensor(uint8_t i) : in_pin(i) {}

    inline void setup();
    inline int read();
};

unsigned int LineSensor::white_border = 600;

bool LineSensor::iswhite(unsigned int c)
{
    return c >= white_border;
}

void LineSensor::setup()
{
    pinMode(in_pin, INPUT);
}

int LineSensor::read()
{
    return analogRead(in_pin);
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_LINE_SENSOR_H */