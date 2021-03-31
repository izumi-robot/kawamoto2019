
#include <SoftwareSerial.h>

int8_t powers[] = {0, 0, 0, 0};
SoftwareSerial motor_ser(12, 13);

void update_motor() {
    char buff[32] = "";
    char * ptr = buff;
    #define UPDATE(i) sprintf(ptr, #i "%c%03u\n", powers[i - 1] < 0 ? 'F' : 'R', abs(powers[i - 1])); ptr += 6;
    UPDATE(1)
    UPDATE(2)
    UPDATE(3)
    UPDATE(4)
    #undef UPDATE
    motor_ser.print(buff);
}

void set_powers(int8_t p0, int8_t p1, int8_t p2, int8_t p3) {
    #define SET(i) powers[i] = p ## i;
    SET(0)
    SET(1)
    SET(2)
    SET(3)
    #undef SET
}

void trans_by_dir(float dir) {
    float s = 70 * sin(dir), t = 70 * cos(dir);
    int8_t a = int8_t((s + t) / 2), b = int8_t((t - s) / 2);
    set_powers(a, b, b, a);
}

void rotate(int8_t power) {
    set_powers(power, -power, power, -power);
}

void setup() {
    motor_ser.begin(19200);
}

void loop() {
    trans_by_dir(millis() / 1000.0);
    update_motor();
    delay(500);
}
