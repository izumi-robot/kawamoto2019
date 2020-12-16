#ifndef ROBO2019_BNO055_H
#define ROBO2019_BNO055_H

#ifdef ARDUINO

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

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

    double get_direction() {
        if (!started) {
            return 0.;
        }
        double d = bno.getVector(Adafruit_BNO055::VECTOR_EULER).x();
        // -180 <= d <= 180
        d -= 180;
        // 0->180, 180->0, -45->-135
        d = d >= 0 ? 180 - d : -(180 + d);
        // 度数法からラジアン
        d = d * PI / 180;
        return d;
    }
} // namespace bno055

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_BNO055_H */