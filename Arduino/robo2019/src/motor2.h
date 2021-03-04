/**
 * @file motor2.h
 * @brief Daisen MCB操作用のクラス定義
 * @version 0.1
 * @date 2021-03-04
 */

#pragma once

#ifdef ARDUINO

#include "vec2d.h"

namespace robo
{

class Motor2
{
private:
    int8_t _powers[4];
    HardwareSerial& _serial;

public:
    /**
     * @brief パワー設定用の文字列を取得する
     * @param[out] dst パワー設定用の文字列
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @note dstには少なくとも6文字を格納する容量が必要。容量チェックは行っていないため、注意すること。
     */
    static void power_str(char *, uint8_t, int8_t);

    /**
     * @brief パワー設定用の文字列を取得する
     * @param[out] dst パワー設定用の文字列
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     */
    static void power_str(String *dst, uint8_t pin, int8_t power);

    /**
     * @brief パワー設定用の文字列を取得する
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @return パワー設定用の文字列
     */
    static String power_str(uint8_t pin, int8_t power);

private:
    /**
     * @brief パワー更新用
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @return true=>MCBに文字を流すべき
     */
    bool _update(uint8_t pin, int8_t power);

public:
    Motor() : _powers{0, 0, 0, 0}, _serial(Serial) {}
    Motor(HardwareSerial& port) : _powers{0, 0, 0, 0}, _serial(port) {}

    /** @brief 停止させる */
    void stop();

    /**
     * @brief モーターのセットアップを行う
     * @note 全体のsetup内で呼ばないと他の機能が使えない
     */
    void setup();

    inline int8_t get_power(uint8_t pin) const;
    inline void get_power_str(char *dst, uint8_t pin);
    inline void get_power_str(String *dst, uint8_t pin);
    inline String get_power_str(uint8_t pin) const;

    void set_one_motor(uint8_t pin, int8_t power);
    void set_all_motors(int8_t a, int8_t b, int8_t c, int8_t d);
    void set_velocity(const double &x, const double &y);
    inline void set_velocity(const robo::V2_double &vel);
    inline void set_left_right(int8_t left, int8_t right);
    inline void set_dir_and_speed(const double &dir, int8_t speed);
    void set_rotate(bool clockwise, int8_t speed);
};

}

void Motor2::power_str(char *dst, uint8_t pin, int8_t power)
{
    if (dst == NULL) return;
    sprintf(
        dst,
        "%1d%c%03d",
        pin,
        power < 0 ? 'F' : 'R'
    );
}

void Motor2::power_str(String *dst, uint8_t pin, int8_t power)
{
    char buffer[8] = "";
    Motor2::power_str(buffer, pin, power);
    *dst = String(buffer);
}

String Motor2::power_str(uint8_t pin, int8_t power)
{
    char buffer[8] = "";
    Motor2::power_str(buffer, pin, power);
    return String(buffer);
}

bool Motor2::_update(uint8_t pin, int8_t power)
{
    int8_t &dst_power = _powers[pin - 1];
    if (dst_power == power) return false;
    dst_power = power;
    return true;
}

void Motor2::stop() {
    _serial.print("1F000\n2F000\n3F000\n4F000\n");
    memset(_powers, 0, 4);
}

void Motor2::setup(unsigned long baud = 19200, byte config = SERIAL_8N1)
{
    if (!_serial) _serial.begin(baud, confing);
    stop();
}

int8_t Motor2::get_power(uint8_t pin) const { return _powers[pin]; }

void Motor2::get_power_str(char *dst, uint8_t pin)
{
    Motor2::power_str(dst, pin, get_power(pin));
}

void Motor2::get_power_str(String *dst, uint8_t pin)
{
    Motor2::power_str(dst, pin, get_power(pin));
}

String Motor2::get_power_str(uint8_t pin) const
{
    return Motor2::power_str(pin, get_power(pin));
}

void Motor2::set_one_motor(uint8_t pin, int8_t power)
{
    if (!_update(pin, power)) return;
    char buffer[8] = "";
    Motor2::power_str(buffer, pin, power);
    _serial.println(buffer);
}

void Motor2::set_all_motors(int8_t a, int8_t b, int8_t c, int8_t d)
{
    char buffer[32] = "";
    char *buf_ptr = buffer;
    int8_t ps[] = {a, b, c, d};
    for (int pin = 1; pin <= 4; pin++) {
        uint8_t &p = ps[i];
        if (!_update(i + 1, p)) continue;
        Motor2::power_str(buf_ptr, pin, p);
        buf_ptr[5] = '\n';
        buf_ptr += 6;
    }
    buf_ptr[0] = '\0';
    _serial.print(buffer);
}

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif  /* ARDUINO */