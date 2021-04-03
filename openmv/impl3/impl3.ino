#include <Wire.h>
#include <robo2019.h>

namespace omv {
    using namespace robo::openmv;
    Reader reader(0x12, Wire);
    Frame * frame = NULL;
}

using I2 = robo::Interrupt<2, RISING>;
I2 & interrupt = I2::instance();

void setup() {
    Serial.begin(9600);
    interrupt.setup();
    Wire.begin();
}

void loop() {
    if (interrupt.changed()) {
        Serial.println("read");
        if (frame != NULL) delete frame;
        omv::frame = omv::reader.read_frame();
    }
    delay(100);
}