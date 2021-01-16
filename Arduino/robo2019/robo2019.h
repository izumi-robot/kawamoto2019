#ifndef ROBO2019_H
#define ROBO2019_H

#ifdef ARDUINO

#include "robo2019/util.h"
#include "robo2019/vec2d.h"
#include "robo2019/interrupt.h"
#include "robo2019/echo.h"
#include "robo2019/line_sensor.h"
#include "robo2019/pixy.h"
#include "robo2019/motor.h"
#include "robo2019/bno055.h"

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_H */