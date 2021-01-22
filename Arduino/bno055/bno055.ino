#include <robo2019.h>
#include <LiquidCrystal_I2C.h>

using robo::motor;
using robo::bno_wrapper;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);
    motor.setup();
    bno_wrapper.setup();
    lcd.init();
    lcd.backlight();
}

double abs_d(double d)
{
    return d > 0 ? d : -d;
}

void loop() {
    double d = bno_wrapper.get_direction();
    double abd = abs_d(d);
    if (d < -PI / 6 || PI / 6 < d)
    {
        motor.set.rotate(d > 0, abd * 50 / PI + 10);
    } else {
        motor.set.stop();
    }
    if (millis() % 100 == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(d * 180 / PI);
    }
    delay(10);
}