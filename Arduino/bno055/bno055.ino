#include <robo2019.h>


void setup() {
    Serial.begin(9600);
    robo::bno055::setup();
}

void loop() {
    double d = robo::bno055::get_direction();
    Serial.println(d);
    delay(1000);
}