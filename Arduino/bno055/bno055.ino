#include <robo2019.h>


void setup() {
    Serial.begin(9600);
    robo::bno055::setup();
}

void loop() {
    Serial.println(robo::bno055::get_direction());
    delay(1000);
}