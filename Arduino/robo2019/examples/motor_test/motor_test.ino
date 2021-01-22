#include <robo2019.h>

using robo::motor;
constexpr int power = 30;

void setup()
{
    Serial.begin(9600);
    motor.setup();
}

void loop()
{
    motor.set.all_motors(power, power, power, power);
    if (millis() % 1000 == 0) { Serial.println(motor.get.info()); }
}