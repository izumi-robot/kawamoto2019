#include <robo2019.h>

namespace omv {
    using namespace robo::openmv;
}

omv::Reader mv_reader(0x12);

void setup() {
    mv_reader.setup();
    Serial.begin(9600);
}

void loop() {
    omv::Frame *frame = mv_reader.read_frame();
    if (frame != NULL && frame->ball_pos != NULL) {
        double dir = omv::pos2dir(frame->ball_pos[0]);
        char buff[8] = "";
        dtostrf(dir, 0, 4, buff);
        Serial.println(buff);
    }
    delay(1000);
}