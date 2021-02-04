#include <robo2019.h>

using robo::I2CReaderWithAddr;
using CameraPos = robo::Vector2D<uint16_t>;


class OpenMVReader : public I2CReaderWithAddr
{
public:
    using I2CReaderWithAddr::I2CReaderWithAddr;

    /**
     * @fn CameraPos read_pos(const CameraPos &)
     */
    CameraPos read_pos(const CameraPos &);
};

CameraPos OpenMVReader::read_pos(const CameraPos &default_pos = CameraPos{0, 0})
{
    uint16_t data_size = I2CReaderWithAddr::read_data_size();
    if (data_size < 4) return default_pos;
    delayMicroseconds(10);
    uint8_t buff[data_size];
    if (!I2CReaderWithAddr::read_data(buff, data_size)) return default_pos;
    uint16_t x = buff[0] | (buff[1] << 8);
    uint16_t y = buff[2] | (buff[3] << 8);
    return CameraPos{x, y};
}

OpenMVReader openmv_i2c(0x12);
const CameraPos default_pos{0, 0};

void setup()
{
    robo::I2CReader::begin();
    Serial.begin(19200);
}

void loop()
{
    static uint8_t frame_count;
    static uint64_t last_time;

    CameraPos pos = openmv_i2c.read_pos(default_pos);
    /*if (pos != default_pos) {
        //Serial.println(pos.to_string());
    } else {
        //openmv_i2c.pass_data();
    }*/

    if (++frame_count % 100 == 0) {
        uint64_t cur_time = millis();
        double fps = 100000.0 / (cur_time - last_time);
        last_time = cur_time;
        frame_count = 0;
        //Serial.print("            ");
        Serial.println(fps);
    }
    delay(1); // Don't loop too quickly.
}
