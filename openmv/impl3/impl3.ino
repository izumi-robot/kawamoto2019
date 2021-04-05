#include <Wire.h>
#include <robo2019.h>

namespace omv {
    using namespace robo::openmv;
    Reader reader(0x12, Wire);
    Frame * frame = NULL;

    void update_frame() {
        if (frame != NULL) delete frame;
        frame = reader.read_frame();
    }
}

using I2 = robo::Interrupt<2, RISING>;
I2 & interrupt = I2::instance();

void setup() {
    Serial.begin(9600);
    interrupt.setup();
    interrupt.changed();
    Wire.begin();
}

void loop() {
    if (interrupt.changed()) {
        Serial.println("read");
        omv::update_frame();
        if (omv::frame != NULL) {
            char buff[128] = "";
            omv::frame->to_string(buff);
            Serial.print(buff);
        }
    }
    delay(1);
}
