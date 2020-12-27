Ball ball = new Ball();
Machine machine = new Machine();
Vector2D diff = new Vector2D(), dest = new Vector2D();
// alpha, beta
float border1 = PI / 7, border2 = PI / 4;


void reset() {
    loop();
    float br = ball.rad(), mr = machine.rad();
    ball.pos.x = random(br, width - br);
    ball.pos.y = random(br, height - br);
    machine.pos.x = random(mr, width - mr);
    machine.pos.y = random(mr, height - mr);
}


void setup() {
    fullScreen();
    //println(width);
    //println(height);
    frameRate(5);
    ball.rad(35);
    machine.rad(105);
    reset();
    textSize(30);
    fill(0);
}


void draw() {
    diff.x = ball.pos.x; diff.y = ball.pos.y;
    diff.isub(machine.pos);
    //diff.set(-diff.y, diff.x);
    if (diff.mag() < ball.rad()) {
        noLoop();
        return;
    }

    // float ang = diff.angle();
    // ang -= PI / 2;
    // if (ang < -PI) {
    //     ang += 2 * PI;
    // }
    float ang = atan2(diff.x, diff.y);
    if (-border2 < ang && ang < border1) {
        dest.x = diff.x * 2;
        dest.y = diff.y;
    } else if (
        (-PI + border2 < ang && ang <= -border1)
        || (border1 <= ang && ang < PI - border2)
    ) {
        dest.x = diff.x;
        dest.y = diff.y - (ball.rad() + 2 * machine.rad()) * ((abs(ang) - border1) / PI + 1);
    } else if (-PI <= ang && ang <= -PI + border2) {
        dest.x = diff.x + machine.rad();
        dest.y = diff.y + (2 * ball.rad() + machine.rad());
    } else { // PI - border2 <= ang && ang <= PI
        dest.x = diff.x - machine.rad();
        dest.y = diff.y + (2 * ball.rad() + machine.rad());
    }

    dest.mag(10);
    machine.vel.set(dest);
    machine.pos.iadd(machine.vel);

    background(255);
    ball.draw();
    machine.draw();
    //line(ball.pos.x, ball.pos.y, machine.pos.x, machine.pos.y);
    line(ball.pos, machine.pos);

    text(String.valueOf(int(ang * 180 / PI)), 10, 50);
}


void keyPressed() {
    reset();
}


void mousePressed() {
    machine.pos.set(mouseX, mouseY);
}
