#include <Wire.h>
#include <robo2019.h>

namespace info {
    using namespace robo::move_info;
}

inline constexpr uint16_t proc_echo(uint16_t before) {
    return before ? before : 1024;
}

constexpr double HPI = PI / 2;
constexpr double QPI = PI / 4;
constexpr int8_t max_speed = 100;
info::MoveInfo *m_stop;
robo::Motor motor(Serial2);

namespace lines {
    robo::LineSensor left(1), right(3), back(5);
}

namespace echos {
    robo::EchoSensor left(7, 6), right(4, 5), back(8, 9);
}

robo::openmv::Reader mv_reader(0x12);
robo::BNO055 bno055(55);
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
    info::MoveInfo *m_info = m_stop;
    #define BIND(_name_) w_ ## _name_ = robo::LineSensor::iswhite(lines::_name_.read())
    bool BIND(left), BIND(right), BIND(back);
    #undef BIND
    if (w_left || w_right || w_back) { // 線を踏んだ
        double d = 0.0;
        #define BIND(_name_) e_ ## _name_ = echos::_name_.read()
        uint16_t BIND(left), BIND(right), BIND(back);
        #undef BIND
        bool lt_lr = e_left < e_right,
            lt_br  = e_back < e_right,
            lt_bl  = e_back < e_left;
        if (lt_lr || lt_br || lt_bl) { // 超音波の値が信頼できる
            d = (lt_br && lt_bl)
                ? 0.0 // 後ろの壁が一番近い => 前に進む
                : lt_lr ? -HPI : HPI // 左の方が近い ? 右に進む : 左に進む
        } else { // 超音波の値が信頼できない
            d = w_back
                ? (w_left ? -QPI // 後ろと左の線を踏んだ => 右前に進む
                    : w_right ? QPI : 0.0) // 右の線を踏んだ ? 左前 : 真ん前
                // else: 後ろの線を踏んでいない
                : w_left ? -HPI : HPI // 右 : 左
        }
        m_info = new info::Translate(d, max_speed);
    }
    // bno
    double bno_dir = bno055.read_geomag_direction();

    // openmv
    robo::openmv::Frame *frame = mv_reader.read_frame();
    robo::openmv::Position *ball_pos = frame == NULL ? NULL : 
    if (frame != NULL) {
    } else {

    }
}