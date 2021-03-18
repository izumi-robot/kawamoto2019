uint8_t pin = 11;

void setup() {
    // put your setup code here, to run once:
    pinMode(pin, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin, LOW);
    delay(5000);
}
