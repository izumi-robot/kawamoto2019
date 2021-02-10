#include <robo2019.h>

robo::I2CReaderWithAddr reader(0x12);

void setup()
{
    Serial.begin(9600);
    reader.begin();
}

void loop()
{
    uint16_t size = reader.read_data_size();
    uint8_t buffer[size];
    reader.read_data(buffer, size);

    for (uint8_t v : buffer) {
        Serial.print(v);
        Serial.print(' ');
    }
    Serial.println();
    delay(1);
}