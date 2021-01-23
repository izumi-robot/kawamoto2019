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
    // 5秒周期で繰り返す
    int t = millis() % 5000;
    // 0~1: 全身
    if (0 <= t < 1000)
    {
        motor.set.all_motors(power, power, power, power);
    }
    // 1~2: 左回転
    else if (t < 2000)
    {
        motor.set.rotate(true, power);
    }
    // 2~3: 前進
    else if (t < 3000)
    {
        motor.set.velocity(power * 2, 0);
    }
    // 3~4: 左前に進む
    else if (t < 4000)
    {
        motor.set.direction_and_speed(PI / 4, power);
    }
    // 4~5: 停止
    else if (t < 5000)
    {
        motor.set.stop();
    }
    if (t % 1000)
    {
        Serial.println(motor.get.info());
    }
    delay(100);
}