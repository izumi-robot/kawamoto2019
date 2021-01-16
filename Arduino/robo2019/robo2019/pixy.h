#ifndef ROBO_PIXY_H
#define ROBO_PIXY_H

#ifdef ARDUINO

#include <ArxContainer.h>

#define PIXY_I2C

#ifdef PIXY_I2C

    #include <Pixy2I2C.h>
    #define PIXY Pixy2I2C

#else /* PIXY_I2C */
#ifdef PIXY_UART

    #include <Pixy2UART.h>
    #define PIXY Pixy2UART

#else /* PIXY_UART */
#ifdef PIXY_SPI

    #include <Pixy2SPI_SS.h>
    #define PIXY Pixy2SPI_SS

#else /* PIXY_SPI */

    #include <SPI.h>
    #include <Pixy2.h>
    #define PIXY Pixy2

#endif /* PIXY_SPI */
#endif /* PIXY_UART */
#endif /* PIXY_I2C */

#include "vec2d.h"

namespace robo {

using robo::V2_int;

namespace pixy {
    PIXY pixy;
    const int window_width = 320, window_height = 200;

    void setup()
    {
        pixy.init();
    }

    int update()
    {
        return pixy.ccc.getBlocks();
    }

    V2_int get_pos(int i)
    {
        int l = update();
        if (l == 0) {
            return V2_int(0, 0);
        }
        int x = pixy.ccc.blocks[i].m_x;
        int y = pixy.ccc.blocks[i].m_y;
        return V2_int{x, y};
    }

    V2_int get_pos()
    {
        return get_pos(0);
    }

    double pos2angle(int m_x, int m_y)
    {
        double x = m_x - window_width / 2;
        double y = m_y - window_height / 2;
        double ans = atan2(y, x);
        return ans;
    }

    double pos2angle(const V2_int &pos)
    {
        V2_int np = pos - V2_int{window_width / 2, window_height / 2};
        double ans = np.angle() + PI * 3 / 4;
        if (ans >= PI) {
            ans -= PI;
        }
        return ans;
    }

    double pos2angle(const robo::V2_double &pos)
    {
        robo::V2_double np = pos - robo::V2_double{window_width / 2., window_height / 2.};
        double ans = np.angle() + PI * 3 / 4;
        if (ans >= PI) {
            ans -= PI;
        }
        return ans;
    }

    void log_blocks()
    {
        Serial.println("begin robo::pixy::log_blocks");

        int l = pixy.ccc.getBlocks();
        for (int i = 0; i < l; ++i) {
            pixy.ccc.blocks[i].print();
        }

        Serial.println("end   robo::pixy::log_blocks");
    }
}

}

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_PIXY_H */