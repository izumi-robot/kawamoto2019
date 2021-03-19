/**
 * @file openmv.h
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

/** @brief OpenMV関連の機能をまとめたもの */
namespace openmv {
    /** @brief ボールのカメラ視点の座標を表すエイリアス */
    using Position = robo::Vector2D<uint16_t>;

    const Position center{90, 70};

    class Frame {
    public:
        using PosPtr = Position *;
        Position *ball_pos;
        Position *y_goal_pos;
        Position *b_goal_pos;

        #define INIT_POS(_name_) _name_ ## _pos(new Position(_name_ ## _x, _name_ ## _y))
        Frame(
            uint16_t ball_x, uint16_t ball_y,
            uint16_t y_goal_x, uint16_t y_goal_y,
            uint16_t b_goal_x, uint16_t b_goal_y
        ) : INIT_POS(ball), INIT_POS(y_goal), INIT_POS(b_goal) {}
        #undef INIT_POS

        Frame(Position *ball_p, Position *y_goal_p, Position *b_goal_p)
        : ball_pos(ball_p), y_goal_pos(y_goal_p), b_goal_pos(b_goal_p) {}
        ~Frame() {
            #define DELETE(_name_) if (_name_ ## _pos != NULL) delete _name_ ## _pos;
            DELETE(ball)
            DELETE(y_goal)
            DELETE(b_goal)
            #undef DELETE
        }
        uint8_t to_string(char *dst) {
            if (dst == NULL) return 0;
            char *ptr = dst;
            #define WRITE_LABEL(_name_) ptr += sprintf_P(ptr, PSTR(#_name_ " pos: "));
            #define WRITE_POS(_name_) if (_name_ ## _pos != NULL) ptr += _name_ ## _pos->to_string(ptr);
            #define WRITE(_name_) WRITE_LABEL(_name_) WRITE_POS(_name_) NEWLINE
            #define NEWLINE *(ptr++) = '\n';
            WRITE(ball)
            WRITE(y_goal)
            WRITE(b_goal)
            #undef WRITE_LABEL
            #undef WRITE_POS
            #undef WRITE
            #undef NEWLINE
            *ptr = '\0';
            return ptr - dst;
        }
    };

    class Reader {
    private:
        TwoWire &_wire;

        void pass_data(uint8_t size) {
            for (uint8_t i = 0; i < size; i++) _wire.read();
        }

        uint16_t read_2byte() {
            return _wire.read() | (_wire.read() << 8);
        }

        Position* read_pos() {
            constexpr uint16_t default_value = 0xffff;
            uint16_t x = read_2byte();
            uint16_t y = read_2byte();
            if (x == default_value && y == default_value) return NULL;
            return new Position(x, y);
        }
    public:
        uint8_t address;

        Reader(uint8_t addr) : _wire(Wire),address(addr) {}
        Reader(uint8_t addr, TwoWire &wire) : _wire(wire), address(addr) {}

        void setup() { _wire.begin(); }

        Frame* read_frame() {
            constexpr uint8_t req_size = 3 * 4;
            uint8_t res_size = _wire.requestFrom(address, req_size);
            if (res_size != req_size) {
                pass_data(res_size);
                return NULL;
            }
            Position *ball_pos = read_pos();
            Position *y_goal_pos = read_pos();
            Position *b_goal_pos = read_pos();
            _wire.beginTransmission(address);
            _wire.write(1);
            _wire.endTransmission();
            if (ball_pos == NULL && y_goal_pos == NULL && b_goal_pos == NULL) return NULL;
            return new Frame(ball_pos, y_goal_pos, b_goal_pos);
        }
    };

    constexpr float pos2dir(const Position &pos) {
        return atan2(
            -float(pos.x) + 90, // = -(pos.x - 90)
            float(pos.y) - 70
        );
    }
} // namespace openmv

} // namespace robo

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */