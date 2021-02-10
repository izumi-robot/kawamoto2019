#include <ArxContainer.h>
#include <LiquidCrystal_I2C.h>

#include <robo2019.h>


namespace use_flag
{
    constexpr bool
        line  = true,
        echo  = false,
        pixy  = true,
        bno   = true,
        motor = true,
        lcd   = true;
}


template <class T> class Sensor
{
public:
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
        inline const int &operator[](size_t i) const { return _list[i]; }

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
        update();
    }

    void update()
    {
        for (int i = 0; i < 3; i++)
        {
            _values[i] = _list[i].read();
        }
    }

    inline const T &operator[](size_t i) const { return _list[i]; }
    inline T &operator[](size_t i) { return _list[i]; }
};

namespace sensors{
    using robo::LineSensor;
    using robo::EchoSensor;

    using Echo_t = Sensor<EchoSensor>;
    using Line_t = Sensor<LineSensor>;

    Echo_t echo(EchoSensor(7, 6), EchoSensor(4, 5), EchoSensor(8, 9));
    Line_t line(LineSensor(1), LineSensor(3), LineSensor(5));
}


enum class MotorFlag : int { stop, move, rotate };

LiquidCrystal_I2C lcd(0x27, 16, 2);

double spin_enter_dir(const double &ball_dir)
{
    double sp_en_dir = ball_dir * 3 / 2;
    if (sp_en_dir < -PI) { sp_en_dir += 2 * PI; }
    if (sp_en_dir >  PI) { sp_en_dir -= 2 * PI; }
    return sp_en_dir;
}


void setup()
{
    Serial.begin(19200);

    if (use_flag::line) {
        sensors::line.setup();
    }
    if (use_flag::echo) {
        sensors::echo.setup();
    }
    if (use_flag::bno) {
        robo::bno055.setup();
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
}

void loop()
{
    static robo::pixy::Camera_pos cam_pos;
    static int untrack_frame = 100;
    static union { double dir; double power; } m_info;
    static long time;

    MotorFlag m_flag = MotorFlag::stop;

    if (use_flag::line) {
        using robo::LineSensor;
        sensors::Line_t::Values &values = sensors::line.values();
        values.update();
        const bool
            lw = LineSensor::iswhite(values.left()),
            rw = LineSensor::iswhite(values.right()),
            bw = LineSensor::iswhite(values.back());
        if (m_flag == MotorFlag::stop && lw || rw || bw) {
            m_flag = MotorFlag::move;
            if (lw) { m_info.dir =  PI / 2 + (bw ? PI / 4 : 0); }
            if (rw) { m_info.dir = -PI / 2 - (bw ? PI / 4 : 0); }
            if (bw) { m_info.dir =  0; }
        }
    }

    if (use_flag::bno && m_flag == MotorFlag::stop) {
        double fdir = robo::bno055.get_geomag_direction();
        if (abs(fdir) > PI / 12) {
            m_flag = MotorFlag::rotate;
            m_info.power = fdir * 80 / PI;
        }
        if (use_flag::lcd) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(fdir * 180 / PI);
        }
    }

    if (use_flag::pixy && m_flag == MotorFlag::stop) {
        if (robo::pixy::update() > 0) {
            double ball_dir;
            m_flag = MotorFlag::move;
            untrack_frame = 0;
            cam_pos = robo::pixy::get_pos(cam_pos);
            ball_dir = robo::pixy::pos2angle(cam_pos);
            m_info.dir = ball_dir;
            //m_info.dir = spin_enter_dir(ball_dir);
            if (use_flag::lcd) {
                lcd.setCursor(0, 1);
                lcd.print("detect");
            }
        } else {
            untrack_frame++;
            if (untrack_frame < 10) {
                m_flag = MotorFlag::move;
            }
            if (use_flag::lcd) {
                lcd.setCursor(0, 1);
                lcd.print("noball");
            }
        }
    }

    if (use_flag::motor) {
        using robo::motor;
        switch (m_flag)
        {
        case MotorFlag::move:
            motor.set.direction_and_speed(m_info.dir, 90);
            break;

        case MotorFlag::rotate:
            motor.set.rotate(
                m_info.power > 0,
                min(abs(m_info.power), 40)
            );
            break;

        case MotorFlag::stop:
        default:
            motor.set.stop();
            break;
        }
    }
}
