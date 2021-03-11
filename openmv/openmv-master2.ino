#include <Wire.h>

struct CamPos {
    uint16_t x, y;
    uint8_t to_string(char *dst) {
        if (dst == NULL) return;
        return sprintf(dst, "(%u, %u)", x, y);
    }
};

bool operator==(const CamPos &lh, const CamPos &rh) {
    return lh.x == rh.x && lh.y == rh.y;
}

bool operator!=(const CamPos &lh, const CamPos &rh) {
    return lh.x != rh.x || lh.y != rh.y;
}

class OpenMV {
private:
    TwoWire &_wire;

public:
    const uint8_t address;

    OpenMV() : _wire(Wire), address(0x12) {}
    OpenMV(uint8_t addr) : _wire(Wire), address(addr) {}
    OpenMV(TwoWire &wire, uint8_t addr) : _wire(wire), address(addr) {}
    OpenMV(uint8_t addr, TwoWire &wire) : _wire(wire), address(addr) {}

    void setup() { _wire.begin(); }
    uint16_t read_2byte() { return _wire.read() | ((uint16_t)_wire.read() << 8); }
    CamPos read_pos(const CamPos &pos_on_fail = CamPos{0, 0}) {
        constexpr uint16_t default_value = 0xffff;
        uint8_t size = _wire.requestFrom(address, (uint8_t)4);
        if (size != 4) return pos_on_fail;
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return (x != default_value || y != default_value) ? CamPos{x, y} : pos_on_fail;
    }
};

OpenMV* openmv;
CamPos pos_on_fail{0, 0};

void setup() {
    openmv = new OpenMV(Wire, 0x12);
    Serial.begin(9600);
    openmv->setup();
}

void loop() {
    static uint8_t frame_count;
    static uint last_time = 0;
    CamPos pos = openmv->read_pos(pos_on_fail);
    if (pos != pos_on_fail) {
        char buffer[16] = "";
        pos.to_string(buffer);
        Serial.println(buffer);
    }
    if (++frame_count == 100) {
        int time
    }
}