/**
 * @file move_info.h
 * @author Kawamoto Hironori
 * @brief モーターの移動情報を表現するクラス定義
 */

#pragma once

#include "vec2d.h"
#include "motor.h"

/**
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

/**
 * @brief モーターの移動情報を表現するクラス定義
 */
namespace move_info
{

    class MoveInfo
    {
    public:
        virtual void apply(robo::Motor &motor) = 0;
        virtual uint8_t to_string(char *dst) = 0;
        virtual String to_string() = 0;
    };

    class Stop : public MoveInfo
    {
    public:
        void apply(robo::Motor &motor) override
        {
            motor.stop();
        }

        uint8_t to_string(char *dst) override
        {
            if (dst == NULL) return 0;
            strcat_P(dst, PSTR("MoveInfo: Stop"));
            return 14; // len("MoveInfo: Stop") == 14
        }

        String to_string() override
        {
            char buffer[16] = "";
            to_string(buffer);
            return String(buffer);
        }
    };

    class Translate : public MoveInfo
    {
    private:
        robo::V2_float vec;

    public:
        Translate(const float &x, const float &y) : vec(x, y) {}
        Translate(const robo::V2_float &vec) : vec(vec) {}

        void apply(robo::Motor &motor) override
        {
            motor.set_velocity(vec);
        }

        uint8_t to_string(char *dst) override
        {
            if (dst == NULL) return 0;
            char *ptr = dst;
            strcat_P(ptr, PSTR("MoveInfo: Translate"));
            ptr += 19; // len("MoveInfo: Translate") == 19
            ptr += vec.to_string(ptr);
            return ptr - dst;
        }

        String to_string() override
        {
            char buffer[64] = "";
            to_string(buffer);
            return String(buffer);
        }
    };

    class Rotate : public MoveInfo
    {
    private:
        const bool clockwise;
        const int8_t speed;

    public:
        Rotate(const bool clockwise, const int8_t speed)
        : clockwise(clockwise), speed(speed) {}

        void apply(robo::Motor &motor) override
        {
            motor.set_rotate(clockwise, speed);
        }

        uint8_t to_string(char *dst) {
            if (dst == NULL) return 0;
            return sprintf_P(
                dst,
                PSTR("MoveInfo: Rotate(clockwise=%s, %d)"),
                clockwise ? PSTR("true") : PSTR("false"),
                speed
            );
        }

        String to_string() override
        {
            char buffer[64];
            to_string(buffer);
            return String(buffer);
        }
    };

} // namespace move_info

} // namespace robo