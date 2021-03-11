import pyb, ustruct
import sensor, image, time

# Color Tracking Thresholds
#   (L Min, L Max, A Min, A Max, B Min, B Max)
ball_thresholds = [
    (   20,    80,    40,    75,    40,    75)
]

yellow_goal_ths = [
    ()
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

BALL, YELLOW_GOAL, BLUE_GOAL = range(3)

bus = pyb.I2C(2, mode=pyb.I2C.SLAVE, addr=0x12)
data, length_data = None, ustruct.pack("<H", 4) # 2byte * 2
default_value = 0xffff

def find_biggest_blob(blobs):
    biggest_area, biggest_index = 0, 0
    # https://docs.openmv.io/library/omv.image.html#class-blob-blob-object
    for i, area in enumerate(map(lambda blob: blob.area(), blobs)):
        if biggest_area < area:
            biggest_area, biggest_index = area, i
    return blobs[i]

def send(kind, x, y, i2c_bus=bus):
    # https://docs.python.org/ja/3/library/struct.html
    # https://docs.openmv.io/library/ustruct.html
    data = ustruct.pack("<B2H", kind, x, y)
    # https://docs.openmv.io/library/pyb.I2C.html
    try:
        bus.send(data, timeout=10000)
    except OSError as err:
        return False
    return True

def send_biggest_blob(kind, blobs):
    if not blobs:
        return False
    big_blob = find_biggest_blob(blobs)
    return send(kind, big_blob.cx(), big_blob.cy())

while True:
    clock.tick()
    # find object
    img = sensor.snapshot()
    # https://docs.openmv.io/library/omv.image.html#class-image-image-object
    blobs = img.find_blobs(
        thresholds,
        #pixels_threshold=5,
        #area_threshold=5
    )
    find_biggest_blob(blobs)
    # search the biggest object
    biggest_blob = blobs[biggest_index]
    x_data, y_data = biggest_blob.cx(), biggest_blob.cy()
    print((x_data, y_data))
    img.draw_cross(x_data, y_data)

    # send data
    send(x_data, y_data)
