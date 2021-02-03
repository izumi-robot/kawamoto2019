#include <robo2019.h>

using robo::EchoSensor;
using robo::motor;

double dir = - PI / 2;
bool changed = false;

namespace echo {
    EchoSensor sensors[] = {EchoSensor(7, 6), EchoSensor(4, 5), EchoSensor(8, 9)};
    EchoSensor &left = sensors[0], &right = sensors[1], &back = sensors[2];
    int values[] = {0, 0, 0};
    int &left_v = values[0], &right_v = values[1], &back_v = values[2];
    void setup()
    {
        for (int i = 0; i < 3; i++) sensors[i].setup();
    }
    void update()
    {
        for (int i = 0; i < 3; i++) {
            values[i] = sensors[i].read();
        }
    }
}

void setup()
{
    Serial.begin(9600);
    motor.setup();
    echo::setup();
}

void loop()
{
    Serial.println("======================");
    echo::update();
    for (auto &v : echo::values) Serial.println(v);
    if (!changed && echo::right_v < 20) {
        dir *= -1;
        changed = true;
    }
    motor.set.direction_and_speed(dir, 80);
    delay(500);
}