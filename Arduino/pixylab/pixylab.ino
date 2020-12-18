#include <robo2019.h>

void setup() {
    robo::pixy::setup();
}

void loop() {
    int l = robo::pixy::update();
    for (int i = 0; i < l; ++i) {
        Serial.println(robo::pixy::get_pos(i).to_string());
    }
}