#include <robo2019.h>

robo::I2CReaderWithAddr openmv_i2c(0x12);

void setup()
{
    robo::I2CReader::begin();
    Serial.begin(19200);
    delay(1000); // Give the OpenMV Cam time to bootup.
}

void loop()
{
    uint16_t data_size = openmv_i2c.read_data_size();
    if (data_size > 0) {
        delayMicroseconds(10);
        uint8_t buff[128] = {};
        openmv_i2c.read_data(buff, data_size);
        for (int i = 0; i < data_size; ++i) {
            Serial.print(buff[i]);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        openmv_i2c.pass_data();
    }

    delay(1); // Don't loop to quickly.
}