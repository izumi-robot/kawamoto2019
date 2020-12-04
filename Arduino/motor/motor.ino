namespace vel_util {
    double front_bound = PI/4, back_bound = PI/4;
    struct Velocity {
        int x; int y;
        double rad() {
            return atan2(y, x);
        }
        double mag() {
            return sqrt(x^2 + y^2);
        }
    };

    Velocity ballPos2vel(double bx, double by) {
        Velocity v = {0, 0};
        
    }
};

namespace motor_ctrl {
    /*
        motors' positions:
        { left-up, right-up, left-bottom, right-bottom }
     */
    int powers[] = {0, 0, 0, 0};

    // assert : m_id = 1,2,3,4 && abs(power) <= 100
    void set(int m_id, int power) {
        /*
            Serial1.println(
                String(m_id)
                + (power < 0 ? "R" : "F")
                + String(
                    min(abs(power), 100)
                )
            );
         */
        String d = power < 0 ? "R" : "F";
        String p = String(abs(power)); // **TODO**: digit
        String dest = String(m_id) + d + p;
        Serial1.println(dest);
        Serial.println(dest);
        powers[m_id - 1] = power;
    }

    void stop() {
        for (int i = 1; i <= 4; ++i) {
            set(i, 0);
        }
    }

    void setup() { stop(); }

    // set motors' powers from radian (direction)
    // assert : -PI <= rad && rad <= PI && max_power >= min_power >= 0
    void set_powers(double rad, int max_power=90, int min_power=70) {
        /*
            min_power <= (a + cos(t)) * b <= max_power
                ** mi = min_power, ma = max_power **
            -> a = (ma + mi) / (ma - mi), b = (ma - mi) / 2
         */
        double a, b;
        if (max_power == min_power) {
            a = max_power;
            b = 0;
        } else {
            a = (max_power + min_power) / (max_power - min_power);
            b = (max_power - min_power) / 2;
        }
        auto f = [&](const double &d) -> int {
            return int((a + cos(d)) * b);
        };
        int r, l; // r : facing-right motor, l : facing-left motor
        bool d = -PI/2 < rad && rad < PI/2;
        r = d ? f(PI/4 + rad) : -f(PI*5/4 - rad);
        l = d ? f(PI/4 - rad) : -f(rad - PI*3/4);
        set(1, r); set(2, l); set(3, l); set(4, r);
    }
};

// example

// frame counter
int t = 0;

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);
    // initialize motors
    motor_ctrl::setup();
}

void loop() {
    // turn the direction of progress to a little right
    t += .01;
    if (PI < t) {
        t = -PI;
    }
    motor_ctrl::set_powers(0);
    delay(1000);
}
