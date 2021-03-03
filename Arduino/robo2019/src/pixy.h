/**
 * @file pixy.h
 * @brief Pixy2操作用の関数群
 */

#ifndef ROBO2019_PIXY_H
#define ROBO2019_PIXY_H

#ifdef ARDUINO

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

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo {

namespace pixy {
    using Camera_pos = robo::V2_int;

    PIXY pixy;
    constexpr int window_width = 320, window_height = 200;
    const Camera_pos center{145, 135};

    bool setup() { return !pixy.init(); }

    int8_t update()
    {
        // https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:ccc_api
        // int8_t getBlocks(bool wait [opt], uint8_t sigmap [opt], uint8_t maxBlocks [opt])
        return pixy.ccc.getBlocks(false, 255, 1);
    }

    Camera_pos get_pos(int i, const Camera_pos &default_value)
    {
        int l = pixy.ccc.numBlocks;
        if (l <= i) { return default_value; }
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

    void cam_pos2real_pos(robo::V2_double *dst, const Camera_pos &cam_pos)
    {
        dst->x = double( cam_pos.y - center.y);
        dst->y = double(-cam_pos.x + center.x);
    }

    inline double pos2angle(const Camera_pos &cam_pos)
    {
        return atan2(
            double(-cam_pos.x + center.x),
            double( cam_pos.y - center.y)
        );
    }

    void pos2angle(double *dst, const Camera_pos &cam_pos)
    {
        *dst = atan2(
            double(-cam_pos.x + center.x),
            double( cam_pos.y - center.y)
        );
    }

    inline Camera_pos real_pos2cam_pos(const robo::V2_double &real_pos)
    {
        return Camera_pos{
            int(-real_pos.y + center.x),
            int( real_pos.x + center.y)
        };
    }

    void real_pos2cam_pos(Camera_pos *dst, const robo::V2_double &real_pos)
    {
        dst->x = int(-real_pos.y + center.x);
        dst->y = int( real_pos.x + center.y);
    }

    void log_blocks()
    {
        int l = pixy.ccc.getBlocks();
        for (int i = 0; i < l; ++i) { pixy.ccc.blocks[i].print(); }
    }
} // namespace pixy

} // namespace robo

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */

#endif /* ROBO2019_PIXY_H */