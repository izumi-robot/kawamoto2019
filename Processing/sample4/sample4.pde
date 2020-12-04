int l = 25,
    max_ = (2 << l) - 1;

float xs[] = new float[l],
      ys[] = new float[l],
      vxs[] = new float[l],
      vys[] = new float[l],
      r = 25;

color c = color(int(random(256)), int(random(256)), int(random(256)));


void setup() {
    //size(500, 500);
    fullScreen();
    for(int i=0; i<l; i++) {
        float order[] = {
            random(r, width - r),
            random(r, height - r),
            random(-10, 10),
            random(-10, 10),
        };
        xs[i] = order[0];
        ys[i] = order[1];
        vxs[i] = order[2];
        vys[i] = order[3];
    }
}

void draw() {
    background(255);
    fill(c);
    int m = round(random(max_));
    for(int i=0; i<l; i++) {
        if((m & (1 << i)) != 0) {
            ellipse(xs[i], ys[i], 2*r, 2*r);
        }
        xs[i] += vxs[i];
        ys[i] += vys[i];

        if(!(0 <= xs[i] - r && xs[i] + r <= width)) {
            vxs[i] *= -1;
        }
        if(!(0 <= ys[i] - r && ys[i] + r <= height)) {
            vys[i] *= -1;
        }
    }
    //background(255);
}

/*
    
    if(!(0 <= y - r && y + r <= height)) {
        vy *= -1;
    }
*/

float[][] coords = new float[10][2],
  vels = new float[10][2];

void setup_() {
    size(500, 500);
    for(int i=0; i<10; i++) {
        float[] order = {
            random(r, width - r),
            random(r, height - r),
            random(-10, 10),
            random(-10, 10),
        };
        coords[i][0] = order[0];
        coords[i][1] = order[1];
        vels[i][0] = order[2];
        vels[i][1] = order[3];
    }
}

void draw_() {
    background(255);
    fill(0, 0, 255);
    for(int i=0; i<10; i++) {
        ellipse(coords[i][0], coords[i][1], 2*r, 2*r);
        coords[i][0] += vels[i][0];
        coords[i][1] += vels[i][1];
        if(!(0 <= coords[i][0] - r && coords[i][0] + r <= width)) {
            vels[i][0] *= -1;
        }
        if(!(0 <= coords[i][1] - r && coords[i][1] + r <= height)) {
            vels[i][1] *= -1;
        }
    }
}
