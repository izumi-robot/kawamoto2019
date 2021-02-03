#include <robo2019.h>

using robo::motor;
constexpr int power = 60;

void setup()
{
    Serial.begin(9600);
    motor.setup();
}

void loop()
{
    motor.set.all_motors(power, power, power, power);
    delay(500);
    motor.set.rotate(true, power);
    delay(500);
    motor.set.velocity(0, -power);
    delay(500);
    motor.set.direction_and_speed(PI / 4, power);
    delay(500);
    motor.set.stop();
    delay(5000);
}

// void loop()
// {
//     // 5秒周期で繰り返す
//     int t = millis() % 5000;
//     // 0~1: 前進
//     if (0 <= t < 1000)
//     {
//         motor.set.all_motors(power, power, power, power);
//     }
//     // 1~2: 右回転
//     else if (t < 2000)
//     {
//         motor.set.rotate(true, power);
//     }
//     // 2~3: 右に進む
//     else if (t < 3000)
//     {
//         motor.set.velocity(0, -power);
//     }
//     // 3~4: 左前に進む
//     else if (t < 4000)
//     {
//         motor.set.direction_and_speed(PI / 4, power);
//     }
//     // 4~5: 停止
//     else if (t < 5000)
//     {
//         motor.set.stop();
//     }
//     if (t % 1000 < 10)
//     {
//         Serial.println(t);
//         Serial.println(motor.get.info());
//     }
//     delay(10);
// }