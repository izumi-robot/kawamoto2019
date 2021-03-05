#include "lib.h"

robo::Motor2 motor(Serial);

void setup()
{
    Serial.begin(9600);
    motor.setup(9600);
}

void loop()
{
    int ms = millis() / 1000 % 5;
    if (0 < ms && ms < 1) {
        motor.stop();
    } else if (ms < 2) {
        motor.set_all_motors(70, 70, 70, 70);
    } else if (ms < 3) {
        motor.set_left_right(50, -20);
    } else if (ms < 4) {
        motor.set_rotate(false, 50);
    }
    delay(100);
}