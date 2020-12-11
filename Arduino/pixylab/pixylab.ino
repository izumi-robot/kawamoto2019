#include <ArxContainer.h>
#include <Pixy2.h>

Pixy2 pixy;

class MyPixy {
    private:
    Pixy2 pixy;
    int block_num;

    public:
    static struct Block {
        private:
        int _x, _y, _width, _height;
        public:

        Block(int x=0, int y=0, int width=0, int height=0)
            :_X(x), _y(y), _width(width), _height(height) {}

        double angle() {
            
        }
    };

    MyPixy() {}

    void setup() {
        pixy.init();
        block_num = 0;
    }

    void update() {
        block_num = pixy.ccc.getBlocks();
    }

    int get_block_num() {
        return block_num;
    }
};

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
