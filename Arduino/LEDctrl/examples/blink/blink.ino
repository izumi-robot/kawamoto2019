/**
 * @file blink.ino
 * @brief Lチカ
 */

#include <LED.h>

// LEDはデジタルピン2に接続
LED led = LED(2);

void setup() {
    Serial.begin(9600);
    led.setup();
}

void loop() {
    led.toggle();
    // Fマクロ https://qiita.com/ma2shita/items/89ed5b74698d4922efdd
    Serial.println(led.get_state() ? F("on") : F("off"));
    delay(1000);
}
