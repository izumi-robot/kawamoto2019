
void str_rjust(String &s, int len, const String &pad) {
    for (int i = s.length(); i < len; i++) {
        s = pad + s;
    }
}

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

    String power_str(int m_id, int power) {
        String d = power < 0 ? "R" : "F";
        String p = String(abs(power)); // **TODO**: digit
        str_rjust(p, 3, "0");
        return String(m_id) + d + p;
    }

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
        String dest = power_str(m_id, power);
        Serial1.println(dest);
        //Serial.println(dest);
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
        bool forward = -PI/2 < rad && rad < PI/2;
        r = forward ? f(PI/4 + rad) : -f(PI*5/4 - rad);
        l = forward ? f(PI/4 - rad) : -f(rad - PI*3/4);
        set(1, r); set(2, l); set(3, l); set(4, r);
    }

    String power_info() {
        String s = "[";
        for (int i = 1; i <= 4; i++) {
            s += String(i) + ": " + power_str(i, powers[i - 1]);
            if (i != 4) {
                s += ", ";
            }
        }
        return s + "]";
    }
};

bool check() {
    static bool b = true;
    static int value = LOW;

    int v = digitalRead(in_pin);
    if (v != value) {
        value = v;
        if (value == HIGH) {
            b = !b;
        }
    }
    return b;
}

// example

// frame counter
double t = 0;

const int in_pin = 22, out_pin = 24;
bool s = false;

void setup() {
    Serial.begin(9600);
    Serial1.begin(19200);
    // initialize motors
    motor_ctrl::setup();
    Serial.println(motor_ctrl::power_info());
    pinMode(in_pin, INPUT);
    pinMode(out_pin, OUTPUT);
}

void loop() {
    static bool s = false;
    static int value = LOW;

    int v = digitalRead(in_pin);
    bool d = (v != value);
    if (v == HIGH && d) {
        s = !s;
    }
    value = v;
    if (s) {
        if (d) {
            digitalWrite(out_pin, HIGH);
            Serial.println("start");
        }
    } else {
        if (d) {
            digitalWrite(out_pin, LOW);
            Serial.println("end");
        }
        delay(100);
        return 0;
    }

    // turn the direction of progress to a little right
    t += .01;
    if (PI < t) {
        t = -PI;
    }
    motor_ctrl::set_powers(t, 50, 40);
    //motor_ctrl::set(1, 50);
    delay(1000);
    Serial.println(motor_ctrl::power_info());
}
