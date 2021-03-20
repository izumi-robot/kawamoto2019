#include <robo2019.h>
#include <SoftwareSerial.h>

SoftwareSerial motor_ser(12, 13);
robo::Motor motor(&Serial);
robo::move_info::Translate translate(100, 0, true);

void setup() {
    motor_ser.begin(19200);
    Serial.begin(19200);
}

void loop() {
    translate.apply(motor);
    Serial.println(motor.info());
    delay(100);
}