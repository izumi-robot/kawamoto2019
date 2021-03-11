import pyb, ustruct
import sensor, image, time

# Color Tracking Thresholds
#   (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [
    (   20,    80,    40,    75,    40,    75)
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

bus = pyb.I2C(2, mode=pyb.I2C.SLAVE, addr=0x12)
data, length_data = None, ustruct.pack("<H", 4) # 2byte * 2
default_value = 0xffff

def send(a, b, i2c_bus=bus):
    # https://docs.python.org/ja/3/library/struct.html
    # https://docs.openmv.io/library/ustruct.html
    data = ustruct.pack("<2H", a, b)
    # https://docs.openmv.io/library/pyb.I2C.html
    try:
        bus.send(length_data, timeout=10000)
        bus.send(data,        timeout=10000)
    except OSError as err:
        return False
    return True


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
    if not blobs:
        # there is no object -- send template data
        send(default_value, default_value)
        continue
    # search the biggest object
    biggest_area = 0
    for i, blob in enumerate(blobs):
        # https://docs.openmv.io/library/omv.image.html#class-blob-blob-object
        area = blob.area()
        if area > biggest_area:
            biggest_area, biggest_index = area, i
    biggest_blob = blobs[biggest_index]
    x_data, y_data = biggest_blob.cx(), biggest_blob.cy()
    print((x_data, y_data))
    img.draw_cross(x_data, y_data)

    # send data
    send(x_data, y_data)
