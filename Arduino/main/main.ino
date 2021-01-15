#define PIXY_I2C

#include <LiquidCrystal_I2C.h>
#include <robo2019.h>

using robo::Echo;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Echo echo(0, 1);

void setup()
{
    Serial.begin(9600);
    echo.setup();
    return;
    robo::bno_wrapper.setup();
    lcd.init();
    lcd.backlight();
    robo::pixy::setup();
}

void loop()
{
    Serial.println(echo.read());
    goto END;
    String bno_info = String("bno055 ") + String(
        robo::bno_wrapper.get_direction() * 180 / PI
    );
    lcd.setCursor(0, 0);
    lcd.print(bno_info);
    robo::pixy::log_blocks();
    END:
    delay(1000);
}