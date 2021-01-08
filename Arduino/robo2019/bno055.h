#ifndef ROBO2019_BNO055_H
#define ROBO2019_BNO055_H

#ifdef ARDUINO

#include <Wire.h>
#include <Adafruit_BNO055.h>


namespace robo {

namespace bno055 {
    Adafruit_BNO055 bno = Adafruit_BNO055(55);
    bool started = false;

    void setup()
    {
        started = bno.begin();
        if (!started) {
            Serial.println("could not connect");
        }
        bno.setExtCrystalUse(true);
    }

    double get_direction()
    {
        if (!started) {
            return 0.;
        }
        double dir_x = bno.getVector(Adafruit_BNO055::VECTOR_EULER).x();
        // -180 <= d <= 180
        dir_x -= 180;
        // 0 -> 180, 180 -> 0, -45 -> -135
        dir_x = dir_x >= 0 ? 180 - dir_x : -(180 + dir_x);
        // 度数法からラジアン
        dir_x = dir_x * PI / 180;
        return dir_x;
    }
} // namespace bno055

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_BNO055_H */