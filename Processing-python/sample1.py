L = [
    0b00111100,
    0b01000010,
    0b10101001,
    0b10000001,
    0b11000011,
    0b01111110,
    0b00100100,
    0b00100010
]


def D(x, y, s):
    it = (
        (r, c)
        for r in range(8)
        for c in range(8)
    )
    for r, c in it:
        if not(L[r]&1<<c):
            continue
        rect(x + c * s, y + r * s, s, s)


def setup():
    size(720, 720)


def draw():
    clear()
    s = 720 / 8
    D(0, 0, s)

