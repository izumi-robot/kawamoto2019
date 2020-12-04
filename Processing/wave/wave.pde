float count = 0;

float wav1(float x) {
    float t = (x - count) / 50, y = 0;
    if (t <= 0) {
        y = sin(t);
    }
    return y;
}

float wav2(float x) {
    float t = (width - x - count) / 50, y = 0;
    if (t <= 0) {
        y = sin(t + PI);
    }
    return y;
}

void setup() {
    fullScreen();
    strokeWeight(2);
}

void draw() {
    background(255);
    translate(0, height / 2);
    for (float x = 0; x < width; x += 2) {
        float y = (wav1(x) + wav2(x)) * 100;
        point(x, y);
    }
    count += 2;
}