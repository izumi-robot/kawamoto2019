#include <robo2019.h>

using robo::Echo;

Echo echo(8, 4);

void setup() {
    Serial.begin(9600);
    echo.setup();
}

void loop() {
    Serial.println(echo.read());
    delay(1000);
}