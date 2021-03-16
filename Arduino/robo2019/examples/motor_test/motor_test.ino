#include <robo2019.h>
#include <SoftwareSerial.h>

// for mega

SoftwareSerial motor_serial(12, 13);
robo::Motor motor(&motor_serial);
constexpr int power = 60;

void setup()
{
    motor_serial.begin(19200);
    Serial.begin(9600);
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
    motor.set_dir_and_speed(PI / 4, power);
    LOG
    delay(500);
    motor.stop();
    LOG
    delay(5000);
}
