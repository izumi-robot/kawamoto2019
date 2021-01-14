#ifndef ROBO2019_BNO055_H
#define ROBO2019_BNO055_H

#ifdef ARDUINO

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


namespace robo {

class BNO_wrapper
{
private:
    static BNO_wrapper _singleton;
    bool _started;
    Adafruit_BNO055 _bno;

private:
    BNO_wrapper() {}
    BNO_wrapper(const BNO_wrapper &) {}
    ~BNO_wrapper() {}
    BNO_wrapper& operator=(const BNO_wrapper &) {}

public:
    static BNO_wrapper& instance();
    void setup();
    double get_direction();
    const Adafruit_BNO055& bno();
};

BNO_wrapper BNO_wrapper::_singleton;

BNO_wrapper& BNO_wrapper::instance()
{
    return BNO_wrapper::_singleton;
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_BNO055_H */