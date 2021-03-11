#include <Wire.h>

class Motor {
private:
    static uint8_t power2byte(int8_t power) {
        return ((power < 0) << 7) | uint8_t(power / 100.0 * 127);
    }
    int8_t _powers[6];
public:
    Motor() : _powers{0, 0, 0, 0, 0, 0} {}
    void update() {
        Wire.beginTransmission(0x14 >> 1);
        #define SEND_POWER(i) Wire.write(Motor::power2byte(_powers[i]))
        SEND_POWER(1);
        SEND_POWER(2);
        SEND_POWER(3);
        SEND_POWER(4);
        #undef SEND_POWER
        Wire.write(0);
        Wire.write(0);
        Wire.endTransmission();
    }
    void stop() {
        memset(_powers, 0, 6);
    }
    void set_all_motors(int8_t m1, int8_t m2, int8_t m3, int8_t m4) {
        #define SET(i) _powers[i - 1] = m ## i
        SET(1); SET(2); SET(3); SET(4);
        #undef SET
    }
};

Motor motor;

void setup() {
    Wire.begin();
}

void loop() {
    motor.set_all_motors(50, -30, 90, -70);
    motor.update();
    delay(2);
}