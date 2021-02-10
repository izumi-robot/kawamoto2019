/**
 * @file robo2019.h
 * @brief 自作ライブラリのエントリーポイント
 */

#ifndef ROBO2019_H
#define ROBO2019_H

#ifdef ARDUINO

#include "robo2019_src/util.h"
#include "robo2019_src/i2c.h"
#include "robo2019_src/vec2d.h"

#include "robo2019_src/interrupt.h"
#include "robo2019_src/echo.h"
#include "robo2019_src/line_sensor.h"
//#include "robo2019_src/pixy.h"
#include "robo2019_src/openmv.h"
#include "robo2019_src/motor.h"
#include "robo2019_src/bno055.h"

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_H */