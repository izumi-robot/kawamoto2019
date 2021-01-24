/**
 * @file motor.h
 * @brief Daisen MCB 操作用のクラス
 */


#ifndef ROBO_MOTOR_H
#define ROBO_MOTOR_H

#ifdef ARDUINO

#include "util.h"
#include "vec2d.h"

namespace robo
{

/**
 * @brief モーター操作用のシングルトンクラス
 * @details ダイセンのMCBを操作するためのシングルトンクラス。モーターの配置についてはREADMEを参照。
 */
class Motor
{
private: // 内部型

    /**
     * @brief モーターの情報を取得する関数群
     */
    class Get
    {
    private:
        //! 情報取得元のインスタンス
        Motor *_motor;
    public:

        /**
         * @brief デフォルトのコンストラクタ
         */
        Get() : _motor(NULL) {}

        /**
         * @brief 引数のポインタで初期化
         */
        Get(Motor *motor) : _motor(motor) {}

        /**
         * @fn int8_t one_motor(uint8_t pin) const
         * @brief pinのモーターのパワーを取得する
         * @param[in] pin モーターのピン番号
         * @return int8_t モーターのパワー
         */
        inline int8_t one_motor(uint8_t) const;
        
        /**
         * @fn String power_str(uint8_t pin) const
         * @brief mcbに流す用の文字列を取得する
         * @param[in] pin モーターのピン番号
         * @return String mcbに流す用の文字列
         * @example power_str(1)
         */
        String power_str(uint8_t) const;
        // 
        String info() const;
    };

    /**
     * @brief モーターのパワーを設定するための関数群
     */
    class Set
    {
    private:
        Motor *_motor;
    public:
        Set() : _motor(NULL) {}
        Set(Motor *motor) : _motor(motor) {}

        bool one_motor(uint8_t, int8_t);
        bool all_motors(int8_t, int8_t, int8_t, int8_t);
        bool velocity(const double &, const double &);
        bool velocity(const robo::V2_double &);
        bool left_right(int8_t, int8_t);
        bool direction_and_speed(const double &, int8_t);
        bool rotate(bool, int8_t);
        bool stop();
        // TODO: 旋回運動
        // void circular(const double &rotate_vel, const int &vel=100);
    };

private: // variables
    static Motor _singleton;
    int8_t _powers[4];
public:
    Get get;
    Set set;

private: // functions
    // シングルトンにする上で欠かせない部分
    /**
     * @brief コンストラクタ
     */
    Motor() : _powers{ 0, 0, 0, 0 }, get(this), set(this) {}
    /**
     * @brief コピーコンストラクタ
     */
    Motor(const Motor &) : _powers{ 0, 0, 0, 0 }, get(this), set(this) {}
    /**
     * @brief デストラクタ
     */
    ~Motor() {}
    /**
     * @brief コピー代入
     */
    Motor& operator=(const Motor &) { return *this; }

public:
    static Motor& instance();
    static String power_str(int, int8_t);

    void stop();
    void setup();
}; // class Motor

Motor Motor::_singleton;

inline int8_t Motor::Get::one_motor(uint8_t pin) const
{
    return _motor->_powers[(pin - 1) & 3];
}

String Motor::Get::power_str(uint8_t pin) const
{
    int8_t power = this->one_motor(pin);
    return Motor::power_str(pin, power);
}

String Motor::Get::info() const
{
    String info_str = "[";
    for (uint8_t i = 1; i <= 4; i++) {
        info_str += String(i) + ": " + this->power_str(i);
        if (i != 4) { info_str += ", "; }
    }
    return info_str + "]";
}

bool Motor::Set::one_motor(uint8_t pin, int8_t power)
{
    int8_t &p = _motor->_powers[pin-1];
    if (power < -100 || abs(p - power) < 5 || 100 < power) { return false; }
    String dest = Motor::power_str(pin, power);
    Serial2.println(dest);
    p = power;
    return true;
}

bool Motor::Set::all_motors(int8_t a, int8_t b, int8_t c, int8_t d)
{
    return one_motor(1, a) & one_motor(2, b) & one_motor(3, c) & one_motor(4, d);
}

bool Motor::Set::velocity(const double &vx, const double &vy)
{
    double root2 = sqrt(2.);
    int8_t left = (int8_t)((vx + vy) / root2), right = (int8_t)((vx - vy) / root2);
    return all_motors(right, left, left, right);
}

bool Motor::Set::velocity(const robo::V2_double &vel)
{
    return velocity(vel.x, vel.y);
}

bool Motor::Set::left_right(int8_t left, int8_t right)
{
    return all_motors(left, right, left, right);
}

bool Motor::Set::direction_and_speed(const double &direction, int8_t speed)
{
    return velocity(speed * cos(direction), speed * sin(direction));
}

bool Motor::Set::rotate(bool clockwise, int8_t speed)
{
    int8_t d = clockwise ? 1 : -1;
    return left_right(speed * d, -speed * d);
}

bool Motor::Set::stop()
{
    return all_motors(0, 0, 0, 0);
}

Motor& Motor::instance()
{
    return Motor::_singleton;
}

String Motor::power_str(int pin, int8_t power)
{
    // R: front?
    String dir_s = power < 0 ? "F" : "R";
    String power_s = String(abs(power));
    power_s = robo::string::rjust(power_s, 3, '0');
    return String(pin) + dir_s + power_s;
}

// void Motor::stop()
// {
//     this->set.all_motors(0, 0, 0, 0);
// }

void Motor::setup()
{
    Serial2.begin(19200);
    this->set.stop();
}

Motor &motor = Motor::instance();

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_MOTOR_H */