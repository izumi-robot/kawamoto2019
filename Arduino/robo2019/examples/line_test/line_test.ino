#include <robo2019.h>

// LineSensor(analog-in pin)
robo::LineSensor left(1), right(3), back(5);

void setup()
{
    Serial.begin(9600);
    left.setup();
    right.setup();
    back.setup();
}

void loop()
{
    Serial.println(
        String(left.read()) + ", "
        + String(right.read()) + ", "
        + String(back.read())
    );
    delay(1000);
}