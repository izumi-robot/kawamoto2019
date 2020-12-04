final int r = 25;
float x, y, vx, vy;


void setup() {
    size(500, 500);
    x = 350;
    y = 100;
    vx = 10;
    vy = 10;
}

/*
x = random(r, width - r);
y = random(r, height - r);
vx = random(5, 10);
vy = random(5, 10);
*/

void draw() {
    background(255);
    fill(0, 255, 0);
    ellipse(x, y, r*2, r*2);
    x += vx;
    y += vy;
 
    if(!(0 <= x - r && x + r <= width)) {
        vx *= -1;
    }
    if(!(0 <= y - r && y + r <= height)) {
        vy *= -1;
    }
}
