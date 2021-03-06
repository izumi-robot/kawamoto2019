/**
 * @file motor.h
 * @brief Daisen MCB 操作用のクラス定義
 */

#pragma once

#ifndef ROBO2019_MOTOR_H
#define ROBO2019_MOTOR_H

#ifdef ARDUINO

#include "util.h"
#include "vec2d.h"

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

class Motor;
class MotorGetter;
class MotorSetter;

/**
 * @brief MCB操作用のシングルトンクラス
 * @details モーターの配置についてはREADMEを参照
 */
class Motor : public robo::SingletonBase<Motor>
{
    friend robo::SingletonBase<Motor>;
    friend MotorGetter;
    friend MotorSetter;

private: // variables
    //! モーターのパワー
    int8_t _powers[4];

public:
    //! 情報取得用の関数群
    MotorGetter &get;
    //! 更新用の関数群
    MotorSetter &set;

private: // functions
    Motor();

public:
    /**
     * @brief パワー設定用の文字列を取得する
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @return パワー設定用の文字列
     * @details 例えば、`power_str(1, -10)`は"1R010"を返す。実際のパワーは変更されない点に注意。
     */
    static String power_str(uint8_t, int8_t);
    /**
     * @brief パワー設定用の文字列を取得する
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @param[out] dst パワー設定用の文字列
     */
    static void power_str(String *, uint8_t, int8_t);
    /**
     * @brief パワー設定用の文字列を取得する
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @param[out] dst パワー設定用の文字列
     * @note dstには少なくとも6文字を格納する容量が必要。容量チェックは行っていないため、注意すること。
     */
    static void power_str(char *, uint8_t, int8_t);

    /**
     * @brief モーターのセットアップを行う
     * @note 全体のsetup内で呼ばないと他の機能が使えない。
     */
    void setup();

}; // class Motor

/**
 * @brief モーターの情報を取得するクラス
 */
class MotorGetter : public robo::SingletonBase<MotorGetter>
{
    friend robo::SingletonBase<MotorGetter>;
private:
    //! 情報取得元のインスタンス
    Motor *_motor;

    MotorGetter();

public:
    /**
     * @brief pinのモーターのパワーを取得する
     * @param[in] pin モーターのピン番号
     * @return int8_t モーターのパワー
     */
    inline int8_t one_motor(uint8_t) const;
    /**
     * @brief pinのモーターのパワーを取得する
     * @param[in] pin モーターのピン番号
     * @param[out] dst モーターのパワー
     */
    inline void one_motor(int8_t *, uint8_t);

    /**
     * @brief パワー設定用の文字列を取得する
     * @param[in] pin モーターのピン番号
     * @return String mcbに流す用の文字列
     */
    String power_str(uint8_t) const;
    /**
     * @brief パワー設定用の文字列を取得する
     * @param[in] pin モーターのピン番号
     * @param[out] dst mcbに流す用の文字列
     */
    void power_str(String *, uint8_t);
    /**
     * @brief パワー設定用の文字列を取得する
     * @param[in] pin モーターのピン番号
     * @param[out] dst mcbに流す用の文字列
     * @note dstには少なくとも6文字を格納する容量が必要。容量チェックは行っていないため、注意すること。
     */
    void power_str(char *, uint8_t);

    /**
     * @brief パワー設定用の文字列のセットを取得
     * @return "[power_str(1), power_str(2), power_str(3), power_str(4)]"
     * @note デバッグ用
     */
    String info() const;
    /**
     * @brief パワー設定用の文字列のセットを取得
     * @param[out] dst "[power_str(1), power_str(2), power_str(3), power_str(4)]"
     * @note デバッグ用
     */
    void info(String *);
    /**
     * @brief パワー設定用の文字列のセットを取得
     * @param[out] dst "[power_str(1), power_str(2), power_str(3), power_str(4)]"
     * @note デバッグ用。dstは少なくとも29文字の容量が必要となる。容量チェックは行っていないため、注意すること。
     */
    void info(char *);
};

