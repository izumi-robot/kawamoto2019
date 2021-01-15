#include <robo2019.h>

void setup()
{
    Serial.begin(9600);
    robo::bno_wrapper.setup();
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