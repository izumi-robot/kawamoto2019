"""
ArduinoとSoftI2C
scl=9, sda=8
Arduino側のプログラムはrobo/Arduino/pico/pico.inoを参照
https://micropython-docs-ja.readthedocs.io/ja/latest/library/machine.SoftI2C.html
"""

from machine import SoftI2C, Pin
from utime import sleep_ms

i2c = SoftI2C(scl=Pin(9), sda=Pin(8))
#i2c.init(scl=Pin(9), sda=Pin(8))
i2c.start()

arduino_addr = 0x18

def send():
    i2c.writeto(arduino_addr, b"a")

while True:
    send()
    sleep_ms(500)
