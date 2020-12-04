#include <Pixy2.h>
#include <SPI.h>

Pixy2 pixy;

void setup() {
    Serial.begin(9600);
    pixy.init();
}

void loop() {
    getBalls();
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
            int x = (int)pixy.ccc.blocks[i].m_x;
            int y = (int)pixy.ccc.blocks[i].m_y;
            print_ball_info(x, y);
            Serial.println("===============");
        }
    } else {
        Serial.println("no ball");
    }
    delay(1000);
}
