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
    BNO_wrapper() : _bno(55) {}
    BNO_wrapper(const BNO_wrapper &) : _bno(55) {}
    ~BNO_wrapper() {}
    BNO_wrapper& operator=(const BNO_wrapper &) {}

public:
    static BNO_wrapper& instance(void);
    void setup(void);
    double get_direction(void);
    Adafruit_BNO055& bno(void);
};

BNO_wrapper BNO_wrapper::_singleton;

BNO_wrapper& BNO_wrapper::instance()
{
    return BNO_wrapper::_singleton;
}

void BNO_wrapper::setup()
{
    this->_started = this->_bno.begin();
    this->_bno.setExtCrystalUse(true);
}

double BNO_wrapper::get_direction()
{
    if (!this->_started) { return 0.; }
    double dir_degree = this->_bno.getVector(Adafruit_BNO055::VECTOR_EULER).x();
    double dir_radian = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree : dir_degree - 360
    ) * -PI / 180;
    return dir_radian;
}

Adafruit_BNO055& BNO_wrapper::bno()
{
    return this->_bno;
}

BNO_wrapper &bno_wrapper = BNO_wrapper::instance();

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_BNO055_H */