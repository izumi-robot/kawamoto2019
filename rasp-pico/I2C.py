"""
ダイセンのMCBでSoftI2C
scl=9, sda=8
https://micropython-docs-ja.readthedocs.io/ja/latest/library/machine.SoftI2C.html
"""

from machine import SoftI2C, Pin
from utime import sleep_ms

i2c = SoftI2C(0, scl=Pin(9), sda=Pin(8))
#i2c.init(scl=Pin(9), sda=Pin(8))

def set_power(power: int, id: int = 0x14) -> None:
    d = 1 if power < 0 else 0
    p = (d << 7) | (127 & abs(power))
    data = bytes([p] + [128] * 5)
    sleep_ms(100)
    i2c.writeto(id, data)
