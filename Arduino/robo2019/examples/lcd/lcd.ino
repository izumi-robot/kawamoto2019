/**
 * @file lcd.ino
 * @brief LCD(液晶ディスプレイ)の使用例
 */

#include <robo2019.h>

// LCD(I2Cアドレス, 列数, 行数)
robo::LCD lcd = robo::LCD(0x27, 16, 2);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Hello, world!");
    lcd.setCursor(0, 1);
    lcd.print("LCD (^^)/");
}

void loop()
{
    int t = millis() / 1000;
    lcd.setCursor(10, 1);
    lcd.print(t);
}