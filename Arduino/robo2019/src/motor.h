/**
 * @file motor2.h
 * @brief Daisen MCB操作用のクラス定義
 * @version 0.1
 * @date 2021-03-04
 */

#pragma once

#ifdef ARDUINO

#include <Print.h>
#include "vec2d.h"

/**
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

/**
 * @brief MCB操作用のクラス
 * @details モーターの配置についてはREADMEを参照
 */
class Motor
{
public: // static functions
    /**
     * @brief パワー設定用の文字列を取得する
     * @param[out] dst パワー設定用の文字列
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @return uint8_t 書き込んだ文字数
     * @note dstには少なくとも6文字を格納する容量が必要。容量チェックは行っていないため、注意すること。
     */
    static uint8_t power_str(char *dst, uint8_t pin, int8_t power);

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

private: // variables
    //! モーターのパワー
    int8_t _powers[4];
    //! MCBがつながっているシリアルポート
    Print &_port;

private:
    /**
     * @brief パワー更新用
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @return true=>MCBに文字を流すべき
     */
    bool _update(uint8_t pin, int8_t power);

public:
    /**
     * @brief Construct a new Motor object
     * @note シリアルポートがSerialであるものとして初期化
     */
    Motor() : _powers{0, 0, 0, 0}, _port(Serial) {}
    /**
     * @brief Construct a new Motor object
     * @param serial MCBがつながっているシリアルポート
     */
    Motor(HardwareSerial& serial) : _powers{0, 0, 0, 0}, _port(serial) {}

    /** @brief 停止させる */
    void stop();

    /**
     * @brief モーターのパワーを取得する
     * @param[in] pin モーターのピン番号
     * @return int8_t モーターのパワー
     */
    inline int8_t get_power(uint8_t pin) const;

    /**
     * @brief モーターのパワーの文字列表示を取得する
     * @param[out] dst 結果の文字列を保存するポインター
     * @param[in] pin モーターのピン番号
     */
    inline uint8_t get_power_str(char *dst, uint8_t pin);

    /**
     * @brief モーターのパワーの文字列表示を取得する
     * @param[out] dst 結果の文字列の保存先
     * @param[in] pin モーターのピン番号
     */
    inline void get_power_str(String *dst, uint8_t pin);

    /**
     * @brief モーターのパワーの文字列表示を取得する
     * @param[in] pin モーターのピン番号
     * @return String 結果の文字列
     */
    inline String get_power_str(uint8_t pin) const;

    /**
     * @brief モーター1つのパワーを設定する
     * @param[in] pin 設定するモーターのピン番号
     * @param[in] power 設定するモーターのパワー
     */
    void set_one_motor(uint8_t pin, int8_t power);

    /**
     * @brief モーター全てのパワーを設定する
     * @param[in] m1 ピン番号1のモーターに設定するパワー
     * @param[in] m2 ピン番号2のモーターに設定するパワー
     * @param[in] m3 ピン番号3のモーターに設定するパワー
     * @param[in] m4 ピン番号4のモーターに設定するパワー
     */
    void set_all_motors(int8_t a, int8_t b, int8_t c, int8_t d);

    /**
     * @brief 機体が平行移動移動するように速度ベクトルを設定する
     * @param[in] vx ベクトルのx成分
     * @param[in] vy ベクトルのy成分
     * @details 座標系の定義はREADMEを参照
     */
    void set_velocity(const double &vx, const double &vy);

    /**
     * @brief 機体が平行移動移動するように速度ベクトルを設定する
     * @param[in] vel 設定するベクトル
     * @details 座標系の定義はREADMEを参照
     */
    inline void set_velocity(const robo::V2_double &vel);

    /**
     * @brief 左輪と右輪でわけてパワーを設定する
     * @param[in] left 左輪のパワー
     * @param[in] right 右輪のパワー
     * @details 左輪、右輪の定義はREADMEを参照
     */
    inline void set_left_right(int8_t left, int8_t right);

    /**
     * @brief 方向と速さで機体の平行移動のベクトルを設定する
     * @param[in] dir ベクトルの方向(ラジアン)
     * @param[in] speed 速さ
     * @details 方向についてはREADMEを参照
     */
    inline void set_dir_and_speed(const double &dir, int8_t speed);

