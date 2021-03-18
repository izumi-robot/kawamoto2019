#include <robo2019.h>

using robo::LineSensor;
LineSensor left(1), right(2), back(3);

void print_color(const uint16_t val) {
    Serial.println(robo::LineSensor::iswhite(val) ? "white" : "black");
}

void setup()
{
    Serial.begin(9600);

    left.setup();
    right.setup();
    back.setup();
}

void loop()
{
    #define BIND(_name_) v_ ## _name_ = _name_.read()
    const uint16_t BIND(left), BIND(right), BIND(back);
    #undef BIND
    #define PRINT Serial.println
    PRINT(v_left);
    PRINT(v_right);
    PRINT(v_back);
    #undef PRINT
    print_color(v_left);
    print_color(v_right);
    print_color(v_back);
    delay(1000);
}
