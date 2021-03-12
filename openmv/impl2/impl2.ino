#include <Wire.h>

class CamPos {
public:
    uint16_t x, y;
    CamPos(uint8_t x, uint8_t y) : x(x), y(y) {}
    uint8_t to_string(char *dst) {
        if (dst == NULL) return 0;
        return sprintf(dst, "(%u, %u)", x, y);
    }
};

bool operator==(const CamPos &lh, const CamPos &rh) {
    return lh.x == rh.x && lh.y == rh.y;
}

bool operator!=(const CamPos &lh, const CamPos &rh) {
    return lh.x != rh.x || lh.y != rh.y;
}

class Frame {
public:
    CamPos *ball_pos, *yellow_goal_pos, *blue_goal_pos;
    #define X(_name_) _name_ ## _x
    #define Y(_name_) _name_ ## _y
    #define PARAM(_name_) uint16_t X(_name_), uint16_t Y(_name_)
    #define NEW_POS(_name_) new CamPos(X(_name_), Y(_name_))
    Frame(PARAM(ball), PARAM(yellow_goal), PARAM(blue_goal))
    : ball_pos(NEW_POS(ball)), yellow_goal_pos(NEW_POS(yellow_goal)), blue_goal_pos(NEW_POS(blue_goal)) {}
    #undef X
    #undef Y
    #undef PARAM
    #undef NEW_POS
    Frame(CamPos *ball_pos, CamPos *yellow_goal_pos, CamPos *blue_goal_pos)
    : ball_pos(ball_pos), yellow_goal_pos(yellow_goal_pos), blue_goal_pos(blue_goal_pos) {}
    ~Frame() {
        #define DELETE(_name_) if (_name_ ## _pos != NULL) delete _name_ ## _pos;
        DELETE(ball)
        DELETE(yellow_goal)
        DELETE(blue_goal)
        #undef DELETE
    }
    uint8_t to_string(char *dst) {
        if (dst == NULL) return 0;
        char *ptr = dst;
        if (ball_pos != NULL){
            ptr += sprintf(ptr, "ball_pos: ");
            ptr += ball_pos->to_string(ptr);
            *(ptr++) = '\n';
        }
        if (yellow_goal_pos != NULL) {
            ptr += sprintf(ptr, "yellow_goal_pos: ");
            ptr += yellow_goal_pos->to_string(ptr);
            *(ptr++) = '\n';
        }
        if (blue_goal_pos != NULL) {
            ptr += sprintf(ptr, "blue_goal_pos: ");
            ptr += blue_goal_pos->to_string(ptr);
            *(ptr++) = '\n';
        }
        *ptr = '\0';
        return ptr - dst;
    }
};

enum class ObjKind : uint8_t { ball, yellow_goal, blue_goal };

class CamObj : public CamPos {
public:
    const ObjKind kind;
    CamObj(ObjKind kind, uint16_t x, uint16_t y) : kind(kind), CamPos(x, y) {}
    CamObj(ObjKind kind, const CamPos &pos) : kind(kind), CamPos(pos) {}
    uint8_t to_string(char *dst) {
        if (!dst) return 0;
        return sprintf(dst, "%s: (%u, %u)", (
            kind == ObjKind::ball ? "ball"
            : kind == ObjKind::yellow_goal ? "yellow goal"
            : kind == ObjKind::blue_goal ? "blue goal"
            : "unknown kind"
        ), x, y);
    }
};

class OpenMV {
private:
    TwoWire &_wire;
    static constexpr uint8_t data_size = 3;

public:
    const uint8_t address;

    OpenMV() : _wire(Wire), address(0x12) {}
    OpenMV(uint8_t addr) : _wire(Wire), address(addr) {}
    OpenMV(TwoWire &wire, uint8_t addr) : _wire(wire), address(addr) {}
    OpenMV(uint8_t addr, TwoWire &wire) : _wire(wire), address(addr) {}

    void setup() { _wire.begin(); }
    uint16_t read_2byte() { return _wire.read() | ((uint16_t)_wire.read() << 8); }
    CamPos* read_pos() {
        constexpr uint16_t default_value = 0xffff;
        uint8_t size = _wire.requestFrom(address, (uint8_t)4);
        if (size != 4) return NULL;
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return (x != default_value || y != default_value) ? new CamPos(x, y) : NULL;
    }
    CamObj* read_obj() {
        uint8_t size = _wire.requestFrom(address, uint8_t(5));
        if (size != uint8_t(5)) return NULL;
        ObjKind kind = static_cast<ObjKind>(_wire.read());
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return new CamObj(kind, x, y);
    }
    Frame* read_frame() {
        const uint16_t default_value = 0xffff;
        CamPos *ball = read_pos();
        CamPos *yellow = read_pos();
        CamPos *blue = read_pos();
        return new Frame(ball, yellow, blue);
    }
};

OpenMV* openmv;
char buffer[128] = "";

void setup() {
    openmv = new OpenMV(Wire, 0x12);
    Serial.begin(9600);
    openmv->setup();
}

void loop() {
    static uint8_t frame_count = 0;
    static uint16_t last_time = 0;
    Frame *frame = openmv->read_frame();
    //CamObj* obj = openmv->read_obj();
    if (frame != NULL) {
        frame->to_string(buffer);
        Serial.println(buffer);
        delete frame;
    }
    if (++frame_count == 100) {
        uint16_t time = millis();
        double fps = 100000.0 / (time - last_time);
        char buffer[16] = "fps: ";
        dtostrf(fps, 5, 2, buffer + 5);
        buffer[10] = '\0';
        Serial.println(buffer);
        frame_count = 0;
        last_time = time;
    }
}
