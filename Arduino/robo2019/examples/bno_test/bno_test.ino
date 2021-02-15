#include <robo2019.h>

void setup()
{
    Serial.begin(9600);
    while (!Serial) delay(1);
    Serial.println("start");
    robo::bno055.setup();
}

void loop()
{
    if (!robo::bno055.detected()) Serial.println("bno not detected");
    // 最初の方向からの差分を取得
    // 反時計回りが正
    // ラジアン(-PI以上PI以下)
    double dir = robo::bno055.get_geomag_direction();
    // 度数法(-180以上180以下)で表示
    Serial.println(dir * 180 / PI);
    delay(1000);
}