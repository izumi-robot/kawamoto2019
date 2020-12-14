#ifndef ROBO_MOTOR_H
#define ROBO_MOTOR_H

#ifdef ARDUINO

#include "util.h"

namespace robo {

namespace motor {
    /*
        motors' positions:
        { left-up, right-up, left-bottom, right-bottom }
     */
    int powers[] = {0, 0, 0, 0};

    String power_str(int m_id, int power) {
        // R: front?
        String d = power < 0 ? "F" : "R";
        String p = String(abs(power));
        robo::str_rjust(p, 3, "0");
        return String(m_id) + d + p;
    }

    // assert : m_id = 1,2,3,4 && abs(power) <= 100
    void set(int m_id, int power) {
        String dest = power_str(m_id, power);
        Serial1.println(dest);
        powers[m_id - 1] = power;
    }

    void stop() {
        for (int i = 1; i <= 4; ++i) {
            set(i, 0);
        }
    }

    void setup(bool serial1_init=true) {
        if (serial1_init) {
            Serial1.begin(19200);
        }
        stop();
    }

    // set motors' powers from radian (direction)
    // assert : -PI <= rad && rad <= PI && max_power >= min_power >= 0

    void set_direction(double rad, int ma_p=40) {
        double l, r, c = cos(rad), s = sin(rad);
        if (-PI/2 < rad && rad < PI/2) {
            l = c + s;
            r = c - s;
        } else {
            l = c - s;
            r = c + s;
        }
        int il = int(ma_p * l), ir = int(ma_p * r);
        set(1, ir); set(2, il); set(3, il); set(4, ir);
    }

    void _set_direction(double rad, int max_power=90, int min_power=70) {
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
        if (-PI/2 <= rad && rad <= PI/2) {
            r = f(PI/4 + rad);
            l = f(PI/4 - rad);
        } else {
            r = -f(PI*5/4 - rad);
            l = -f(rad - PI*3/4);
        }
        set(1, r); set(2, l); set(3, l); set(4, r);
    }

    String info() {
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

}

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_MOTOR_H */