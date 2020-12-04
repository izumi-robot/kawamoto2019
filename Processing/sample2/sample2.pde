float x, y, r;


void setup() {
    size(500, 500);
    x = 250;
    y = 250;
    r = 25;
}

void draw() {
    background(255);
    fill(200, 0, 200);
    ellipse(x, y, r * 2, r * 2);
    x += 10;
    y += 10;
    x %= width;
    y %= height;
}

/*
10 + 5 -> 15
10 - 5 -> 5
10 * 5 -> 50
10 / 5 -> 2.0
10 ^ 5 -> 100000
10 % 5 -> 0
sqrt(2) -> 1.41421356...
PI -> 3.14...
*/
