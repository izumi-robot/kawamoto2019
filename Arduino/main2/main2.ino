#include <Wire.h>
#include <SoftwareSerial.h>
#include <robo2019.h>

namespace info {
    using namespace robo::move_info;

    class Ptr {
    private:
        MoveInfo *_info;
        inline void _del() {
            if (_info != NULL) delete _info;
        }

    public:
        Ptr() : _info(new robo::move_info::Stop()) {}
        Ptr(MoveInfo *info) : _info(info) {}
        Ptr(const Ptr &) = delete;

        ~Ptr() { _del(); }

        Ptr& operator = (const Ptr &ptr) = delete;
        Ptr& operator = (MoveInfo *ptr) {
            _del();
            _info = ptr;
            return *this;
        }

        operator bool () const { return _info != NULL; }

        bool operator == (const Ptr &ptr) const { return ptr.ptr() == _info; }
        bool operator != (const Ptr &ptr) const { return ptr.ptr() != _info; }

        bool operator == (MoveInfo * pinfo) const { return pinfo == _info; }
        bool operator != (MoveInfo * pinfo) const { return pinfo != _info; }

        MoveInfo * operator -> () const { return _info; }
        MoveInfo * ptr() const { return _info; }
    };
}

namespace omv {
    using namespace robo::openmv;
}

float update_frame() {
    static uint8_t frame_count;
    static uint16_t last_time;
    static float fps;

    if (++frame_count == 100) {
        uint16_t cur_time = millis();
        fps = 100000.0 / (cur_time - last_time);
        last_time = cur_time;
        frame_count = 0;
    }
    return fps;
}

constexpr float HPI = PI / 2;
constexpr float QPI = PI / 4;
constexpr float bno_threshold = PI / 10;
constexpr float front_range = PI / 10;
constexpr int8_t max_speed = 100;

constexpr uint8_t kicker_pin = 10;
SoftwareSerial motor_ser(12, 13);
robo::Motor motor(&motor_ser);
auto_ptr<info::MoveInfo> m_info;
//info::Ptr m_info;

namespace lines {
    robo::LineSensor left(1), right(2), back(3);

    constexpr bool iswhite(uint16_t val) {
        return val >= 450;
    }
}

namespace echos {
    robo::EchoSensor left(1, 2), right(3, 4), back(5, 6);
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

    motor_ser.begin(19200);
    Serial.begin(19200);
    m_info = new info::Stop();

    lcd.setup();
}

void loop() {

    #define L_BIND(_name_) w_ ## _name_ = lines::iswhite(lines::_name_.read())
    const bool w_left = lines::left.read() > 400, L_BIND(right), L_BIND(back);
    #undef L_BIND
    const bool on_line = w_left || w_right || w_back;

    omv::Frame *frame = mv_reader.read_frame();
    omv::Position *ball_pos = frame == NULL ? NULL : frame->ball_pos;
    omv::Position *y_goal_pos = frame == NULL ? NULL : frame->y_goal_pos;
    float y_goal_dir = y_goal_pos == NULL ? 10 : omv::pos2dir(*y_goal_pos);
    float bno_dir = bno055.get_geomag_direction();

    if (on_line) { // 線を踏んだ
        float d = 0.0;
        if (abs(y_goal_dir) < front_range) {
            d = PI;
        } else {
            //#define USE_ECHO
            #ifdef USE_ECHO
            #define BIND(_name_) e_ ## _name_ = echos::_name_.read()
            uint16_t BIND(left), BIND(right), BIND(back);
            #undef BIND
            d = (e_back < e_right && e_back < e_left)
                ? 0.0 // 後ろの壁が一番近い => 前に進む
                : e_left < e_right ? -HPI : HPI; // 左の方が近い ? 右に進む : 左に進む
            #else /* USE_ECHO */
            d = w_left == w_right ? 0.0 : w_left ? -HPI : HPI;
            #endif /* USE_ECHO */
        }
        m_info = new info::Translate(robo::V2_float::from_polar_coord(d, max_speed));
        goto MOTOR;
    }

    // direction
    BNO: {
        float adir = abs(bno_dir);
        if (adir > bno_threshold) {
            m_info = new info::Rotate(bno_dir > 0, int8_t(adir * 25 + 40));
            // (adir - 0) / (PI - 0) * (100 - 20) + 20
            // -> adir * 25 + 40
            goto MOTOR;
        }
    }

    BALL:
    if (ball_pos != NULL) {
        float ball_dir = omv::pos2dir(*ball_pos);
        m_info = new info::Translate(robo::V2_float::from_polar_coord(ball_dir * 3 / 2, max_speed));
    }

    m_info = new info::Stop();

    MOTOR: {
        if (m_info) {
            m_info->apply(motor);
        }
    }

    LOG: {
        lcd.clear();
        char buff[64] = "";
        sprintf_P(buff, PSTR("l:%u,r:%u,b:%u"), w_left, w_right, w_back);
        lcd.setCursor(0,0);
        lcd.print(buff);
        lcd.setCursor(0, 1);
        lcd.print(update_frame());
    }

    END: {
        if (frame != NULL) delete frame;
    }
}
