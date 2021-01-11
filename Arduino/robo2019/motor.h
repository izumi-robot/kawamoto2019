#ifndef ROBO_MOTOR_H
#define ROBO_MOTOR_H

#ifdef ARDUINO

#include "util.h"
#include "vec2d.h"

namespace robo
{

class Motor
{
private: // internal-types
    class Get
    {
    private:
        Motor *_motor;
    public:
        Get(): _motor(NULL) {}
        Get(Motor *motor): _motor(motor) {}

        inline int8_t one_motor(uint8_t) const;
        String power_str(uint8_t pin) const;
        String info() const;
    };

    class Set
    {
    private:
        Motor *_motor;
    public:
        Set(): _motor(NULL) {}
        Set(Motor *motor): _motor(motor) {}

        bool one_motor(uint8_t, int8_t);
        bool all_motors(int8_t, int8_t, int8_t, int8_t);
        bool velocity(const double &, const double &);
        bool velocity(const robo::V2_double &);
        bool left_right(int8_t, int8_t);
        bool direction_and_speed(const double &, int8_t);
        bool rotate(bool, int8_t);
        // TODO: 旋回運動
        // void circular(const double &rotate_vel, const int &vel=100);
    };

public:
    enum Pin { pin1; pin2}

private: // variables
    static Motor _singleton;
    static int8_t powers[];
    int8_t _powers[4];
public:
    Get get;
    Set set;

private: // functions
    Motor()
        : _powers{ 0, 0, 0, 0 }, get(this), set(this) {}
    Motor(const Motor&)
        : _powers{ 0, 0, 0, 0 }, get(this), set(this) {}
    ~Motor() {}
    Motor& operator=(const Motor&) { return *this; }

public:
    static Motor& instance();
    static String power_str(int pin, int8_t power);

    void stop();
    void setup();
}; // class Motor

int8_t Motor::powers[] = { 0, 0, 0, 0 };
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
    if (power < -100 || p == power || 100 < power) { return false; }
    String dest = Motor::power_str(pin, power);
    Serial1.println(dest);
    p = power;
    return true;
}

bool Motor::Set::all_motors(int8_t a, int8_t b, int8_t c, int8_t d)
{
    return one_motor(1, a) && one_motor(2, b) && one_motor(3, c) && one_motor(4, d);
}

bool Motor::Set::velocity(const double &vx, const double &vy)
{
    double root2 = sqrt(2.);
    int8_t fl = (int8_t)((vy - vx) / root2), fr = (int8_t)((vy + vx) / root2);
    return all_motors(fr, fl, fl, fr);
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
    double x = speed * sin(direction);
    double y = speed * cos(direction);
    return velocity(x, y);
}

bool Motor::Set::rotate(bool clockwise, int8_t speed)
{
    int8_t d = clockwise ? 1 : -1;
    return left_right(speed * d, -speed * d);
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

void Motor::stop()
{
    this->set.all_motors(0, 0, 0, 0);
}

void Motor::setup()
{
    Serial1.begin(19200);
    this->stop();
}

Motor &motor = Motor::instance();

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_MOTOR_H */