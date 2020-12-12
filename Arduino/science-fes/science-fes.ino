#include <robo.h>

void setup() {
    Serial.begin(9600);
    robo::pixy_util::setup();
    robo::motor_ctrl::setup();
    robo::interrupt::setup(3); // interrupt pin 3
}

void loop() {
    INTERRUPT: { // label
        using namespace robo::interrupt;
        if (changed()) {
            if (state) {
                Serial.println("on");
            } else {
                Serial.println("off");
            }
        }
        if (!state) {
            return;
        }
    }

    robo::Vector2D<double> ball_pos;

    PIXY: {
        using robo::pixy_util::pixy;
        int block_num = pixy.ccc.getBlocks();
        if (block_num == 0) {
            return;
        }
        ball_pos.x = double(pixy.ccc.blocks[0].m_x);
        ball_pos.y = double(pixy.ccc.blocks[0].m_y);
    }

    double rad = robo::pixy_util::pos2angle(ball_pos);

    MOTOR: {
        robo::motor_ctrl::set_powers(rad, 40, 20);
    }
}
