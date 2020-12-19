#ifndef ROBO_PIXY_H
#define ROBO_PIXY_H

#ifdef ARDUINO

#include <ArxContainer.h>
#include <Pixy2.h>
#include <SPI.h>
#include "vec2d.h"

namespace robo {

namespace pixy {
    Pixy2 pixy;
    const int window_width = 320, window_height = 200;

    void setup() {
        pixy.init();
    }

    int update() {
        return pixy.ccc.getBlocks();
    }

    V2_int get_pos(int i) {
        int l = update();
        if (l == 0) {
            return V2_int(0, 0);
        }
        int x = pixy.ccc.blocks[i].m_x;
        int y = pixy.ccc.blocks[i].m_y;
        return V2_int{x - window_width / 2, y - window_height / 2};
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

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_PIXY_H */