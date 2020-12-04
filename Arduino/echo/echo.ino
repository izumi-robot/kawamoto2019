class Echo {
    private:
    int input_pin, order_pin, result;

    public:
    Echo(int i, int o) : input_pin(i), order_pin(o) {}

    void setup() {
        pinMode(input_pin, INPUT);
        pinMode(order_pin, OUTPUT);
    }

    int read() {
        digitalWrite(order_pin, LOW);
        delayMicroseconds(10);
        digitalWrite(order_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(order_pin, LOW);
        result = pulseIn(input_pin, HIGH) / 60;
        return result;
    }

    inline int getReault() { return result; }
};

Echo echo(4, 3);

void setup() {
    Serial.begin(9600);
    echo.setup();
}

void loop() {
    Serial.println(echo.read());
    delay(1000);
}