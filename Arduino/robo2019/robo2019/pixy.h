#ifndef ROBO_PIXY_H
#define ROBO_PIXY_H

#ifdef ARDUINO

#include <ArxContainer.h>

#define PIXY_I2C


#ifdef PIXY_I2C

#include <Pixy2I2C.h>
using PIXY = Pixy2I2C;

#else /* PIXY_I2C */
#ifdef PIXY_UART

#include <Pixy2UART.h>
using PIXY = Pixy2UART;

#else /* PIXY_UART */
#ifdef PIXY_SPI

#include <Pixy2SPI_SS.h>
using PIXY = Pixy2SPI_SS;

#else /* PIXY_SPI */

#include <SPI.h>
#include <Pixy2.h>
using PIXY = Pixy2;

#endif /* PIXY_SPI */
#endif /* PIXY_UART */
#endif /* PIXY_I2C */

#include "vec2d.h"

namespace robo {

namespace pixy {
    using Camera_pos = robo::V2_int;

    PIXY pixy;
    constexpr int window_width = 320, window_height = 200;
    const Camera_pos center{145, 135};

    void setup() { pixy.init(); }

    int update() { return pixy.ccc.getBlocks(); }

    Camera_pos get_pos(int i, const Camera_pos &default_value)
    {
        int l = update();
        if (l == 0) { return default_value; }
        const Block &block = pixy.ccc.blocks[i];
        return Camera_pos{
            int(block.m_x),
            int(block.m_y)
        };
    }
    Camera_pos get_pos(int i) { return get_pos(i, Camera_pos{0, 0}); }
    Camera_pos get_pos() { return get_pos(0); }
    Camera_pos get_pos(const Camera_pos &default_value) { return get_pos(0, default_value); }

    inline robo::V2_double cam_pos2real_pos(const Camera_pos &cam_pos)
    {
        return robo::V2_double{
            double( cam_pos.y - center.y),
            double(-cam_pos.x + center.x)
        };
    }

    inline double pos2angle(const Camera_pos &pos)
    {
        return cam_pos2real_pos(pos).angle();
    }

    inline Camera_pos real_pos2cam_pos(const robo::V2_double &real_pos)
    {
        return Camera_pos{
            int(-real_pos.y + center.x),
            int( real_pos.x + center.y)
        };
    }

    void log_blocks()
    {
        int l = pixy.ccc.getBlocks();
        for (int i = 0; i < l; ++i) { pixy.ccc.blocks[i].print(); }
    }

    namespace ball_tracer
    {
        Camera_pos last_pos{0, 0};
        bool started = false;
        double last_time = 0;
        int undetect_count = 0;

        Camera_pos calc_pos(const robo::V2_double &velocity)
        {
            int len = pixy.ccc.numBlocks;
            double t = millis() / 1000.0;
            double diff_t = t - last_time;
            bool detected = len > 0;
            if (detected) { undetect_count = 0; }
            else          { undetect_count++; }
            last_time = t;
            if (!started) {
                if (detected) {
                    last_pos = get_pos();
                    return last_pos;
                } else {
                    return Camera_pos{0, 0};
                }
            }
            if (detected) {
                struct {
                    int index = 0;
                    double diff = -1;
                } nearest;
                for (int i = 0; i < len; ++i) {
                    double d = (get_pos(i) - last_pos).mag();
                    if (nearest.diff < 0 || d < nearest.diff) {
                        nearest.index = i;
                        nearest.diff = d;
                    }
                }
                last_pos = get_pos(nearest.index);
            } else {
                robo::V2_double re_pos = cam_pos2real_pos(last_pos) + velocity * diff_t;
                last_pos = real_pos2cam_pos(re_pos);
            }
            return last_pos;
        }
    }
}

}

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_PIXY_H */