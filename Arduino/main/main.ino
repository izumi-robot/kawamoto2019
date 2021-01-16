#include <ArxContainer.h>
#include <LiquidCrystal_I2C.h>

#include <robo2019.h>

using arx::vector;

namespace use_flag
{
    const bool
        line  = false,
        echo  = false,
        pixy  = false,
        bno   = false,
        motor = true;
}

namespace echo
{
    using robo::Echo;
    Echo sensors[] = {
        Echo(0, 1), Echo(2, 3), Echo(4, 5)
    };

    Echo &left = sensors[0], &right = sensors[1], &back = sensors[2];

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
        LineSensor(0), LineSensor(2), LineSensor(3)
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
        for (LineSensor e : sensors)
        {
            e.setup();
        }
        values::update();
    }
}

void setup()
{
    Serial.begin(9600);

    if (use_flag::line)  line::setup();
    if (use_flag::echo)  echo::setup();
    if (use_flag::bno)   robo::bno_wrapper.setup();
    if (use_flag::pixy)  robo::pixy::setup();
    if (use_flag::motor) robo::motor.setup();
}

void loop()
{
    LINE_ECHO: {
        double ndir = 0;
        LINE:  if (use_flag::line)  {
            using robo::LineSensor;
            line::values::update();
        }

        ECHO:  if (use_flag::echo)  {}
    }

    BNO:   if (use_flag::bno)   {}

    PIXY:  if (use_flag::pixy)  {}

    MOTOR: if (use_flag::motor) {
        using robo::motor;
        motor.set.direction_and_speed(0, 80);
    }

    END:
    delay(70);
}