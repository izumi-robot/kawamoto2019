#include <robo2019.h>
#include <ArxContainer.h>

// robo::Echo e_left(), e_right();

class LineSensor
{
private:
    uint8_t in_pin;
public:
    LineSensor(uint8_t input_pin): in_pin(input_pin) {}

    void setup()
    {
        pinMode(in_pin, INPUT);
    }

    int read()
    {
        return analogRead(in_pin);
    }
};

arx::vector<double> ds{0, PI, -PI / 2, PI / 2, -PI / 6, PI * 5 / 6};
LineSensor line_sensors[] = {
    LineSensor(1),
    LineSensor(3),
    LineSensor(5)
};

int black_border = 0;

bool iswhite(int v)
{
    return v > 650;
}

void setup() {
    Serial.begin(9600);
    robo::motor.setup();
    robo::bno055::setup();
    for (LineSensor sensor : line_sensors) {
        sensor.setup();
        black_border += sensor.read();
    }
    black_border /= 3;
}

void loop() {
    double facing_dir, mov_dir;
    int line_value;

    BNO055: {
        facing_dir = robo::bno055::get_direction();
    }

    ROTATE: {
        if (abs(facing_dir) > PI / 6) {
            bool cond = facing_dir > 0;
            robo::motor.set.rotate(cond, (int8_t)(abs(50 * facing_dir / PI)) + 10);
        }
        goto END;
    }

    LINE: {
        int left  = line_sensors[0].read(),
            right = line_sensors[1].read(),
            back  = line_sensors[2].read();
        if (iswhite(left)) {
            mov_dir = -PI / 2;
            goto MOVE;
        } else if (iswhite(right)) {
            mov_dir = PI / 2;
            goto MOVE;
        } else if (iswhite(back)) {
            mov_dir = 0;
            goto MOVE;
        }
    }

    DEFAULT_DIR: {
        //int i = millis() / 1000 % 6;
        mov_dir = -PI / 2;
    }

    MOVE: {
        robo::motor.set.direction_and_speed(mov_dir, 70);
    }

    END:
    //Serial.println(robo::motor.get.info());
    delay(10);
}