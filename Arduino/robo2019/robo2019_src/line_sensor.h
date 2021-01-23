#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#ifdef ARDUINO

namespace robo {

class LineSensor
{
private:
    static int _white_border;
    int _in_pin;
private:
    LineSensor() {}
public:
    static int  white_border();
    static void white_border(int);
    static bool iswhite(int);

    LineSensor(int i) : _in_pin(i) {}
    void setup();
    int read();
    int in_pin();
};

int LineSensor::_white_border = 300;

int LineSensor::white_border()
{
    return _white_border;
}

void LineSensor::white_border(int new_border)
{
    _white_border = new_border > 0 ? _white_border : new_border;
}

bool LineSensor::iswhite(int c)
{
    return c >= _white_border;
}

void LineSensor::setup()
{
    pinMode(_in_pin, INPUT);
}

int LineSensor::read()
{
    return analogRead(_in_pin);
}

int LineSensor::in_pin()
{
    return _in_pin;
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* LINE_SENSOR_H */