"""
ダイセンのMCB
tx=0, rx=1
"""

from machine import UART, Pin
from utime import sleep_ms

uart0 = UART(0, 19200, tx=Pin(0), rx=Pin(1))

cmds = [
    b"1R000\n",
    b"1F050\n",
    b"1R000\n",
    b"1R050\n"
]

i = 0

while True:
    uart0.write(cmds[i % 4])
    i += 1
    sleep_ms(500)
