#include <robo2019.h>

using robo::bno055;

void setup()
{
    Serial.begin(9600);
    bno055.setup();
    if (bno055.detected()) Serial.println("detected");
}

void loop()
{
    static int frame_count;

    double dir = bno055.update_gyro_dir();
    if (++frame_count % 1000 == 0) {
        frame_count = 0;
        Serial.println(degrees(dir));
    }
    // delay(10);
}