#include <ArxContainer.h>
#include <LiquidCrystal_I2C.h>

#include <robo2019.h>


namespace use_flag
{
    constexpr bool
        line  = false,
        echo  = false,
        pixy  = true,
        bno   = true,
        motor = true,
        lcd   = false;
}


template <class T>
class Sensor
{
private:
    class Values
    {
    private:
        Sensor *ptr;
        int _list[3];
        int &_left, &_right, &_back;
    public:
        Values()
            : ptr(NULL), _list{0, 0, 0}, _left(_list[0]), _right(_list[1]), _back(_list[2]) {}
        Values(Sensor *p)
            : ptr(p), _list{0, 0, 0}, _left(_list[0]), _right(_list[1]), _back(_list[2]) {}
        void update()
        {
            for (int i = 0; i < 3; ++i)
            {
                _list[i] = (*ptr)[i].read();
            }
        }

        inline const int &left()  const { return _left;  }
        inline const int &right() const { return _right; }
        inline const int &back()  const { return _back;  }
        inline const int &operator[](size_t i) const { return _list[i % 3]; }

        inline int &left()  { return _left;  }
        inline int &right() { return _right; }
        inline int &back()  { return _back;  }
        inline int &operator[](size_t i) { return _list[i]; }
    };

private:
    T _list[3];
    T &_left, &_right, &_back;
    Values _values;

public:
    Sensor(const T &left, const T &right, const T &back)
        : _list{ left, right, back },
        _left(_list[0]), _right(_list[1]), _back(_list[2]),
        _values(this) {}

    inline const T &left()  const { return _left;  }
    inline const T &right() const { return _right; }
    inline const T &back()  const { return _back;  }

    inline T &left()  { return _left;  }
    inline T &right() { return _right; }
    inline T &back()  { return _back;  }

    Values &values() { return _values; }

    void setup()
    {
        for (int i = 0; i < 3; ++i)
        {
            _list[i].setup();
        }
        _values.update();
    }

    inline const T &operator[](size_t i) const { return _list[i % 3]; }
    inline T &operator[](size_t i) { return _list[i]; }
};

namespace sensors{
    using robo::LineSensor;
    using robo::Echo;

    Sensor<Echo> echo(Echo(2, 3), Echo(4, 5), Echo(6, 7));
    Sensor<LineSensor> line(LineSensor(0), LineSensor(1), LineSensor(2));
}


enum class MotorFlag : int { stop, move, rotate };


LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{
    Serial.begin(9600);

    if (use_flag::line) {
        robo::LineSensor::white_border(300);
        sensors::line.setup();
    }
    if (use_flag::echo) {
        sensors::echo.setup();
    }
    if (use_flag::bno) {
        robo::bno_wrapper.setup();
    }
    if (use_flag::pixy) {
        robo::pixy::setup();
    }
    if (use_flag::motor) {
        robo::motor.setup();
    }
    if (use_flag::lcd) {
        lcd.init();
        lcd.backlight();
    }
    delay(5000);
}

void loop()
{
    static robo::pixy::Camera_pos cam_pos;
    static int untrack_frame = 100;
    static double dir;

    MotorFlag m_flag = MotorFlag::stop;

    double f_dir = robo::bno_wrapper.get_direction();
    double abs_fd = abs(f_dir);
    if (abs_fd > PI / 6) {
        m_flag = MotorFlag::rotate;
    }

    int block_len = robo::pixy::update();
    if (block_len > 0) {
        m_flag = MotorFlag::move;
        untrack_frame = 0;
        cam_pos = robo::pixy::get_pos(0, cam_pos);
        String pos_str = cam_pos.to_string();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(pos_str);
        Serial.println(pos_str);
        dir = robo::pixy::pos2angle(cam_pos);
    } else {
        untrack_frame++;
    }

    if (use_flag::motor) {
        using robo::motor;
        switch (m_flag)
        {
        case MotorFlag::move:
            motor.set.direction_and_speed(dir, 80);
            break;
        case MotorFlag::rotate:
            motor.set.rotate(f_dir > 0, abs_fd * 50 / PI + 10);
        case MotorFlag::stop:
        default:
            motor.set.stop();
            break;
        }
    }

    delay(10);
}
