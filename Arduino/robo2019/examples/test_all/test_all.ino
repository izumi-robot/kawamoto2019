/**
 * @file test_all.ino
 * @brief 全部一気に検証
 */

#include <robo2019.h>
#include <SoftwareSerial.h>

// robo::openmvのエイリアス
namespace omv {
    using namespace robo::openmv;
}

// robo::move_infoのエイリアス
namespace inf {
    using namespace robo::move_info;

    using Infos = MoveInfo*[];
}

robo::BNO055 bno = robo::BNO055();

using Int2 = robo::Interrupt<2, RISING>;
Int2 & i2 = Int2::instance();

robo::LineSensor ls(2);

SoftwareSerial motor_ser = SoftwareSerial(12, 13);
robo::Motor motor(&motor_ser);

inf::Infos infos = {
    new inf::Stop(),
    new inf::Rotate(true, 10),
    new inf::Translate(70, -50)
};

omv::Reader mv_reader = omv::Reader(0x12);

robo::USSensor uss(3, 4);

robo::V2_int vec{1, -1};

void setup()
{
    Serial.begin(9600);
    motor_ser.begin(19200);

    bno.setup();
    if (bno.detected()) Serial.println(F("bno detected"));

    i2.setup();

    ls.setup();

    motor.stop();

    mv_reader.setup();

    uss.setup();

    Serial.println(vec.to_string());
}

void loop()
{
    char buff[256] = "";
    char * ptr = buff;
    int16_t value;
    int16_t sec = millis() / 1000;

    strcat_P(ptr, PSTR("direction from bno: "));
    ptr += 20;

    dtostrf(bno.get_geomag_direction(), 5, 3, ptr);
    ptr += 5;
    *(ptr++) = '\n';

    if (i2.changed()) {
        strcat_P(ptr, PSTR("inerrupt changed.\n"));
        ptr += 18;
    }
    ptr += sprintf_P(ptr, PSTR("interrupt state: %u\n"), i2.state());

    value = ls.read();
    ptr += sprintf_P(
        ptr,
        PSTR("line sensor: %u, %s\n"),
        value,
        robo::LineSensor::iswhite(value) ? PSTR("white") : PSTR("black")
    );

    infos[sec % 3]->apply(motor);
    ptr += motor.info(ptr);

    omv::Frame * frame = mv_reader.read_frame();
    if (frame != NULL) {
        ptr += frame->to_string(ptr);
        delete frame;
    }

    value = uss.read();
    ptr += sprintf_P(ptr, PSTR("us sensor: %d\n"), value);
}
