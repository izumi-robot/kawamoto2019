#include <robo2019.h>

// Echo(Echo-pin, Trig-pin)
robo::Echo echo(2, 3);

void setup()
{
    Serial.begin(9600);
    echo.setup();
}

void loop()
{
    Serial.println(echo.read());
    delay(1000);
}