/**
 * @brief モーターのパワーを設定するための関数群
 */
class MotorSetter : public robo::SingletonBase<MotorSetter>
{
    friend robo::SingletonBase<MotorSetter>;
private:
    //! 情報取得元のインスタンス
    Motor *_motor;

    MotorSetter();

    /**
     * @brief パワー更新用
     * @param[in] pin モーターのピン番号
     * @param[in] power モーターのパワー
     * @return trueならMCBに文字を流すべき
     */
    bool _update(uint8_t, int8_t);

public:
    /**
     * @brief ピン番号pinのモーターのパワーをpowerに設定
     * @param[in] pin ピン番号
     * @param[in] power パワー
     */
    void one_motor(uint8_t, int8_t);

    /**
     * @brief 全てのモーターのパワーを一気に設定する
     * @param[in] a ピン番号1に設定するモーターのパワー
     * @param[in] b ピン番号2に設定するパワー
     * @param[in] c 番号3のパワー
     * @param[in] d 4番のパワー
     */
    void all_motors(int8_t, int8_t, int8_t, int8_t);

    /**
     * @brief ベクトル(vx, vy)が機体の速度ベクトルになるようにモーターのパワーを設定する
     * @param[in] vx ベクトルのx成分
     * @param[in] vy ベクトルのy成分
     * @details x成分は機体の正面方向が正方向、y成分は機体の左方向が正方向。いつもの座標系を反時計回りに90度回転させた感じ。こうすることで機体の正面が0度になり、方向の管理が楽になる。
     */
    void velocity(const double &, const double &);
    /**
     * @brief velocity(v.x, v.y)のショートカット
     * @param[in] v 設定する速度ベクトル
     * @sa bool velocity(const double vx, const double vy)
     * @details V2_doubleについてはvec2d.hを参照。
     */
    inline void velocity(const robo::V2_double &);

    /**
     * @brief 左輪(ピン番号1, 3)、右輪(ピン番号2, 4)でパワーを設定する
     * @param[in] left  左輪のパワー
     * @param[in] right 右輪のパワー
     */
    inline void left_right(int8_t, int8_t);

    /**
     * @brief 与えられた方向と速さに機体の速度を設定する
     * @param[in] direction 方向(ラジアン)
     * @param[in] speed 速さ
     * @details 方向は機体の正面を0とし、反時計回りが正回転。PIまたは-PIで真後ろを指す。
     */
    inline void direction_and_speed(const double &, int8_t);

    /**
     * @brief 回転するようにパワーを設定する。
     * @param[in] clockwise 時計回りに回転するかどうか
     * @param[in] speed 回転の速さ
     */
    void rotate(bool, int8_t);

    /**
     * @brief 停止させる
     */
    inline void stop();
    // TODO: 旋回運動
    // void circular(const double &rotate_vel, const int &vel=100);
};

/*
 * Motor
 */

Motor::Motor() : get(MotorGetter::instance()), set(MotorSetter::instance()) {}

String Motor::power_str(uint8_t pin, int8_t power)
{
    char p_str[8] = "";
    Motor::power_str(p_str, pin, power);
    return String(p_str);
}
void Motor::power_str(String *dst, uint8_t pin, int8_t power)
{
    char p_str[8] = "";
    Motor::power_str(p_str, pin, power);
    *dst = String(p_str);
}
void Motor::power_str(char *dst, uint8_t pin, int8_t power)
{
    // R: 正転?
    if (dst == NULL) return;
    sprintf(
        dst, "%1d%c%03d",
        pin, power < 0 ? 'F' : 'R', abs(power)
    );
}

void Motor::setup()
{
    Serial2.begin(19200);
    set.stop();
}

/*
 * MotorGetter
 */

MotorGetter::MotorGetter() : _motor(&Motor::instance()) {}

