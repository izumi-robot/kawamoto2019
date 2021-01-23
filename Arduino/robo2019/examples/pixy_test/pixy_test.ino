#include <robo2019.h>

void setup()
{
    Serial.begin(9600);
    robo::pixy::setup();
}

void loop()
{
    int block_num = robo::pixy::update();
    Serial.println("============");
    for (int i = 0; i < block_num; i++) {
        robo::pixy::Camera_pos c_pos = robo::pixy::get_pos();
        double angle = robo::pixy::pos2angle(c_pos);
        Serial.println(c_pos.to_string());
        Serial.println("angle: " + String(angle));
    }
    delay(1000);
}