PVector
    minimum = new PVector(-2, -2),
    maximum = new PVector(2, 2),
    range = new PVector(maximum.x - minimum.x, maximum.y - minimum.y),
    d = new PVector(0, 0),
    scale = new PVector(0, 0),
    center = new PVector(0, 0),
    canvas_size = new PVector(0, 0);


Complex julia_c = new Complex(-.4, .6);

color c;

float t = 0, len = 1;
int num = 50;


void setup() {
    fullScreen();
    canvas_size.x = width;
    canvas_size.y = height;
    center = PVector.div(canvas_size, 2);
    noStroke();
    colorMode(HSB, num);
}


void draw() {
    range = PVector.sub(maximum, minimum);
    scale.x = range.x / width;
    scale.y = range.y / height;

    background(255);
    float cx = center.x, cy = center.y;
    translate(cx, cy);
    // rotate(t);

    for (float x = -cx; x < cx; x+=len)
    for (float y = -cy; y < cy; y+=len) {
        float
            re = minimum.x + (x + cx) * scale.x,
            im = minimum.y + (y + cy) * scale.y;
        // int n = mandelbrot(new Complex(re, im), num);
        int n = julia(new Complex(re, im), julia_c, num);
        c = n == num ? color(0) : color(n, num, num);
        fill(c);
        rect(x, y, len, len);
    }

    t += .01;
    minimum.add(d);
}


int mandelbrot(Complex z) {
    return mandelbrot(z, num);
}

int mandelbrot(Complex z, int num) {
    Complex z1 = z;
    int count = 0;
    for (; z1.mag() < 2 && count < num; count++) {
        z1 = z1.mul(z1).add(z);
    }
    return count;
}


int julia(Complex z, Complex c) {
    return julia(z, c, num);
}

int julia(Complex z, Complex c, int num) {
    Complex z1 = new Complex(z.real, z.imag);
    int count = 0;
    for (; z1.mag() < 2 && count < num; count++) {
        z1 = z1.mul(z1).add(c);
    }
    return count;
}
