#ifndef ROBO_INTERRUPT_H
#define ROBO_INTERRUPT_H

#ifdef ARDUINO

// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

namespace robo {

namespace interrupt {
    int in_pin;
    volatile bool state = false;

    void setup(int);
    void callback();
    bool changed();
    bool check();

    void callback() {
        noInterrupts();
        Serial.println("changed");
        state = !state;
        interrupts();
    }

    void setup(int i=12) {
        Serial.println("robo::interrupt::setup");
        in_pin = i;

        pinMode(in_pin, INPUT);
        attachInterrupt(digitalPinToInterrupt(in_pin), callback, RISING);
    }

    bool changed() {
        static bool s = false;

        bool ans = s != state;
        s = state;
        return ans;
    }

    bool check() {
        static bool s = LOW;

        bool n = digitalRead(in_pin) == HIGH;
        bool changed = n != state;
        state = n;
        return changed;
    }

}

}

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_INTERRUPT_H */