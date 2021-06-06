/*
Raspberry Pi PicoとI2C通信するプログラム
pico側のプログラムはrobo/rasp-pico/I2c.pyを参照
*/

#include <Wire.h>

bool led_state;

void on_read(int data_len) {
    led_state = !led_state;
    digitalWrite(LED_BUILTIN, led_state);
    for (int i = 0; i < data_len; ++i) {
        Wire.read();
    }
}

void setup() {
	Wire.begin(0x18);
    pinMode(LED_BUILTIN, OUTPUT);
    Wire.onReceive(on_read);
    led_state = false;
    digitalWrite(LED_BUILTIN, led_state);
}

void loop() {
	// do nothing
}
