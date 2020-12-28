#include <robo2019.h>

robo::Echo e(6, 7);

void setup() {
    e.setup();
    Serial.begin(9600);
}

void loop() {
    Serial.println(e.read());
    delay(1000);
}

// const int pin = LED_BUILTIN;

// bool b = false;


// void setup() {
//     Serial.begin(9600);
//     pinMode(pin, OUTPUT);
// }


// void loop() {
//     if (b) {
//         digitalWrite(pin, HIGH);
//         Serial.println("on");
//     } else {
//         digitalWrite(pin, LOW);
//         Serial.println("off");
//     }
//     delay(500);
//     b = !b;
// }