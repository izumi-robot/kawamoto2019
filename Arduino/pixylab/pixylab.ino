#include <ArxContainer.h>
#include <Pixy2.h>
#include <SPI.h>
#include <MyTypes.h>

Pixy2 pixy;

namespace robo {

namespace pixy_util {
    const int window_width = 320, window_height = 200;

    double pos2angle(int m_x, int m_y) {
        double x = m_x - window_width / 2;
        double y = m_y - window_height / 2;
        double ans = atan2(y, x);

    }
}

namespace btn_onoff {
    const int in_pin = 22, out_pin = 24;
    bool state  = false;

    void setup();
    void callback();
    bool changed();
    bool check();

    void setup() {
        pinMode(out_pin, OUTPUT);

        pinMode(in_pin, INPUT);
        attachInterrupt(in_pin, callback, RISING);
    }

    void callback() {
        Serial.println("changed");
        state = !state;
    }

    bool changed() {
        static bool s = false;

        bool ans = s != state;
        s = state;
        return ans;
    }

    bool check() {
        static bool s = LOW;

        bool n = digitalRead(in_pin) == HIGH;
        bool changed = n != state;
        state = n;
        return changed;
    }

}

}


void setup() {
    Serial.begin(9600);
    pixy.init();
    robo::btn_onoff::setup();
}


void loop() {
    using namespace robo::btn_onoff;
    if (check()) {
        if (state) {
            Serial.println("start");
        } else {
            Serial.println("end");
        }
    }
    if (!state) {
        return;
    }
    digitalWrite(out_pin, HIGH);
    getBalls();
    delay(500);
    digitalWrite(out_pin, LOW);
    delay(500);
}

void print_ball_info(int x, int y) {
    Serial.print("x: ");
    Serial.println(x);
    Serial.print("y: ");
    Serial.println(y);
}

void getBalls() {
    int blocks = (int)pixy.ccc.getBlocks();
    if(blocks) {
        for(int i=0; i<blocks; i++) {
            const auto &b = pixy.ccc.blocks[i];
            b.print();
            Serial.println(robo::pixy_util::pos2angle(b.m_x, b.m_y)/PI*180);
        }
    } else {
        Serial.println("no ball");
    }
}
