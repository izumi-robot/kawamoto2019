/**
 * @file openmv_.h
 * @brief I2C通信の読み取り用のクラス定義
 */

#pragma once

#ifdef ARDUINO

#include <Wire.h>

#include "vec2d.h"

/**
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

namespace openmv {
    using Position = robo::Vector2D<uint16_t>;

    enum class Kind : uint8_t { ball, yellow_goal, blue_goal };

    struct ObjInfo : public Position {
    public:
    };
}

/** @brief カメラ視点でのボールの座標を表現する型 */
using CameraPos = robo::Vector2D<uint16_t>;

class OpenMV {
private:
    TwoWire &_wire;
public:
    const uint8_t address;

    OpenMV() : _wire(Wire), address(0x12) {}
    OpenMV(uint8_t addr) : _wire(Wire), address(addr) {}
    OpenMV(TwoWire &wire, uint8_t addr) : _wire(wire), address(addr) {}

    void setup() { _wire.begin(); }
    uint16_t read_2byte() { return _wire.read() | ((uint16_t)_wire.read() << 8); }

    CameraPos read_pos(const CameraPos &pos_on_fail = CameraPos{0, 0}) {
        uint16_t data_size = read_data_size();
        uint8_t size = _wire.requestFrom(address, data_size);
        if (size != 4) return pos_on_fail;
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return (x != 0xffff || y != 0xffff) ? Vector2{x, y} : pos_on_fail;
    }
};

} // namespace robo

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */