#include <Wire.h>
#include <robo2019.h>

namespace info {
    using namespace robo::move_info;
}

namespace omv {
    using namespace robo::openmv;
}

constexpr double HPI = PI / 2;
constexpr double QPI = PI / 4;
constexpr double bno_threshold = PI / 18;
constexpr int8_t max_speed = 100;
info::MoveInfo *m_stop;
robo::Motor motor(Serial2);

namespace lines {
    robo::LineSensor left(1), right(3), back(5);
}

namespace echos {
    robo::EchoSensor left(7, 6), right(4, 5), back(8, 9);
}

omv::Reader mv_reader(0x12);
robo::BNO055 bno055(0, 0x28);
robo::LCD lcd(0x27, 16, 2);

void setup() {
    echos::left.setup();
    echos::right.setup();
    echos::back.setup();

    lines::left.setup();
    lines::right.setup();
    lines::back.setup();

    mv_reader.setup();

    bno055.setup();

    Serial.begin(19200);
    motor.setup(19200);
    m_stop = new info::Stop();
    lcd.setup();
}

void loop() {
    using omv::Position;
    info::MoveInfo *m_info = m_stop;
    #define BIND(_name_) w_ ## _name_ = robo::LineSensor::iswhite(lines::_name_.read())
    bool BIND(left), BIND(right), BIND(back);
    #undef BIND
    omv::Frame *frame = mv_reader.read_frame();
    Position *ball_pos = frame == NULL ? NULL : frame->ball_pos;

    if (w_left || w_right || w_back) {
        // 線を踏んだ
        double d = 0.0;
        #define BIND(_name_) e_ ## _name_ = echos::_name_.read()
        uint16_t BIND(left), BIND(right), BIND(back);
        #undef BIND
        bool lt_lr = e_left < e_right,
            lt_br  = e_back < e_right,
            lt_bl  = e_back < e_left;
        d = (lt_br && lt_bl)
            ? 0.0 // 後ろの壁が一番近い => 前に進む
            : lt_lr ? -HPI : HPI; // 左の方が近い ? 右に進む : 左に進む
        m_info = new info::Translate(d, max_speed);
        goto MOTOR;
    }
    // bno
    {
        double bno_dir = bno055.get_geomag_direction();
        double adir = abs(bno_dir);
        if (adir > bno_threshold) {
            m_info = new info::Rotate(bno_dir > 0, int8_t(adir * 19 + 40));
        // (adir - 0) / (PI - 0) * (100 - 40) + 40
        // -> adir * 19 + 40
        goto MOTOR;
        }
    }

    // openmv
    if (ball_pos != NULL) {
        double ball_dir = omv::pos2dir(*ball_pos);
        m_info = new info::Translate(robo::V2_double::from_polar_coord(ball_dir * 3 / 2, max_speed));
    } else {
    }

    MOTOR: {
        m_info->apply(motor);
    }

    LOG: {
        char buff[64] = "";
        m_info->to_string(buff);
        Serial.println(buff);
        for (uint8_t pin = 1; pin <= 4; pin++) Serial.println(motor.get_power_str(pin));
        lcd.clear();
        lcd.print(buff + 10);
    }

    END:
    if (m_info != NULL && m_info != m_stop) delete m_info;
}
