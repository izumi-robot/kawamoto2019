#include <robo2019.h>

void setup()
{
    Serial.begin(9600);
    robo::pixy::setup();
}

void loop()
{
    int block_num = robo::pixy::update();
    if (block_num == 0) {
        delay(1000);
        return;
    }
    robo::pixy::Camera_pos c_pos = robo::pixy::get_pos();
    double angle = robo::pixy::pos2angle(c_pos);
    Serial.println(c_pos.to_string());
    Serial.println("angle: " + String(angle));
    delay(1000);
}