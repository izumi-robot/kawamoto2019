/**
 * @file bno055.ino
 * @brief BNO055ラッパーの使用例
 */

#include <robo2019.h>

//  Adafruit_BNO055(id, addr)
robo::BNO055 bno055( 0, 0x28);

void setup()
{
    Serial.begin(9600);
    Serial.println("start");
    bno055.setup();
}

void loop()
{
    // BNOが接続されているか確認
    if (!bno055.detected()) Serial.println("bno not detected");
    /**
     * 現在向いている方向を取得
     * 最初に向いていた方向を0としてラジアン(-PI以上PI以下)、反時計回りが正で表現
     */
    float dir = bno055.get_geomag_direction();
    // 度数法(-180以上180以下)で表示
    Serial.println(dir * 180 / PI);
    delay(1000);
}
