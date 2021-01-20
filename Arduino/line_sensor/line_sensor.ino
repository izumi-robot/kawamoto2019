#include <robo2019.h>

using robo::LineSensor;
LineSensor left(0), right(1), back(2);

void setup()
{
    Serial.begin(9600);

    left.setup();
    right.setup();
    back.setup();
}

void loop()
{
    int lv = left.read();
    int rv = right.read();
    int bv = back.read();
    Serial.println(
        "left: " + String(lv)
        + ", right: " + String(rv)
        + ", back: " + String(bv)
    );
    delay(1000);
}