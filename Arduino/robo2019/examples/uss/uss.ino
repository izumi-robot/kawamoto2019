/**
 * @file uss.ino
 * @brief 超音波センサーを使う例
 */

#include <robo2019.h>

// USSensor(Echo-pin, Trig-pin)
robo::USSensor echo(3, 4);

void setup()
{
    Serial.begin(9600);
    echo.setup();
}

void loop()
{
    Serial.println(echo.read());
    delay(1000);
}