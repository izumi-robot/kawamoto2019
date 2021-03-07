#include <robo2019.h>



struct MoveInfo
{
    virtual void apply(robo::Motor &motor) = 0;
    virtual String to_string() = 0;
};

struct Stop : public MoveInfo
{
public:
    void apply(robo::Motor &motor) override
    {
        motor.stop();
    }

    String to_string() override
    {
        return "MoveInfo: Stop";
    }
}

struct Translate : public MoveInfo
{
private:
    const robo::V2_double vec;
public:
    Translate(const double &x, const double &y) : vec(x, y) {}
    Translate(const robo::V2_double &vec) : vec(vec) {}

    void apply(robo::Motor &motor) override
    {
        motor.set_velocity(x, y);
    }

    String to_string() override
    {
        return "MoveInfo: Translate" + vec.to_string();
    }
};

struct Rotate : public MoveInfo
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

    String to_string() override
    {
        char buffer[32];
        sprintf(buffer, "MoveInfo: Rotate(%d)", speed);
        return String(buffer);
    }
};

#define USE_MOTOR
#define USE_ECHO
#define USE_LINE
#define USE_OPENMV
#define USE_BNO055
#define USE_LCD
#define DO_DEBUG

constexpr double HPI = PI / 2;
constexpr double QPI = PI / 4;
constexpr int8_t max_speed = 100;

robo::Motor motor(Serial);

namespace lines {
    robo::LineSensor left(1), right(3), back(5);
}

namespace echos {
    robo::EchoSensor left(7, 6), right(4, 5), back(8, 9);
}

robo::OpenMVReader openmv(0x12);
robo::BNO055 bno055(55);
robo::LCD lcd(0x27, 16, 2);

MoveInfo *m_stop;

void setup()
{
    #ifdef USE_MOTOR
    motor.setup(19200);
    m_stop = new Stop();
    #endif /* USE_MOTOR */

    #ifdef USE_ECHO
    echos::left.setup();
    echos::right.setup();
    echos::back.setup();
    #endif /* USE_ECHO */

    #ifdef USE_LINE
    lines::left.setup();
    lines::right.setup();
    lines::back.setup();
    #endif /* USE_LINE */

    #ifdef USE_OPENMV
    openmv.setup();
    #endif /* USE_OPENMV */

    #ifdef USE_BNO055
    bno055.setup();
    #endif /* USE_BNO055 */

    #ifdef USE_LCD
    lcd.setup();
    #endif /* USE_LCD */

    #ifdef DO_DEBUG
    Serial.begin(19200);
    #endif /* DO_DEBUG */
}

void loop()
{
    static MoveInfo *m_info;

    m_info = m_stop;
    bool fetch_echo = false;

    #ifdef USE_LINE
    LINE: {
    using robo::LineSensor;
    bool w_left = LineSensor::iswhite(lines::left.read()),
        w_right = LineSensor::iswhite(lines::right.read()),
        w_back  = LineSensor::iswhite(lines::back.read());

    #define LINE_DIR (w_back\
            ? (w_left == w_right ? 0.0 : (w_left ? -QPI : QPI))\
            : (w_left == w_right ? 0.0 : (w_left ? -HPI : HPI)))

    if (w_left || w_right || w_back) {
        double d = 0.0;

        #ifdef USE_ECHO
        using robo::EchoSensor;
        int e_left  = echos::left.read() || 1024,
            e_right = echos::right.read() || 1024,
            e_back  = echos::back.read() || 1024;
        d = (
            (e_left != e_right || e_right != e_back)
            ? (
                (e_left < e_right)
                ? (e_left < e_back ? -HPI : 0.0)
                : (e_right < e_back ? HPI : 0.0)
            )
            : LINE_DIR
        );
        #else /* USE_ECHO */
        d = LINE_DIR;
        #endif /* USE_ECHO */

        m_info = new Translate(
            max_speed * cos(d),
            max_speed * sin(d)
        );
    } // if (w_left || w_right || w_back)
    } // tag LINE
    #endif /* USE_LINE */

    #ifdef USE_BNO055
    BNO055: {
    double fdir = bno055.get_geomag_direction();
    double adir = abs(fdir);
    if (adir > 1.0) { // 1.0: PI / 3
        m_info = new Rotate(fdir > 0, int8_t())
        pmap(adir, 0, PI, 40, 100);
    }
    }
    #endif /* USE_BNO055 */

    #ifdef USE_OPENMV

    #endif /* USE_OPENMV */

    #ifdef USE_MOTOR
    #endif /* USE_MOTOR */

    #ifdef USE_LCD
    #endif /* USE_LCD */

    #ifdef DO_DEBUG
    #endif /* DO_DEBUG */
}
