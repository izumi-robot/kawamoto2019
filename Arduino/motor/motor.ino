#include <robo2019.h>

using robo::motor;
using robo::bno_wrapper;

constexpr int power = 100;

void setup()
{
    motor.setup();
    bno_wrapper.setup();
}

void loop()
{
    double dir = bno_wrapper.get_direction();
    if (abs(dir) > PI / 6) {
        motor.set.rotate(dir > 0, abs(dir) * 40 / PI + 10);
    } else {
        motor.set.stop();
    }
    //motor.set.all_motors(power, power, power, power);
}