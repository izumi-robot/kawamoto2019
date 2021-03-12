import pyb, ustruct
import sensor, image, time

# Color Tracking Thresholds
#   (L Min, L Max, A Min, A Max, B Min, B Max)
ball_thresholds = [
    (   40,    60,    50,    75,    40,    65)
]

#   (L Min, L Max, A Min, A Max, B Min, B Max)
yellow_goal_ths = [
    (   15,    40,     0,    20,    60,    80)
]

blue_goal_ths = [
    (    0,    40,   -10,    10,   -25,   -10)
]

"""
orange
#fe543f -> (60, 63, 48)
#b61c11 -> (39, 58, 47)
#ff4829 -> (58, 67, 57)

blue
#567cac -> (51, 0, -30)
#365794 -> (37, 8, -37)
#0e376b -> (23, 7, -34)

yellow 1
#f8ab24 -> (76, 18, 73)
#ffcc3e -> (84,  5, 73)
#eca120 -> (72, 18, 70)

yellow 2
#e4ab2f -> (73, 10, 67)
#fecf31 -> (85, 3, 77)
#e5aa43 -> (73, 12, 59)
"""

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

BALL, YELLOW_GOAL, BLUE_GOAL = 0, 1, 2
default_value = 0xffff

bus = pyb.I2C(2, mode=pyb.I2C.SLAVE, addr=0x12)


def find_biggest_blob(blobs):
    if not blobs:
        return None
    biggest_area, biggest_index = 0, 0
    # https://docs.openmv.io/library/omv.image.html#class-blob-blob-object
    for i, area in enumerate(map(lambda blob: blob.area(), blobs)):
        if biggest_area < area:
            biggest_area, biggest_index = area, i
    return blobs[i]


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
        pass
    finally:
        return (x, y)


while True:
    clock.tick()
    # find object
    img = sensor.snapshot()
    # https://docs.openmv.io/library/omv.image.html#class-image-image-object
    ball_blob = find_biggest_blob(img.find_blobs(
        ball_thresholds,
        #pixels_threshold=5,
        #area_threshold=5
    ))
    yellow_blob = find_biggest_blob(img.find_blobs(
        yellow_goal_ths,
        pixels_threshold=20,
        area_threshold=20
    ))
    blue_blob = find_biggest_blob(img.find_blobs(
        blue_goal_ths,
        pixels_threshold=20,
        area_threshold=20
    ))
    img.draw_cross(*send_blob(ball_blob))
    img.draw_cross(*send_blob(yellow_blob))
    img.draw_cross(*send_blob(blue_blob))
    print(clock.fps())
