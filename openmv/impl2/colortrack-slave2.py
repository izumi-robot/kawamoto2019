import pyb, ustruct
import sensor, image, time

# Color Tracking Thresholds
#   (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [
    (   40,    60,    40,    80,    30,    60), # orange ball
    (   20,    75,     0,    30,    25,    50), # yellow goal
    (    0,    40,   -15,    15,   -40,     5)  # blue goal
]

# https://docs.openmv.io/library/omv.sensor.html
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=300)
sensor.set_brightness(0)
sensor.set_saturation(0)
sensor.set_auto_gain(False)
sensor.set_auto_exposure(False, 5000)
sensor.set_auto_whitebal(False)
clock = time.clock()

default_value = 0xffff

bus = pyb.I2C(2, mode=pyb.I2C.SLAVE, addr=0x12)


def find_biggest_blob(blobs):
    # https://docs.openmv.io/library/omv.image.html#class-blob-blob-object
    b_blob, b_area = None, 0
    for blob in blobs:
        area = blob.area()
        if b_area < area:
            b_blob, b_area = blob, area
    return b_blob


def blob_code_filter(blobs, code):
    return filter(lambda b: b.code() == code, blobs)

def send_blob(blob, i2c_bus=bus):
    x, y = default_value, default_value
    if blob:
        x, y = blob.cx(), blob.cy()
    # https://docs.python.org/ja/3/library/struct.html
    # https://docs.openmv.io/library/ustruct.html
    data = ustruct.pack("<2H", x, y)
    # https://docs.openmv.io/library/pyb.I2C.html
    try:
        bus.send(data, timeout=10000)
    except OSError as err:
        return False
    return True


def get_blob_pos(blob):
    if not blob:
        return (-1, -1)
    return (blob.cx(), blob.cy())

while True:
    clock.tick()
    img = sensor.snapshot()
    # https://docs.openmv.io/library/omv.image.html#class-image-image-object
    blobs = img.find_blobs(
        thresholds,
        #x_stride=5,
        #y_stride=5,
        pixels_threshold=10,
    )

    ball = find_biggest_blob(blob_code_filter(blobs, 1))
    y_goal = find_biggest_blob(blob_code_filter(blobs, 2))
    b_goal = find_biggest_blob(blob_code_filter(blobs, 4))

    img.draw_cross(*get_blob_pos(ball))
    img.draw_cross(*get_blob_pos(y_goal))
    img.draw_cross(*get_blob_pos(b_goal))

    send_blob(ball)
    send_blob(y_goal)
    send_blob(b_goal)
    print(clock.fps())
