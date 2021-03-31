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
    float dir = ang * 3 / 2;
    dest.x = 10 * cos(dir);
    dest.y = 10 * sin(dir);
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
