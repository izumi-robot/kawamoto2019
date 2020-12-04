
void setup() {
    //fullScreen();
    size(512, 512);
    background(255);
    fill(0);
    frameRate(5);
}

void draw() {
    //background(255);
    ellipse(getX(), getY(), 25, 25);
}

float getX() {
    return random(0, width);
}

float getY() {
    return random(0, height);
}
