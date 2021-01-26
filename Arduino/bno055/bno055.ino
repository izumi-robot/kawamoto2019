#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 _bno055(55);

void setup()
{
    Serial.begin(9600);
    if (_bno055.begin()) {
        Serial.println("detected");
        _bno055.setExtCrystalUse(true);
    }
}

#include <robo2019.h>

//using robo::_bno055;
using imu_v3 = imu::Vector<3>;

void printVector(const imu_v3 &vec)
{
    char buffer[64];
    sprintf(buffer, "(%+3.2f, %+3.2f, %3.2f)\n", vec.x(), vec.y(), vec.z());
    Serial.print(buffer);
}

void printQuat(const imu::Quaternion &quat)
{
    char buffer[64];
    sprintf(buffer, "(%+3.2f, %+3.2f, %+3.2f, %+3.2f)\n", quat.x(), quat.y(), quat.x(), quat.w());
    Serial.println(buffer);
}

// void setup()
// {
//     Serial.begin(9600);
//     _bno055.setup();
// }

void loop()
{
    Serial.println("================");

    Serial.print("Euler: ");
    printVector(_bno055.getVector(Adafruit_BNO055::VECTOR_EULER));

    Serial.print("Gyroscope: ");
    printVector(_bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE));

    Serial.print("Quaternion: ");
    printQuat(_bno055.getQuat());

    delay(1000);
}