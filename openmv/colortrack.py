import sensor, image, time
# Color Tracking Thresholds
#   (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [
    (   20,   80,    20,    80,    40,    75)
]
"""
rgb             -> lab
(255, 160,  83) -> ( 74,  29,  54)
(255,  18,   0) -> ( 54,  79,  67)
(255, 122,   3) -> ( 66,  46,  73)
(185,  38,  26) -> ( 41,  57,  44)
"""
# You may pass up to 16 thresholds above. However, it's not really possible to segment any
# scene with 16 thresholds before color thresholds start to overlap heavily.

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=300)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_exposure(False, 5000)
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. Don't set "merge=True" becuase that will merge blobs which we don't want here.

x_data, y_data = 0, 0
biggest_area, biggest_index, biggest_blob = 0, 0, None
area = 0

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
