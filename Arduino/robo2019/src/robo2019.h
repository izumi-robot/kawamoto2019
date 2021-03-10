/**
 * @file robo2019.h
 * @brief 自作ライブラリのエントリーポイント
 */

#ifndef ROBO2019_H
#define ROBO2019_H

#ifdef ARDUINO

#include "util.h"
#include "i2c.h"
#include "vec2d.h"

#include "interrupt.h"
#include "echo.h"
#include "line_sensor.h"
//#include "pixy.h"
#include "openmv.h"
#include "motor.h"
#include "bno055.h"
#include "lcd.h"

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */

#endif /* ROBO2019_H */