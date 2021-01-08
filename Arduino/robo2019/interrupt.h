#ifndef ROBO_INTERRUPT_H
#define ROBO_INTERRUPT_H

#ifdef ARDUINO

// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

namespace robo {

template <int in_pin>
class Interrupt
{
private:
    static volatile bool _state;

    Interrupt() {}
    Interrupt(const Interrupt&) {}
    ~Interrupt() {}
    Interrupt& operator=(const Interrupt&) {}

    static void callback() { _state = !_state; }

public:
    static void setup()
    {
        pinMode(in_pin, INPUT);
        attachInterrupt(digitalPinToInterrupt(in_pin), callback, RISING);
    }

    static inline bool state() { return _state; }

    static bool changed()
    {
        static bool pre_state;
        bool ans = pre_state != _state;
        pre_state = _state;
        return ans;
    }
};

static volatile bool _state = false;

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_INTERRUPT_H */