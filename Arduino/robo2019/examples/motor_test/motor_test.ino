#include <robo2019.h>

// for mega

robo::Motor motor(Serial2);
constexpr int power = 60;

void setup()
{
    Serial.begin(9600);
    motor.setup();
}

void loop()
{
    #define LOG Serial.println(motor.info());
    motor.set_all_motors(power, power, power, power);
    LOG
    delay(500);
    motor.set_rotate(true, power);
    LOG
    delay(500);
    motor.set_velocity(0, -power);
    LOG
    delay(500);
    motor.set_direction_and_speed(PI / 4, power);
    LOG
    delay(500);
    motor.set_stop();
    LOG
    delay(5000);
}
