const int LED_pin = 8;
const int in_pin = 12;

void setup() {
    pinMode(LED_pin, OUTPUT);
    pinMode(in_pin, INPUT);
    //Serial.begin(9600);
}

void loop() {
    if (check()) {
        digitalWrite(LED_pin, HIGH);
        for (int i = 0; i < 20; i++) {
            delay(100);
            check();
        }
        digitalWrite(LED_pin, LOW);
        for (int i = 0; i < 10; i++) {
            delay(100);
            check();
        }
    } else {
        delay(10);
        check();
    }
}

bool check() {
    static bool b = true;
    static int value = LOW;

    int v = digitalRead(in_pin);
    if (v != value) {
        value = v;
        if (value == HIGH) {
            b = !b;
        }
    }
    return b;
}