import pyb, ustruct
import sensor, image, time

thresholds = [
    (   20,   80,    20,    80,    40,    75)
]

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=300)
sensor.set_auto_gain(False)
sensor.set_auto_exposure(False, 5000)
sensor.set_auto_whitebal(False)
clock = time.clock()

bus = pyb.I2C(2, mode=pyb.I2C.SLAVE, addr=0x12)
bus.deinit() # Fully reset I2C device...
bus = pyb.I2C(2, mode=pyb.I2C.SLAVE, addr=0x12)

x_data, y_data = 0, 0
biggest_area, biggest_index, biggest_blob = 0, 0, None
area = 0
data = None

while True:
    # find object
    biggest_area = 0
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs(thresholds)
    if not blobs:
        continue
    for i, blob in enumerate(blobs):
        area = blob.area()
        if biggest_area < area:
            biggest_area, biggest_index = area, i
    biggest_blob = blobs[biggest_index]
    x_data, y_data = biggest_blob.cx(), biggest_blob.cy()
    
    # send data
    data = ustruct.pack(">2H", 97, )
