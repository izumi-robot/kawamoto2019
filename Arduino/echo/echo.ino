#include <robo2019.h>

robo::EchoSensor e = robo::EchoSensor(9, 8);

void setup() {
    e.setup();
    Serial.begin(9600);
}

void loop() {
    Serial.print("Read: ");
    Serial.println(e.read());
    delay(1000);
}