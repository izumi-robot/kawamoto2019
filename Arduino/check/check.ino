#include <Wire.h>
#include <HardwareSerial.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class EchoSensor {
public:
    const uint8_t echo_pin, trig_pin;
    EchoSensor(uint8_t e, uint8_t t) : echo_pin(e), trig_pin(t) {}
    void setup() {
        pinMode(echo_pin, INPUT);
        pinMode(trig_pin, OUTPUT);
    }
    int read() {
        #define DELAY_MS10 delayMicroseconds(10)
        digitalWrite(trig_pin, LOW);
        DELAY_MS10;
        digitalWrite(trig_pin, HIGH);
        DELAY_MS10;
        digitalWrite(trig_pin, LOW);
        return pulseIn(echo_pin, HIGH) / 59;
        #undef DELAY_MS10
    }
};

class LineSensor {
public:
    const uint8_t input_pin;
    LineSensor(uint8_t i) : input_pin(i) {}
    void setup() { pinMode(input_pin, INPUT); }
    int read() { return analogRead(input_pin); }
};

class Vector2 {
public:
    static inline Vector2 from_polar_coord(const double &angle, const double &mag) {
        return Vector2{ mag * cos(angle), mag * sin(angle) };
    }
    double x, y;
    Vector2() : x(0), y(0) {}
    Vector2(const double &x, const double &y) : x(x), y(y) {}
    uint8_t to_string(char *dst) {
        if (dst == NULL) return 0;
        sprintf(dst, "(%f, %f)", x, y);
        return strlen(dst);
    }
    String to_string() {
        char buff[16] = "";
        sprintf(buff, "(%f, %f)", x, y);
        return String(buff);
    }
};

inline bool operator==(const Vector2 &lh, const Vector2 &rh) { return lh.x == rh.x && lh.y == rh.y; }
inline bool operator!=(const Vector2 &lh, const Vector2 &rh) { return lh.x != rh.x || lh.y != rh.y; }

#define IM4(_macro_) _macro_(+) _macro_(-) _macro_(*) _macro_(/)
#define VEC_IOP(_operator_) Vector2& operator _operator_ ## = (Vector2 &lh, const Vector2 &rh) {\
    lh.x _operator_ ## = rh.x; lh.y _operator_ ## = rh.y; return lh; }
IM4(VEC_IOP)
#undef VEC_IOP
#define VEC_OP(_operator_) Vector2 operator _operator_ (const Vector2 &lh, const Vector2 &rh) {\
    Vector2 res = lh; res _operator_ ## = rh; return res; }
IM4(VEC_OP)
#undef VEC_OP
#undef IM4


class BNO055 : public Adafruit_BNO055 {
private:
    bool _detected = false;
public:
    using Adafruit_BNO055::Adafruit_BNO055;
    void setup() {
        _detected = Adafruit_BNO055::begin();
        Adafruit_BNO055::setExtCrystalUse(true);
    }
    double get_geomag_dir() {
        if (!_detected) return 0;
        double dir_degree = Adafruit_BNO055::getVector(Adafruit_BNO055::VECTOR_EULER).x();
        double dir_radian = (
            (0 <= dir_degree && dir_degree <= 180)
            ? dir_degree
            : dir_degree - 360
        ) * -PI / 180;
    }
    inline bool detected() { return _detected; }
};

class OpenMV {
private:
    TwoWire &_wire;
public:
    const uint8_t address;
    OpenMV() : _wire(Wire), address(0x12) {}
    OpenMV(uint8_t addr) : _wire(Wire), address(addr) {}
    OpenMV(TwoWire wire, uint8_t addr) : _wire(wire), address(addr) {}
    void setup() { _wire.begin(); }
    uint16_t read_2byte() { return _wire.read() | (uint16_t(_wire.read()) << 8); }
    uint16_t read_data_size() {
        _wire.requestFrom(address, 2);
        if (_wire.available() == 2) { return read_2byte(); }
        return 0;
    }
    Vector2 read_pos(
        const Vector2 &pos_on_fail = Vector2{0, 0},
        uint16_t default_value = 0xffff
    ) {
        uint16_t data_size = read_data_size();
        _wire.requestFrom(address, data_size);
        if (_wire.available() != 4) return pos_on_fail;
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return (x != default_value || y != default_value) ? Vector2{x, y} : pos_on_fail;
    }
};

