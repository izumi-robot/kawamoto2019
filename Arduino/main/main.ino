#include <ArxContainer.h>
#include <LiquidCrystal_I2C.h>

#include <robo2019.h>


namespace use_flag
{
    constexpr bool
        line  = true,
        echo  = true,
        pixy  = false,
        bno   = true,
        motor = true,
        lcd   = true;
}


namespace echo
{
    using robo::Echo;
    Echo sensors[] = {
        Echo(2, 3), Echo(4, 5), Echo(6, 7)
    };

    Echo &left = sensors[0], &right = sensors[1], &back = sensors[2];

    namespace values
    {
        int list[] = {0, 0, 0};
        int &left = list[0], &right = list[1], &back = list[2];
        void update()
        {
            for (int i = 0; i < 3; i++)
            {
                list[i] = sensors[i].read();
            }
        }
    }

    void setup()
    {
        for (Echo e : sensors)
        {
            e.setup();
        }
    }
}


namespace line
{
    using robo::LineSensor;
    LineSensor sensors[] = {
        LineSensor(0), LineSensor(1), LineSensor(2)
    };

    LineSensor &left = sensors[0], &right = sensors[1], &back = sensors[2];

    namespace values
    {
        int list[] = {0, 0, 0};
        int &left = list[0], &right = list[1], &back = list[2];
        void update()
        {
            for (int i = 0; i < 3; i++)
            {
                list[i] = sensors[i].read();
            }
        }
    }

    void setup()
    {
        for (LineSensor l : sensors)
        {
            l.setup();
        }
        values::update();
    }
}


enum class MotorFlag : int {
    stop, move, rotate
};


LiquidCrystal_I2C lcd(0x27, 16, 2);
robo::V2_double ball_pos{0, 0};
int untrack_frame = 0;


void setup()
{
    Serial.begin(9600);
    robo::LineSensor::white_border(300);

    if (use_flag::line) {
        line::setup();
    }
    if (use_flag::echo)  {
        echo::setup();
    }
    if (use_flag::bno) {
        robo::bno_wrapper.setup();
    }
    if (use_flag::pixy)  {
        robo::pixy::setup();
    }
    if (use_flag::motor) {
        robo::motor.setup();
    }
    if (use_flag::lcd)   {
        lcd.init();
        lcd.backlight();
    }
    delay(5000);
}

void loop()
{
    union {
        double direction;
        double rotate_angle;
    } info;
    info.direction = -PI / 2;
    MotorFlag m_flag = MotorFlag::move;

    LINE_ECHO: {
        LINE:  if (use_flag::line)  {
            using robo::LineSensor;
            line::values::update();
            const bool
                l_wh = LineSensor::iswhite(line::values::left),
                r_wh = LineSensor::iswhite(line::values::right),
                b_wh = LineSensor::iswhite(line::values::back);
            if (l_wh && r_wh) {
                info.direction = 0;
            } else if (l_wh) {
                info.direction = b_wh ? PI / 4 : PI / 2;
            } else if (r_wh) {
                info.direction = b_wh ? -PI / 4 : -PI / 2;
            } else if (b_wh) {
                info.direction = 0;
            }
            m_flag = l_wh || r_wh || b_wh ? MotorFlag::move : m_flag;
        }

        ECHO:  if (use_flag::echo)  {}
    }

    BNO: if (use_flag::bno) {
        double dir = robo::bno_wrapper.get_direction();
        if (abs(dir) > PI / 4) {
            info.rotate_angle = dir * 80 / PI;
            m_flag = MotorFlag::rotate;
        }
        if (use_flag::lcd) {
            lcd.setCursor(0, 1);
            lcd.print(dir);
        }
        //Serial.println("bno: " + String(dir));
    }

    PIXY: if (use_flag::pixy)  {
        int num = robo::pixy::update();
        if (num > 0) {
            untrack_frame = 0;
            robo::pixy::Camera_pos c_pos = robo::pixy::get_pos(0);
            ball_pos = robo::pixy::cam_pos2real_pos(c_pos);
            Serial.println(c_pos.to_string());
        } else {
            untrack_frame++;
            if (untrack_frame > 3) {
                m_flag = MotorFlag::stop;
            }
        }
        info.direction = atan2(ball_pos.x, ball_pos.y);
    }

    MOTOR: if (use_flag::motor) {
        using robo::motor;
        switch (m_flag)
        {
        case MotorFlag::move:
            motor.set.direction_and_speed(info.direction, 80);
            break;
        case MotorFlag::rotate:
            motor.set.rotate(
                info.rotate_angle > 0,
                int8_t(abs(info.rotate_angle))
            );
            break;
        default: // MotorFlag::stop
            motor.set.stop();
            break;
        }
    }

    LCD: if (use_flag::lcd) {
        lcd.setCursor(0, 0);
        lcd.print(info.direction * 180 / PI);
    }

    END:
    delay(50);
}
