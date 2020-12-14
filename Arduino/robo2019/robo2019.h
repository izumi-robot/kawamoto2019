#ifndef ROBO2019_H
#define ROBO2019_H

#ifdef ARDUINO

#include "util.h"
#include "vec2d.h"
#include "interrupt.h"
#include "echo.h"
#include "pixy.h"
#include "motor.h"

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_H */