class Motor {
public:
    static uint8_t power_str(char *dst, uint8_t pin, int8_t power) {
        if (dst == NULL) return 0;
        sprintf(dst, "%1d%c%03d", pin, power < 0 ? 'F' : 'R',abs(power));
        return strlen(dst);
    }
private:
    int8_t _powers[4];
    HardwareSerial &_serial;
    bool _update(uint8_t pin, int8_t power) {
        int8_t &p = _powers[pin - 1];
        if (p == power) return false;
        p = power;
        return true;
    }
public:
    Motor() : _powers{ 0, 0, 0, 0 }, _serial(Serial) {}
    Motor(HardwareSerial &serial) : _powers{ 0, 0, 0, 0 }, _serial(serial) {}
    void stop() {
        _serial.print("1F000\n2F000\n3F000\n4F000\n");
        memset(_powers, 0, 4);
    }
    void setup(const unsigned long &baud = 19200, int8_t config = SERIAL_8N1) {
        if (_serial) _serial.begin(baud, config);
        stop();
    }
    int8_t info(char *dst) {
        if (dst == NULL) return 0;
        char *ptr = dst;
        for (uint8_t i = 0; i < 4; i++) {
            Motor::power_str(ptr, i + 1, _powers[i]);
            ptr += 5;
            if (i == 3) break;
            sprintf(ptr, ", ");
            ptr += 2;
        }
        return 26; // 7 * 3 + 5
    }
    void set_one_motor(uint8_t pin, int8_t power) {
        if (!_update(pin, power)) return;
        char buff[8] = "";
        Motor::power_str(buff, pin, power);
        _serial.println(buff);
    }
    void set_all_motors(int8_t m1, int8_t m2, int8_t m3, int8_t m4) {
        int8_t npowers[4] = { m1, m2, m3, m4 };
        char buff[32] = "";
        char *ptr = buff;
        for (uint8_t pin = 1; pin <= 4; pin++) {
            int8_t np = npowers[pin - 1];
            if (!_update(pin, np)) continue;
            Motor::power_str(ptr, pin, np);
            ptr += 5;
            *(ptr++) = '\n';
        }
        *ptr = '\0';
        _serial.print(buff);
    }
    inline void set_left_right(int8_t left, int8_t right) { set_all_motors(left, right, left, right); }
    void set_velocity(const double &vx, const double &vy) {
        static const double root2 = sqrt(2.0);
        int8_t e1 = int8_t((vx + vy) / root2);
        int8_t e2 = int8_t((vx - vy) / root2);
        set_all_motors(e2, e1, e1, e2);
    }
    inline void set_velocity(const Vector2 &vel) { set_velocity(vel.x, vel.y); }
    inline void set_dir_and_speed(const double &dir, int8_t speed) { set_velocity(speed * cos(dir), speed * sin(dir)); }
    void set_rotate(bool clockwise, int8_t speed) {
        int8_t d = clockwise ? 1 : -1;
        set_left_right(speed * d, -speed * d);
    }
};

uint8_t frame_count = 0;
EchoSensor e23(2, 3), e45(4, 5), e67(6, 7);
LineSensor l1(1), l2(2), l3(3);
const Vector2 pos_on_fail{0, 0};
//         id, addr
BNO055 bno(-1, 0x28);
OpenMV openmv(0x12);
const Vector2 test_vel{-42, 90};
Motor motor(Serial); /* TODO */

void setup() {
    Serial.begin(9600);
    e23.setup(); e45.setup(); e67.setup();
    l1.setup(); l2.setup();
    bno.setup();
    openmv.setup();
    motor.setup();
}

void loop() {
    frame_count++;
    frame_count &= 0xff;

    char buffer[128] = "";
    char *ptr = buffer;

    #define READ(_reader_) sprintf(ptr, #_reader_ " = %4d\n", _reader_.read())
    #define E_READ(_reader_) READ(_reader_); ptr += 11;
    E_READ(e23) E_READ(e45) E_READ(e67)
    #undef E_READ
    #define L_READ(_reader_) READ(_reader_); ptr += 10;
    L_READ(l1) L_READ(l2) L_READ(l3)
    #undef L_READ

    Vector2 cam_pos = openmv.read_pos();
    if (cam_pos != pos_on_fail) {
        sprintf(ptr, "openmv = "); ptr += 9;
        uint8_t len = cam_pos.to_string(ptr); ptr += len;
        *(ptr++) = '\n';
    }

    double bnodir = bno.get_geomag_dir();
    sprintf(ptr, "bno = %4f\n", bnodir);
    ptr += 7;

    switch (frame_count % 5) {
        case 1: motor.set_all_motors(50, 50, 50, 50); break;
        case 2: motor.set_rotate(true, 80); break;
        case 3: motor.set_velocity(test_vel); break;
        case 4: motor.set_dir_and_speed(PI / 6, 70); break;
        case 0: default: motor.stop(); break;
    }
    uint8_t len = motor.info(ptr); ptr += len;
    *(ptr++) = '\n';

    *ptr = '\0';
    Serial.print(buffer);
    delay(1000);
}