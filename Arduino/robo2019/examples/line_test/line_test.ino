#include <robo2019.h>

// LineSensor(analog-in pin)
robo::LineSensor line_sensor(3);

void setup()
{
    line_sensor.setup();
}

void loop()
{
    Serial.println(line_sensor.read());
    delay(1000);
}