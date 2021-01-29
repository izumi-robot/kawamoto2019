#include <robo2019.h>

using robo::motor;
using robo::LineSensor;
LineSensor left(1), right(3), back(5);

bool changed = false;

void setup()
{
    Serial.begin(9600);

    motor.setup();

    left.setup();
    right.setup();
    back.setup();
}

void loop()
{
    static double dir = PI / 2;
    const bool
        lw = LineSensor::iswhite(left.read()),
        rw = LineSensor::iswhite(right.read()),
        bw = LineSensor::iswhite(back.read());
    if (rw && !changed) {
        dir *= -1;
        changed = true;
    }
    motor.set.direction_and_speed(dir, 100);
}
