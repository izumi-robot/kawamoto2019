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

} // namespace interrupt

template <int in_pin> class Interrupt {
    private:
    volatile bool _state = false;

    Interrupt() {}
    Interrupt(const Interrupt&) {}
    ~Interrupt() {}
    Interrupt& operator=(const Interrupt&) {}

    void callback() { _state = !_state; }

    public:
    static Interrupt& instance() {
        static Interrupt ins;
        return ins;
    }

    void setup() {
        pinMode(in_pin, INPUT);
        attachInterrupt(digitalPinToInterrupt(in_pin), callback, RISING);
    }

    inline bool state() { return _state; }

    bool changed() {
        static bool s = false;
        bool ans = s != _state;
        s = _state;
        return ans;
    }
};

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_INTERRUPT_H */