#ifndef ROBO_INTERRUPT_H
#define ROBO_INTERRUPT_H

#ifdef ARDUINO

// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

namespace robo {

#define TMP template<int in_pin>
#define INTERRUPT Interrupt<in_pin>

TMP class Interrupt {
private:
    static volatile bool _state;
    static Interrupt _singleton;

    Interrupt() {}
    Interrupt(const Interrupt &) {}
    ~Interrupt() {}
    Interrupt& operator=(const Interrupt &) {}

    static void callback();

public:
    static Interrupt& instance();
    void setup();
    inline bool state();
    bool changed();
};

TMP void INTERRUPT::callback()
{
    INTERRUPT::_state = !INTERRUPT::_state;
}

TMP INTERRUPT& INTERRUPT::instance()
{
    return INTERRUPT::_singleton;
}

TMP void INTERRUPT::setup()
{
    pinMode(in_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(in_pin), callback, RISING);
}

TMP bool INTERRUPT::state()
{
    return _state;
}

TMP bool INTERRUPT::changed()
{
    static bool pre_state;
    bool ans = pre_state != _state;
    pre_state = _state;
    return ans;
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO_INTERRUPT_H */