# motor.h

## class Motor

```C++
struct { // set
    // assert : pin = 1,2,3,4 && abs(power) <= 100
    void one_motor(uint8_t pin, int8_t power)
    {
        uint8_t i = pin - 1;
        if (powers[i] == power) {
            return;
        }
        String dest = power_str(pin, power);
        Serial1.println(dest);
        powers[i] = power;
    }

    void all_motors(int8_t a, int8_t b, int8_t c, int8_t d)
    {
        one_motor(1, a);
        one_motor(2, b);
        one_motor(3, c);
        one_motor(4, d);
    }

    void velocity(const double &vx, const double &vy)
    {
        double root2 = sqrt(2.);
        int8_t fl = (int8_t)((vy - vx) / root2), fr = (int8_t)((vy + vx) / root2);
        all_motors(fr, fl, fl, fr);
    }

    void velocity(const robo::V2_double &vel)
    {
        velocity(vel.x, vel.y);
    }

    void left_right(int8_t left, int8_t right)
    {
        all_motors(left, right, left, right);
    }

    void direction_and_speed(const double &direction, int8_t speed)
    {
        double x = speed * sin(direction);
        double y = speed * cos(direction);
        velocity(x, y);
    }

    void rotate(bool clockwise, int8_t speed=100)
    {
        int8_t d = clockwise ? 1 : -1;
        left_right(speed * d, -speed * d);
    }

    // TODO: 旋回運動
    // void circular(const double &rotate_vel, const int &vel=100);
} set;

struct { // get
    inline int8_t one_motor(uint8_t pin) const
    {
        return powers[pin - 1];
    }

    String power_str(uint8_t pin) const
    {
        return Motor::power_str(pin, powers[pin - 1]);
    }

    String info() const
    {
        String info_str = "[";
        for (uint8_t i = 1; i <= 4; i++) {
            info_str += String(i) + ": " + power_str(i);
            if (i != 4) {
                info_str += ", ";
            }
        }
        return info_str + "]";
    }
} get;
```