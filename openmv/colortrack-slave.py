import pyb, ustruct
import sensor, image, time

thresholds = [(20, 80, 40, 75, 40, 75)]

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
data, length_data = None, ustruct.pack("<h", 2 * 2) # 2byte * 2

x_data, y_data = 0, 0
biggest_area, biggest_index, biggest_blob = 0, 0, None
area = 0

while True:
    clock.tick()
    # find object
    img = sensor.snapshot()
    blobs = img.find_blobs(thresholds)
    if not blobs:
        # there is no object
        continue
    # search the biggest object
    biggest_area = 0
    for i, blob in enumerate(blobs):
        area = blob.area()
        if area > biggest_area:
            biggest_area, biggest_index = area, i
    biggest_blob = blobs[biggest_index]
    x_data, y_data = biggest_blob.cx(), biggest_blob.cy()
    print((x_data, y_data))
    img.draw_cross(x_data, y_data)

    # send data
    print("send data!")
    data = ustruct.pack("<2h", x_data, y_data)
    try:
        bus.send(length_data, timeout=10000)
        bus.send(data,        timeout=10000)
    except OSError as err:
        pass
