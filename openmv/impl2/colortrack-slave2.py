import pyb, ustruct
import sensor, image, time

# Color Tracking Thresholds
#   (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [
    (   40,    60,    40,    80,    30,    60), # orange ball
    (   20,    75,     0,    30,    25,    50), # yellow goal
    (   10,    25,   -15,    15,   -40,   -10)  # blue goal
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


def get_blob_pos(blob):
    if not blob:
        return (default_value, default_value)
    return (blob.cx(), blob.cy())


def blob_code_filter(blobs, code):
    return filter(lambda b: b.code() == code, blobs)


def send_nums(nums, i2c_bus=bus):
    l = len(nums)
    # https://docs.python.org/ja/3/library/struct.html
    # https://docs.openmv.io/library/ustruct.html
    data = ustruct.pack("<%dH" % l, *nums)
    try:
        # https://docs.openmv.io/library/pyb.I2C.html
        i2c_bus.send(data, timeout=10000)
    except OSError as err:
        return False
    return True


while True:
    clock.tick()
    img = sensor.snapshot()
    # https://docs.openmv.io/library/omv.image.html#class-image-image-object
    blobs = img.find_blobs(
        thresholds,
        #x_stride=5,
        #y_stride=5,
        #pixels_threshold=10,
    )

    ball = find_biggest_blob(blob_code_filter(blobs, 1))
    y_goal = find_biggest_blob(blob_code_filter(blobs, 2))
    b_goal = find_biggest_blob(blob_code_filter(blobs, 4))

    ba_x, ba_y = get_blob_pos(ball)
    yg_x, yg_y = get_blob_pos(y_goal)
    bg_x, bg_y = get_blob_pos(b_goal)

    img.draw_cross(ba_x, ba_y)
    img.draw_cross(yg_x, yg_y)
    img.draw_cross(bg_x, bg_y)

    send_nums((ba_x, ba_y, yg_x, yg_y, bg_x, bg_y))
    print(clock.fps())

