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

/** @brief OpenMV関連の機能をまとめたもの */
namespace openmv {
    /** @brief ボールのカメラ視点の座標を表すエイリアス */
    using Position = robo::Vector2D<uint16_t>;

    /** @brief オブジェクトの種類を表現する列挙型 */
    enum class Kind : uint8_t { ball, yellow_goal, blue_goal };

    /** @brief カメラから見たオブジェクトの情報 */
    struct ObjInfo {
    public:
        //! オブジェクトの種類
        const Kind kind;
        //! オブジェクトの位置
        const Position pos;

        ObjInfo() = delete;
        /** @brief 種類と座標を指定して初期化 */
        ObjInfo(Kind kind, const uint16_t &x, const uint16_t &y) : kind(kind), pos(x, y) {}
        /** @brief 種類と座標を指定して初期化 */
        ObjInfo(Kind kind, const Position &pos) : kind(kind), pos(pos) {}

        /**
         * @brief 文字列表現を取得する
         * @param[out] dst 文字列を書き込むバッファ
         * @return uint8_t 書き込んだ文字数
         * @note バッファオーバーランに注意。容量は30文字あると安心。
         */
        uint8_t to_string(char *dst);
    };

    class Reader {
    private:
        TwoWire &_wire;

        uint16_t read_2byte() {
            return _wire.read() | (_wire.read() << 8);
        }
    public:
        uint8_t address;

        Reader(uint8_t addr) : _wire(Wire),address(addr) {}
        Reader(uint8_t addr, TwoWire &wire) : _wire(wire), address(addr) {}

        ObjInfo* read_obj() {
            uint8_t size = _wire.requestFrom(address, 5);
            if (size != 5) return NULL;
            Kind kind = static_cast<Kind>(_wire.read());
            uint16_t x = read_2byte();
            uint16_t y = read_2byte();
            return new ObjInfo(kind, x, y);
        }
    };
} // namespace openmv

} // namespace robo

uint8_t robo::openmv::ObjInfo::to_string(char *dst) {
    if (dst == NULL) return;
    return sprintf(dst, "%s: (%u, %u)", (
        kind == Kind::ball ? "ball"
        : kind == Kind::yellow_goal ? "yellow goal"
        : kind == Kind::blue_goal ? "blue goal"
        : "unknown kind"
    ), x, y);
}

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */