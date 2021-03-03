/**
 * @file openmv.h
 * @brief OpenMVの情報を読み取るためのクラス定義
 */

#ifndef ROBO2019_OPENMV_H
#define ROBO2019_OPENMV_H

#ifdef ARDUINO

#include "vec2d.h"
#include "i2c.h"

/**
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

using robo::I2CReaderWithAddr;
using CameraPos = robo::Vector2D<uint16_t>;

/**
 * @brief OpenMVの読み取り用のクラス
 */
class OpenMVReader : public I2CReaderWithAddr
{
public:
    using I2CReaderWithAddr::I2CReaderWithAddr;

    /**
     * @brief ボールのOpenMV上の座標を読み取る
     * @param[in] pos_on_fail 読み取りに失敗した時に返される座標
     * @return CameraPos OpenMV上の座標
     */
    CameraPos read_pos(const CameraPos &);
};

CameraPos OpenMVReader::read_pos(const CameraPos &pos_on_fail = CameraPos{0, 0})
{
    static constexpr uint16_t default_value = (1 << 16) - 1;
    uint16_t data_size = I2CReaderWithAddr::read_data_size();
    if (data_size < 4) {
        return pos_on_fail;
    }
    delayMicroseconds(10);
    uint8_t buff[data_size];
    if (!I2CReaderWithAddr::read_data(buff, data_size)) {
        pass_data();
        return pos_on_fail;
    }
    uint16_t x = buff[0] | (buff[1] << 8);
    uint16_t y = buff[2] | (buff[3] << 8);
    return (
        (x == default_value && y == default_value)
        ? pos_on_fail
        : CameraPos{x, y}
    );
}

} // namespace robo

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */

#endif /* ROBO2019_OPENMV_H */