#include <robo2019.h>

void setup()
{
    Serial.begin(9600);
    robo::bno_wrapper.setup();
}

void loop()
{
    // 最初の方向からの差分を取得
    // 反時計回りが正
    // ラジアン(-PI以上PI以下)
    double dir = robo::bno_wrapper.get_direction();
    // 度数法(-180以上180以下)
    Serial.println(dir * 180 / PI);
    delay(1000);
}