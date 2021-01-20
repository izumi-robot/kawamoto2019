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

# Interrupt

```C++
template <int in_pin>
class Interrupt
{
private:
    static volatile bool _state;
    static Interrupt _instance;

    Interrupt() {}
    Interrupt(const Interrupt&) {}
    ~Interrupt() {}
    Interrupt& operator=(const Interrupt&) {}

    static void callback() { _state = !_state; }

public:
    static Interrupt& instance()
    {
        return _instance;
    }

    static void setup()
    {
        pinMode(in_pin, INPUT);
        attachInterrupt(digitalPinToInterrupt(in_pin), callback, RISING);
    }

    static inline bool state() { return _state; }

    static bool changed()
    {
        static bool pre_state;
        bool ans = pre_state != _state;
        pre_state = _state;
        return ans;
    }
};

template <int in_pin> volatile bool Interrupt<in_pin>::_state = false;
template <int in_pin> Interrupt<in_pin> Interrupt<in_pin>::_instance;
```

# bno055

```C++
namespace bno055 {
    Adafruit_BNO055 bno = Adafruit_BNO055(55);
    bool started = false;

    void setup()
    {
        started = bno.begin();
        if (!started) {
            Serial.println("could not connect");
        }
        bno.setExtCrystalUse(true);
    }

    double get_direction()
    {
        if (!started) {
            return 0.;
        }
        double dir_degree = bno.getVector(Adafruit_BNO055::VECTOR_EULER).x();
        double dir_radian = (
            (0 <= dir_degree && dir_degree <= 180) ? dir_degree : dir_degree - 360
        ) * PI / 180;
        return dir_radian;
        // // -180 <= d <= 180
        // dir_x -= 180;
        // // 0 -> 180, 180 -> 0, -45 -> -135
        // dir_x = dir_x >= 0 ? 180 - dir_x : -(180 + dir_x);
        // // 度数法からラジアン
        // dir_x = dir_x * PI / 180;
        // return dir_x;
    }
} // namespace bno055
```

# Vector2D

```C++
template<class T>
class Vector2D
{
private: // static part
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    static Vector2D from_polar_coord(const double &, const T &);

public: // nonstatic part
    T x, y;

    Vector2D() : x(0), y(0) {}
    Vector2D(const T &x, const T &y)
        : x(x), y(y) {}
    Vector2D(const T_VEC2D &p)
        : x(p.x), y(p.y) {}
    Vector2D(const T_LIST_(p))
        : x(p[0]), y(p[1]) {}
    Vector2D(const std::initializer_list<T> &init)
    {
        auto beg = init.begin();
        this->x = *beg;
        this->y = *(beg + 1);
    }

    Vector2D& operator=(const T_VEC2D &);
    Vector2D& operator=(const T_LIST);

    const T& operator[](size_t) const;
    T& operator[](size_t);

    String to_string() const;

    inline T dot(const Vector2D &) const;
    inline T dot(const T_LIST) const;
    inline T dot(const T &, const T &) const;

    double angle() const;
    double mag() const;
};

TMP T_VEC2D T_VEC2D::from_polar_coord(const double &angle, const T &magnitude)
{
    return T_VEC2D{
        magnitude * cos(angle),
        magnitude * sin(angle)
    };
}

TMP T_VEC2D& T_VEC2D::operator=(const T_VEC2D &tmp)
{
    this->x = tmp.x;
    this->y = tmp.y;
    return *this;
}

TMP T_VEC2D& T_VEC2D::operator=(const T_LIST_(tmp))
{
    this->x = tmp[0];
    this->y = tmp[1];
    return *this;
}

TMP const T& T_VEC2D::operator[](size_t index) const
{
    if (index == 1) { return this->y; }
    return this->x;
}

TMP T& T_VEC2D::operator[](size_t index)
{
    if (index == 1) { return this->y; }
    // else
    return this->x;
}

TMP String T_VEC2D::to_string() const
{
    return (
        "(" + String(this->x) + ", "
        + String(this->y) + ")"
    );
}

TMP inline T T_VEC2D::dot(const T_VEC2D &v) const
{
    return this->x * v.x + this->y * v.y;
}

TMP inline T T_VEC2D::dot(const T_LIST_(tmp)) const
{
    return this->x * tmp[0] + this->y * tmp[1];
}

TMP inline T T_VEC2D::dot(const T &x, const T &y) const
{
    return this->x * x + this->y * y;
}

TMP double T_VEC2D::angle() const
{
    return atan2(this->y, this->x);
}

TMP double T_VEC2D::mag() const
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}
```
