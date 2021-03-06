#include <Wire.h>

namespace robo
{

class I2CReader
{
public:
    static void begin();

    static uint16_t pass_data();

    uint16_t read_data_size(uint8_t addr);

    bool read_data(char * buff, uint8_t addr, uint16_t data_size);

    bool read_data(uint8_t * buff, uint8_t addr, uint16_t data_size);
};

class I2CReaderWithAddr : public I2CReader
{
public:
    const uint8_t address;
    I2CReaderWithAddr(uint8_t addr) : I2CReader(), address(addr) {}

    inline uint16_t read_data_size();

    inline bool read_data(char *, uint16_t);

    inline bool read_data(uint8_t *, uint16_t);
};

}

void robo::I2CReader::begin() { Wire.begin(); }

uint16_t robo::I2CReader::pass_data()
{
    uint16_t data_size = Wire.available();
    for (int i = 0; i < data_size; ++i) {
        Wire.read();
    }
    return data_size;
}

uint16_t robo::I2CReader::read_data_size(uint8_t addr)
{
    Wire.requestFrom(addr, (uint8_t)2);
    if (Wire.available() == 2) {
        return Wire.read() | (Wire.read() << 8);
    }
    return 0;
}

bool robo::I2CReader::read_data(char *buff, uint8_t addr, uint16_t data_size)
{
    if (buff == NULL) return false;

    Wire.requestFrom(addr, data_size);
    if (Wire.available() < data_size) return false;

    for (uint16_t i = 0; i < data_size; ++i) {
        buff[i] = Wire.read();
    }
    return true;
}

bool robo::I2CReader::read_data(uint8_t *buff, uint8_t addr, uint16_t data_size)
{
    if (buff == NULL) return false;

    Wire.requestFrom(addr, data_size);
    if (Wire.available() < data_size) return false;

    for (uint16_t i = 0; i < data_size; ++i) {
        buff[i] = Wire.read();
    }
    return true;
}

uint16_t robo::I2CReaderWithAddr::read_data_size()
{
    return I2CReader::read_data_size(address);
}

bool robo::I2CReaderWithAddr::read_data(char *buff, uint16_t data_size)
{
    return I2CReader::read_data(buff, address, data_size);
}

bool robo::I2CReaderWithAddr::read_data(uint8_t *buff, uint16_t data_size)
{
    return I2CReader::read_data(buff, address, data_size);
}

namespace robo
{
    struct CameraPos {
    public:
        uint16_t x, y;

        String to_string() {
            char buff[32] = "";
            sprintf(buff, "(%u, %u)", x, y);
            return String(buff);
        }

        bool operator != (const CameraPos &rh) {
            return x != rh.x || y != rh.y;
        }
    };

using robo::I2CReaderWithAddr;

class OpenMVReader : public I2CReaderWithAddr
{
public:
    using I2CReaderWithAddr::I2CReaderWithAddr;

    CameraPos read_pos(const CameraPos & pos_on_fail);
};

CameraPos OpenMVReader::read_pos(const CameraPos &pos_on_fail = CameraPos{0, 0})
{
    static constexpr uint16_t default_value = 0xffff;
    uint16_t data_size = I2CReaderWithAddr::read_data_size();
    if (data_size < 4) { return pos_on_fail; }
    delayMicroseconds(10);
    uint8_t buff[data_size];
    if (!I2CReaderWithAddr::read_data(buff, data_size)) {
        pass_data();
        return pos_on_fail;
    }
    uint16_t x = buff[0] | (buff[1] << 8);
    uint16_t y = buff[2] | (buff[3] << 8);
    return (
        (x == default_value && y == default_value)
        ? pos_on_fail
        : CameraPos{x, y}
    );
}

}

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
        Serial.print("read\n");
        //Serial.println(pos.to_string());
    }

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
