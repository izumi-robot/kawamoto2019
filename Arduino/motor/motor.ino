#include <robo2019.h>
#include <ArxContainer.h>

using namespace robo;

bool t = false;
const int pin = 4;
arx::vector<double> dirs{0, PI, }

void setup() {
    Serial.begin(9600);
    motor::setup();
}

void loop() {

    motor::set_direction(0);
    Serial.println(motor::info());
    delay(1000);

    motor::set_direction(PI);
    Serial.println(motor::info());
    delay(1000);

    motor::set_direction(PI/2);
    Serial.println(motor::info());
    delay(1000);

    motor::set_direction(-PI/2);
    Serial.println(motor::info());
    delay(1000);

    motor::set_direction(PI/4);
    Serial.println(motor::info());
    delay(1000);

    motor::set_direction(-PI*3/4);
    Serial.println(motor::info());
    delay(1000);

    motor::stop();
    delay(5000);
}