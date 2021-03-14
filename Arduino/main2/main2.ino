#include <Wire.h>
#include <robo2019.h>

class MoveInfo
{
public:
    virtual void apply(robo::Motor &motor) = 0;
    virtual uint8_t to_string(char *dst) = 0;
    virtual String to_string() = 0;
};

class Stop : public MoveInfo
{
public:
    void apply(robo::Motor &motor) override
    {
        motor.stop();
    }

    uint8_t to_string(char *dst) override
    {
        if (dst == NULL) return 0;
        return sprintf(dst, "MoveInfo: Stop");
    }

    String to_string() override
    {
        char buffer[16] = "";
        to_string(buffer);
        return String(buffer);
    }
};

class Translate : public MoveInfo
{
private:
    const robo::V2_double vec;

public:
    Translate(const double &x, const double &y) : vec(x, y) {}
    Translate(const robo::V2_double &vec) : vec(vec) {}

    void apply(robo::Motor &motor) override
    {
        motor.set_velocity(vec);
    }

    uint8_t to_string(char *dst) override
    {
        if (dst == NULL) return 0;
        char *ptr = dst;
        ptr += sprintf(ptr, "MoveInfo: Translate");
        ptr += vec.to_string(ptr);
        return ptr - dst;
    }

    String to_string() override
    {
        char buffer[64] = "";
        to_string(buffer);
        return String(buffer);
    }
};

class Rotate : public MoveInfo
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

    uint8_t to_string(char *dst) {
        if (dst == NULL) return 0;
        return sprintf(
            dst,
            "MoveInfo: Rotate(clockwise=%s, %d)",
            clockwise ? "true" : "false",
            speed
        );
    }

    String to_string() override
    {
        char buffer[64];
        to_string(buffer);
        return String(buffer);
    }
};

inline constexpr uint16_t proc_echo(uint16_t before) {
    return before ? before : 1024;
}

constexpr double HPI = PI / 2;
constexpr double QPI = PI / 4;
constexpr int8_t max_speed = 100;
MoveInfo *m_stop;
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
    lcd.setup();
}

void loop() {
    bool w_left = IS_WHITE(lines::left.read()),
        w_right = IS_WHITE(lines::right.read()),
        w_back  = IS_WHITE(lines::back.read());
    robo::openmv::Frame *frame = mv_reader.read_frame();
    double bno_dir = bno055.read_geomag_direction();
    if (frame->ball_pos != NULL) {
        
    } else {
        
    }
}