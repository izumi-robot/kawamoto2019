/**
 * @file robo2019.h
 * @brief 自作ライブラリのエントリーポイント
 */

#ifndef ROBO2019_H
#define ROBO2019_H

#ifdef ARDUINO

#include "src/util.h"
#include "src/i2c.h"
#include "src/vec2d.h"

#include "src/interrupt.h"
#include "src/echo.h"
#include "src/line_sensor.h"
//#include "src/pixy.h"
#include "src/openmv.h"
#include "src/motor.h"
#include "src/bno055.h"

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_H */