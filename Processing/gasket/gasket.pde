void gasket(int level, float cell_size) {
    if (level <= 0) return;
    rect(0, 0, cell_size, cell_size);
    float nextLen = cell_size * pow(2, level - 2);
    gasket(level - 1, cell_size);
    loadPixels();
    PImage img = get(0, 0, (int)nextLen, (int)nextLen);
    image(img, nextLen, 0, nextLen, nextLen);
    image(img, 0, nextLen, nextLen, nextLen);
}

void setup() {
    size(720, 720);
}

void draw() {
    clear();
    gasket(16, width / 16);
}