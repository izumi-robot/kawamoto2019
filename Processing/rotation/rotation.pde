float t = 0, d = 30;
final float W = 360, H = 360;

void setup() {
    //size(720, 720);
    fullScreen();
    fill(-1);
    //frameRate(2);
}

void draw() {
    clear();
    for (float c = -W; c < W; c += d)
    for (float r = -H; r < H; r += d) {
        PVector p = new PVector(c * 2 + r * 2, c / 2 + r / 2)
        circle(x, y, 10);
    }
    t += .1;
}
