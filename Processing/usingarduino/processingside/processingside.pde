import processing.serial.*;


Serial port;
float currentdir;


void setup() {
    size(360, 360);
    port = new Serial(this, Serial.list()[0], 9600);
    currentdir = 0;
}


void draw() {
    if (port.available() > 0) {
        String inBuffer = port.readString();
        currentdir = str2float(inBuffer, currentdir);
    }

    float radius = min(width, height) / 3;

    background(255);
    translate(width / 2, height / 2);
    ellipse(0, 0, radius, radius);
    float x = sin(-currentdir), y = cos(-currentdir + PI);
    line(0, 0, radius * x, radius * y);
}


float str2float(String str, float def_value) {
    String lines[] = str.split("\n", 0);
    for (int i = lines.length - 1; i >= 0; i--) {
        if (lines[i].matches("-?[0-9]+\\.?[0-9]*")) {
            return Float.parseFloat(lines[i]);
        }
    }
    return def_value;
}