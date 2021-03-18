#include <Arduino.h>
#include "bno055.h"

void robo::BNO055::setup()
{
    _detected = Adafruit_BNO055::begin();
    Adafruit_BNO055::setExtCrystalUse(true);
}

double robo::BNO055::get_geomag_direction()
{
    if (!_detected) { return 0.; }
    double dir_degree = Adafruit_BNO055::getVector(Adafruit_BNO055::VECTOR_EULER).x();
    double dir_radian = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree
        : dir_degree - 360
    ) * -PI / 180;
    return dir_radian;
}
void robo::BNO055::get_geomag_direction(double *dst)
{
    if (dst == NULL) return;
    double &res = *dst;
    if (!_detected) {
        res = 0.;
        return;
    }
    double dir_degree = Adafruit_BNO055::getVector(Adafruit_BNO055::VECTOR_EULER).x();
    res = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree
        : dir_degree - 360
    ) * -PI / 180;
}

bool robo::BNO055::detected()
{
    return _detected;
}