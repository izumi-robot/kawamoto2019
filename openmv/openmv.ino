#include <Wire.h>

struct CameraPos {
public:
    uint16_t x, y;

    CameraPos() : x(0), y(0) {}
    CameraPos(uint16_t x, uint16_t y) : x(x), y(y) {}

    String to_string() {
        char buff[16] = "";
        sprintf(buff, "(%u, %u)", x, y);
        return String(buff);
    }
};

bool operator==(const CameraPos &lh, const CameraPos &rh) {
    return lh.x == rh.x && lh.y == rh.y;
}

bool operator!=(const CameraPos &lh, const CameraPos &rh) {
    return lh.x != rh.x || lh.y != rh.y;
}

#define IM4(_macro_) _macro_(+) _macro_(-) _macro_(*) _macro_(/)

#define CMPOS_IOP(_operator_) CameraPos& operator _operator_ ## = (CameraPos &lh, const CameraPos &rh) {\
    lh.x _operator_ ## = rh.x; lh.y _operator_ ## = rh.y; return lh; }

IM4(CMPOS_IOP)

#undef CMPOS_IOP

#define CMPOS_OP(_operator_) CameraPos operator _operator_ (const CameraPos &lh, const CameraPos &rh) {\
    CameraPos res = lh; res _operator_ ## = rh; return res; }

IM4(CMPOS_OP)

#undef CMPOS_OP

#undef IM4

class OpenMV {
private:
    TwoWire &_wire;
public:
    const uint8_t address;

    OpenMV() : _wire(Wire), address(0x12) {}
    OpenMV(uint8_t addr) : _wire(Wire), address(addr) {}
    OpenMV(TwoWire wire, uint8_t addr) : _wire(wire), address(adddr) {}

    void begin() { _wire.begin(); }

    uint16_t read_2byte() {
        return _wire.read() | (uint16_t(_wire.read()) << 8);
    }

    uint16_t read_data_size() {
        _wire.requestFrom(address, 2);
        if (_wire.available() == 2) {
            return read_2byte();
        }
        return 0;
    }

    CameraPos read_pos(
        const CameraPos &pos_on_fail = CameraPos{0, 0},
        uint16_t default_value = 0xffff
    ) {
        uint16_t data_size = read_data_size();
        _wire.requestFrom(address, data_size);
        if (_wire.available() != 4) return pos_on_fail;
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return (
            (x != default_value || y != default_value)
            ? CameraPos{x, y}
            : pos_on_fail
        );
    }
};

OpenMV openmv_i2c(0x12);
const CameraPos pos_on_fail{0, 0};

void setup() {
    openmv_i2c.begin();
    Serial.begin(9600);
}

void loop()
{
    static uint8_t frame_count;
    static uint64_t last_time;

    CameraPos pos = openmv_i2c.read_pos(pos_on_fail);
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
