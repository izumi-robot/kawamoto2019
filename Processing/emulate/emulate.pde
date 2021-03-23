Emulator emulator;

void setup() {
    fullScreen();
    emulator = new HeadingEmu();
    emulator.setup();
}

void draw() {
    background(255);
    emulator.draw();
}

void keyPressed() {
    emulator.keyPressed();
}