    /**
     * @brief 機体が回転するようにパワーを設定する
     * @param[in] clockwise 回転の方向(時計回りかどうか)
     * @param[in] speed 回転速度
     */
    void set_rotate(bool clockwise, int8_t speed);

    uint8_t info(char *dst) {
        if (dst == NULL) return 0;
        char *ptr = dst;
        for (uint8_t pin = 1; pin <= 4; pin++) {
            ptr += get_power_str(ptr, pin);
            if (pin == 4) continue;
            strcat(ptr, ", ");
            ptr += 2;
        }
        return ptr - dst;
    }

    String info() {
        char buff[32] = "";
        info(buff);
        return String(buff);
    }
};

} // namespace robo

uint8_t robo::Motor::power_str(char *dst, uint8_t pin, int8_t power)
{
    if (dst == NULL) return 0;
    return sprintf(
        dst,
        "%1d%c%03d",
        pin,
        power < 0 ? 'F' : 'R',
        abs(power)
    );
}

void robo::Motor::power_str(String *dst, uint8_t pin, int8_t power)
{
    char buffer[8] = "";
    robo::Motor::power_str(buffer, pin, power);
    *dst = String(buffer);
}

String robo::Motor::power_str(uint8_t pin, int8_t power)
{
    char buffer[8] = "";
    robo::Motor::power_str(buffer, pin, power);
    return String(buffer);
}

bool robo::Motor::_update(uint8_t pin, int8_t power)
{
    int8_t &dst_power = _powers[pin - 1];
    if (dst_power == power) return false;
    dst_power = power;
    return true;
}

void robo::Motor::stop()
{
    _port.print("1F000\n2F000\n3F000\n4F000\n");
    memset(_powers, 0, 4);
}

int8_t robo::Motor::get_power(uint8_t pin) const { return _powers[pin - 1]; }

uint8_t robo::Motor::get_power_str(char *dst, uint8_t pin)
{
    return robo::Motor::power_str(dst, pin, get_power(pin));
}

void robo::Motor::get_power_str(String *dst, uint8_t pin)
{
    robo::Motor::power_str(dst, pin, get_power(pin));
}

String robo::Motor::get_power_str(uint8_t pin) const
{
    return robo::Motor::power_str(pin, get_power(pin));
}

void robo::Motor::set_one_motor(uint8_t pin, int8_t power)
{
    if (!_update(pin, power)) return;
    char buffer[8] = "";
    robo::Motor::power_str(buffer, pin, power);
    _port.println(buffer);
}

void robo::Motor::set_all_motors(int8_t m1, int8_t m2, int8_t m3, int8_t m4)
{
    char buffer[32] = "";
    char *buf_ptr = buffer;
    int8_t ps[] = { m1, m2, m3, m4 };
    for (int pin = 1; pin <= 4; pin++) {
        int8_t &p = ps[pin - 1];
        if (!_update(pin, p)) continue;
        robo::Motor::power_str(buf_ptr, pin, p);
        buf_ptr[5] = '\n';
        buf_ptr += 6;
    }
    buf_ptr[0] = '\0';
    _port.print(buffer);
}

void robo::Motor::set_velocity(const double &vx, const double &vy)
{
    static const double root2 = sqrt(2.);
    int8_t e1 = int8_t((vx + vy) / root2);
    int8_t e2 = int8_t((vx - vy) / root2);
    set_all_motors(e2, e1, e1, e2);
}

void robo::Motor::set_velocity(const robo::V2_double &vel)
{
    set_velocity(vel.x, vel.y);
}

void robo::Motor::set_left_right(int8_t left, int8_t right)
{
    set_all_motors(left, right, left, right);
}

void robo::Motor::set_dir_and_speed(const double &dir, int8_t speed)
{
    set_velocity(speed * cos(dir), speed * sin(dir));
}

void robo::Motor::set_rotate(bool clockwise, int8_t speed)
{
    int8_t d = clockwise ? 1 : -1;
    set_left_right(speed * d, -speed * d);
}

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif  /* ARDUINO */