int8_t MotorGetter::one_motor(uint8_t pin) const
{
    return _motor->_powers[pin - 1];
}
void MotorGetter::one_motor(int8_t *dst, uint8_t pin)
{
    if (dst == NULL) return;
    *dst = _motor->_powers[pin - 1];
}

String MotorGetter::power_str(uint8_t pin) const
{
    int8_t power = one_motor(pin);
    return Motor::power_str(pin, power);
}
void MotorGetter::power_str(String *dst, uint8_t pin)
{
    if (dst == NULL) return;
    int8_t power = one_motor(pin);
    Motor::power_str(dst, pin, power);
}
void MotorGetter::power_str(char *dst, uint8_t pin)
{
    if (dst == NULL) return;
    int8_t power = one_motor(pin);
    Motor::power_str(dst, pin, power);
}

String MotorGetter::info() const
{
    String info_str = "[";
    for (uint8_t i = 1; i <= 4; i++)
    {
        info_str += this->power_str(i);
        if (i != 4) { info_str += ", "; }
    }
    return info_str + "]";
}
void MotorGetter::info(String *dst)
{
    if (dst == NULL) return;
    String info_str = *dst;
    info_str = "[";
    for (uint8_t i = 1; i <= 4; i++)
    {
        info_str += this->power_str(i);
        if (i != 4) { info_str += ", "; }
    }
    info_str += "]";
}
void MotorGetter::info(char *dst)
{
    if (dst == NULL) return;
    char *ptr = dst;
    ptr[0] = '[';
    ptr += 1;
    for (int8_t i = 1; i <= 4; i++)
    {
        this->power_str(ptr, i);
        ptr += 5;
        if (i < 4)
        {
            strcpy(ptr, ", ");
            ptr += 2;
        }
    }
    ptr[0] = ']';
    ptr[1] = '\0';
}

/*
 * MotorSetter
 */

MotorSetter::MotorSetter() : _motor(&Motor::instance()) {}

bool MotorSetter::_update(uint8_t pin, int8_t power)
{
    int8_t &c_power = _motor->_powers[pin - 1];
    if (c_power == power) return false;
    c_power = power;
    return true;
}

void MotorSetter::one_motor(uint8_t pin, int8_t power)
{
    if (!_update(pin, power)) return;
    char p_str[8] = "";
    Motor::power_str(p_str, pin, power);
    Serial2.println(p_str);
}

void MotorSetter::all_motors(int8_t a, int8_t b, int8_t c, int8_t d)
{
    int8_t new_powers[] = {a, b, c, d};
    char dst[64] = "";
    char *ptr = dst;
    for (uint8_t i = 0; i < 4; ++i)
    {
        const int8_t n_power = new_powers[i]; // new
        if (!_update(i + 1, n_power)) continue;
        Motor::power_str(ptr, i + 1, n_power);
        ptr[5] = '\n';
        ptr += 5;
    }
    ptr[1] = '\0';
    Serial2.print(dst);
}

void MotorSetter::velocity(const double &vx, const double &vy)
{
    double root2 = sqrt(2.);
    int8_t e1 = int8_t((vx + vy) / root2);
    int8_t e2 = int8_t((vx - vy) / root2);
    all_motors(e2, e1, e1, e2);
}
void MotorSetter::velocity(const robo::V2_double &v)
{
    velocity(v.x, v.y);
}

void MotorSetter::left_right(int8_t left, int8_t right)
{
    all_motors(left, right, left, right);
}

void MotorSetter::direction_and_speed(const double &direction, int8_t speed)
{
    velocity(speed * cos(direction), speed * sin(direction));
}

void MotorSetter::rotate(bool clockwise, int8_t speed)
{
    int8_t d = clockwise ? 1 : -1;
    left_right(speed * d, -speed * d);
}

void MotorSetter::stop()
{
    all_motors(0, 0, 0, 0);
}

//! Motorのシングルトンオブジェクトへの参照
Motor &motor = Motor::instance();

} // namespace robo

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */

#endif /* ROBO2019_MOTOR_H */