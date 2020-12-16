#ifndef ROBO_MOTOR_H
#define ROBO_MOTOR_H

#ifdef ARDUINO

#include "util.h"
#include "vec2d.h"

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

    namespace set {

        // assert : m_id = 1,2,3,4 && abs(power) <= 100
        void one_motor(int m_id, int power) {
            String dest = power_str(m_id, power);
            Serial1.println(dest);
            powers[m_id - 1] = power;
        }

        void velocity(const double &vx, const double &vy) {
            double root2 = sqrt(2.);
            int fl = int((vy - vx) / root2), fr = int((vy + vx) / root2);
            one_motor(1, fr); one_motor(2, fl); one_motor(3, fl); one_motor(4, fr);
        }

        void velocity(const robo::V2_double &vel) {
            velocity(vel.x, vel.y);
        }

        void left_right(const double &left, const double &right) {
            one_motor(1, left); one_motor(2, right); one_motor(3, left); one_motor(4, right);
        }

        void rotate(bool clockwise, int vel=100) {
            int d = clockwise ? 1 : -1;
            left_right(vel * d, -vel * d);
        }

        void circular(const double &rotate_vel, const int &vel=100);
    } // namespace set

    void stop() {
        for (int i = 1; i <= 4; ++i) {
            set::one_motor(i, 0);
        }
    }

    void setup(bool serial1_init=true) {
        if (serial1_init) {
            Serial1.begin(19200);
        }
        stop();
    }
};

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_MOTOR_H */