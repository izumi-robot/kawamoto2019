/**
 * @file motor.ino
 * @brief MCB操作の例
 * @details ロボットの方向などの定義はrobo2019/README.mdを参照
 */

#include <robo2019.h>
#include <SoftwareSerial.h>


SoftwareSerial motor_serial(12, 13);

robo::Motor motor(&motor_serial);

constexpr int power = 60;

// 長ったらしいので省略
namespace inf {
    using namespace robo::move_info;
}

inf::MoveInfo * infos[] = {
    new inf::Translate(100, 0),
    new inf::Rotate(true, power),
    new inf::Translate(0, -power),
    new inf::Translate(robo::V2_float::from_polar_coord(PI / 4, power)),
    new inf::Stop()
};

void setup()
{
    motor_serial.begin(19200);
    Serial.begin(9600);
}

void loop()
{
    infos[0]->apply(motor);
    for (uint8_t i = 0; i < 5; i++) {
        delay(500);
        infos[i]->apply(motor);
        Serial.println(motor.info());
    }
    delay(5000);
}
