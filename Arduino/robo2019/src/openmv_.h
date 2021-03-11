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

    uint16_t read_data_size() {
        uint8_t size = _wire.requestFrom(address, (uint8_t)2);
        if (size == 2) { return read_2byte(); }
        return 0;
    }

    CameraPos read_pos(
        const CameraPos &pos_on_fail = CameraPos{0, 0},
        uint16_t default_value = 0xffff
    ) {
        uint16_t data_size = read_data_size();
        uint8_t size = _wire.requestFrom(address, data_size);
        if (size != 4) return pos_on_fail;
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return (x != default_value || y != default_value) ? Vector2{x, y} : pos_on_fail;
    }
};

} // namespace robo

void robo::I2CReader::setup() { _wire.begin(); }

uint16_t robo::I2CReader::pass_data()
{
    uint16_t data_size = _wire.available();
    for (uint16_t i = 0; i < data_size; ++i) { _wire.read(); }
    return data_size;
}

uint16_t robo::I2CReader::read_2byte()
{
    return _wire.read() | ((uint16_t)_wire.read() << 8);
}

uint16_t robo::I2CReader::read_data_size(uint8_t addr)
{
    _wire.requestFrom(addr, (uint8_t)2);
    if (_wire.available() == 2) {
        return _wire.read();
    }
    return 0;
}

bool robo::I2CReader::read_data(char *buff, uint8_t addr, uint16_t data_size)
{
    if (buff == NULL) return false;

    Wire.requestFrom(addr, data_size);
    if (Wire.available() < data_size) return false;

    for (uint16_t i = 0; i < data_size; ++i) {
        buff[i] = Wire.read();
    }
    return true;
}

bool robo::I2CReader::read_data(uint8_t *buff, uint8_t addr, uint16_t data_size)
{
    if (buff == NULL) return false;

    Wire.requestFrom(addr, data_size);
    if (Wire.available() < data_size) return false;

    for (uint16_t i = 0; i < data_size; ++i) {
        buff[i] = Wire.read();
    }
    return true;
}

uint16_t robo::I2CReaderWithAddr::read_data_size()
{
    return I2CReader::read_data_size(address);
}

bool robo::I2CReaderWithAddr::read_data(char *buff, uint16_t data_size)
{
    return I2CReader::read_data(buff, address, data_size);
}

bool robo::I2CReaderWithAddr::read_data(uint8_t *buff, uint16_t data_size)
{
    return I2CReader::read_data(buff, address, data_size);
}

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */