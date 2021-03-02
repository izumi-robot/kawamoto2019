void leftDragon(float sz, int level) {
    if (level == 0) {
        line(0, 0, sz, 0);
        translate(sz, 0);
    } else {
        leftDragon(sz, level - 1);
        rotate(-PI / 2);
        rightDragon(sz, level - 1);
    }
}

void rightDragon(float sz, int level) {
    if (level == 0) {
        line(0, 0, sz, 0);
        translate(sz, 0);
    } else {
        leftDragon(sz, level - 1);
        rotate(PI / 2);
        fill(map(level, 0, 10, 0, 255), 255, 255);
        rightDragon(sz, level - 1);
    }
}

void setup() {
    fullScreen();
    //size(800, 800);
    strokeWeight(2);
    colorMode(HSB);
}

void draw() {
    background(255);
    translate(1096, 1100);
    leftDragon(25.5, 11);
}