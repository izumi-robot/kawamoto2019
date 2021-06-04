"""
ボードについてるLEDをチカらせる
https://micropython-docs-ja.readthedocs.io/ja/latest/library/machine.Pin.html
"""

from machine import Pin
from time import sleep_ms

led = Pin(25, Pin.OUT)

while True:
    led.toggle()
    sleep_ms(500)
