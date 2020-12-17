#include <robo2019.h>
#include <ArxContainer.h>

// robo::Echo e_left(), e_right();

arx::vector<double> ds{0, PI, -PI / 2, PI / 2, -PI / 6, PI * 5 / 6};
double t = 0;

void setup() {
    Serial.begin(9600);
    robo::motor::setup();
    robo::bno055::setup();
}

void loop() {
    double dir;

    BNO055: {
        dir = robo::bno055::get_direction();
    }

    ROTATE: {
        if (abs(dir) <= PI / 18) {
            //robo::motor::stop();
            goto MOVE;
        }
        bool c = dir > 0;
        robo::motor::set::rotate(c, int(abs(50 * dir / PI)) + 10);
        goto END;
    }

    MOVE: {
        using robo::V2_double;
        t += .1;
        int i = int(t) % 6;
        V2_double v = V2_double::from_polar_coord(ds[i], 50);
        robo::motor::set::velocity(v);
    }

    END:
    delay(100);
}