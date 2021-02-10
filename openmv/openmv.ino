#include <robo2019.h>

robo::OpenMVReader openmv_i2c(0x12);
const robo::CameraPos pos_on_fail{0, 0};

void setup()
{
    robo::I2CReader::begin();
    Serial.begin(19200);
}

void loop()
{
    static uint8_t frame_count;
    static uint64_t last_time;

    robo::CameraPos pos = openmv_i2c.read_pos(pos_on_fail);
    if (pos != pos_on_fail) {
        Serial.println(pos.to_string());
    }

    if (++frame_count % 100 == 0) {
        uint64_t cur_time = millis();
        double fps = 100000.0 / (cur_time - last_time);
        last_time = cur_time;
        frame_count = 0;
        //Serial.print("            ");
        //Serial.println(fps);
    }
    delay(1); // Don't loop too quickly.
}
