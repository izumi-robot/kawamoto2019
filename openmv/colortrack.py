import sensor, image, time
# Color Tracking Thresholds
#   (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [
    (   20,   80,    40,    75,    40,    75)
]

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=300)
sensor.set_brightness(0)
sensor.set_saturation(0)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_exposure(False, 5000)
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

while(True):
    biggest_area = 0
    clock.tick()
    img = sensor.snapshot()
    blobs = img.find_blobs(
        thresholds,
        #pixels_threshold=5,
        #area_threshold=5
    )
    print("fps=%d" % clock.fps())
    if not blobs:
        continue
    for i, blob in enumerate(blobs):
        area = blob.area()
        if biggest_area < area:
            biggest_area, biggest_index = area, i
    biggest_blob = blobs[biggest_index]
    x_data, y_data = biggest_blob.cx(), biggest_blob.cy()
    img.draw_rectangle(biggest_blob.rect())
    img.draw_cross(x_data, y_data)
    print(" x=%d" % x_data)
    print(" y=%d" % y_data)
