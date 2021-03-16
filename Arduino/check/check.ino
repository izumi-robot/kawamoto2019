#include <Wire.h>
#include <robo2019.h>

inline constexpr uint16_t proc_echo(uint16_t before) {
    return before ? before : 1024;
}

namespace info {
    using namespace robo::move_info;
}

#define USE_MOTOR
#define USE_ECHO
#define USE_LINE
#define USE_OPENMV
#define USE_BNO055
#define USE_LCD

constexpr double HPI = PI / 2;
constexpr double QPI = PI / 4;
constexpr int8_t max_speed = 100;
info::MoveInfo *m_stop;

#ifdef USE_MOTOR
robo::Motor motor(Serial2);
#endif /* USE_MOTOR */

#ifdef USE_LINE
namespace lines {
    robo::LineSensor left(1), right(3), back(5);
}
#endif /* USE_LINE */

#ifdef USE_ECHO
namespace echos {
    robo::EchoSensor left(7, 6), right(4, 5), back(8, 9);
}
#endif /* USE_ECHO */

#ifdef USE_OPENMV
robo::openmv::Reader mv_reader(0x12);
#endif /* USE_OPENMV */

#ifdef USE_BNO055
robo::BNO055 bno055(55);
#endif /* USE_BNO055 */

#ifdef USE_LCD
robo::LCD lcd(0x27, 16, 2);
#endif /* USE_LCD */

void setup()
{
    Wire.begin();
    m_stop = new info::Stop();

    #ifdef USE_MOTOR
    motor.setup(19200);
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

    #ifdef USE_BNO055
    bno055.setup();
    #endif /* USE_BNO055 */

    #ifdef USE_LCD
    lcd.setup();
    #else /* USE_LCD */
    Serial.begin(19200);
    #endif /* USE_LCD */
}

void loop()
{
    #ifdef USE_LCD
    lcd.clear();
    #define PRINT(something) lcd.print(something)
    #else /* USE_LCD */
    #define PRINT(something) Serial.print(something)
    #endif /* USE_LCD */

    ECHO:
    #ifdef USE_ECHO
    {

    #define E_READ(_name_) PRINT(echos::_name_.read())
    E_READ(left);
    E_READ(right);
    E_READ(back);
    #undef E_READ

    }
    #endif /* USE_ECHO */

    LINE:
    #ifdef USE_LINE
    {

    #define L_READ(_name_) PRINT(lines::_name_.read())
    L_READ(left);
    L_READ(right);
    L_READ(back);
    #undef L_READ

    }
    #endif /* USE_LINE */

    BNO055:
    #ifdef USE_BNO055
    {

    PRINT(bno055.get_geomag_direction());

    }
    #endif /* USE_BNO055 */

    OPENMV:
    #ifdef USE_OPENMV
    {

    using namespace robo::openmv;
    Frame *frame = mv_reader.read_frame();
    if (frame != NULL && frame->ball_pos != NULL) {
        char buff[16] = "";
        frame->ball_pos->to_string(buff);
        PRINT(buff);
    }

    }
    #endif /* USE_OPENMV */

    MOTOR:
    #ifdef USE_MOTOR
    {

    double d = millis() / 1000.;
    motor.set_dir_and_speed(d, 100);
    PRINT(motor.info());

    }
    #endif /* USE_MOTOR */

    delay(1000);
}
