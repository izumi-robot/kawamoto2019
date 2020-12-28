#ifndef ROBO_INTERRUPT_H
#define ROBO_INTERRUPT_H

#ifdef ARDUINO

// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

namespace robo {

template <int in_pin>
class Interrupt {
    private:
    static volatile bool _state = false;

    Interrupt() {}
    Interrupt(const Interrupt&) {}
    ~Interrupt() {}
    Interrupt& operator=(const Interrupt&) {}

    static void callback() { _state = !_state; }

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