#ifndef ROBO_ECHO_H
#define ROBO_ECHO_H

#ifdef ARDUINO

namespace robo {

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

}

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_ECHO_H */