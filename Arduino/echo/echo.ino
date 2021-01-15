#include <echo.h>

robo::Echo e(2, 3);

void setup() {
    e.setup();
    Serial.begin(9600);
}

void loop() {
    Serial.println(e.read());
    delay(1000);
}