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

    void set_direction(double rad, int v=40) {
        double l, r, c = cos(rad), s = sin(rad), root2 = sqrt(2);
        l = v * (c + s) / root2;
        r = v * (c - s) / root2;
        int il = int(l), ir = int(r);
        set(1, ir); set(2, il); set(3, il); set(4, ir);
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