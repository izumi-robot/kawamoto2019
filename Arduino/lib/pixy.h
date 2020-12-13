#ifndef ROBO_PIXY_H
#define ROBO_PIXY_H

#include <ArxContainer.h>
#include <Pixy2.h>
#include <SPI.h>
#include "vec2d.h"

namespace robo {

namespace pixy_util {
    Pixy2 pixy;
    const int window_width = 320, window_height = 200;

    void setup() {
        pixy.init();
    }

    double pos2angle(int m_x, int m_y) {
        double x = m_x - window_width / 2;
        double y = m_y - window_height / 2;
        double ans = atan2(y, x);
        return ans;
    }

    double pos2angle(const robo::Vector2D<double> &pos) {
        using dvec = robo::Vector2D<double>;
        dvec np = pos - dvec(window_width / 2., window_height / 2.);
        double ans = np.angle() + PI*3/4;
        if (ans >= PI) {
            ans -= PI;
        }
        return ans;
    }

    void log_blocks() {
        Serial.println("begin robo::pixy_util::log_blocks");

        int l = pixy.ccc.getBlocks();
        for (int i = 0; i < l; ++i) {
            pixy.ccc.blocks[i].print();
        }
        Serial.println("end   robo::pixy_util::log_blocks");
    }
}

}

#endif /* ROBO_PIXY_H */