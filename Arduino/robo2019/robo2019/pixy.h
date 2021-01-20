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

namespace pixy {
    using Camera_pos = robo::V2_int;

    PIXY pixy;
    constexpr int window_width = 320, window_height = 200;

    void setup() { pixy.init(); }

    int update() { return pixy.ccc.getBlocks(); }

    Camera_pos get_pos(int i, const Camera_pos &default_value)
    {
        int l = update();
        if (l == 0) { return default_value; }
        Block block = pixy.ccc.blocks[i];
        int x = block.m_x;
        int y = block.m_y;
        return Camera_pos{x, y};
    }
    Camera_pos get_pos(int i) { return get_pos(i, Camera_pos{0, 0}); }
    Camera_pos get_pos() { return get_pos(0); }
    Camera_pos get_pos(const Camera_pos &default_value) { return get_pos(0, default_value); }

    double pos2angle(const Camera_pos &pos)
    {
        double x = -pos.y + 135;
        double y =  pos.x - 145;
        return atan2(y, x);
    }

    void log_blocks()
    {
        Serial.println("begin robo::pixy::log_blocks");
        int l = pixy.ccc.getBlocks();
        for (int i = 0; i < l; ++i) { pixy.ccc.blocks[i].print(); }
        Serial.println("end   robo::pixy::log_blocks");
    }
}

}

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_PIXY_H */