class HeadingEmu extends Emulator{
    private float _goal_heading, heading_vel;

    private void reset_heading() {
        this.heading_vel = 0;
        this._machine.heading(random(TAU));
    }

    public HeadingEmu(float goal_heading) {
        super(new Machine(width / 2, height / 2, 0, 0, min(width, height) / 3, 0));
        this._goal_heading = goal_heading;
    }

    public HeadingEmu() {
        this(PI / 2);
    }

    public void setup() {
        this.reset_heading();
    }

    public void draw() {
        float actual_heading = this._machine.heading();
        float heading = actual_heading - this._goal_heading;
        if (heading > PI) {
            heading -= TAU;
        }

        if (abs(heading) > PI / 10) {
            float dt = 1 / frameRate;
            float ideal_hv = -heading;
            this.heading_vel += ideal_hv - this.heading_vel;
            this._machine.heading(actual_heading + dt * this.heading_vel);
        }
        this._machine.draw();
    }

    public void keyPressed() {
        this.reset_heading();
    }

    public float goal_heading() {
        return this._goal_heading;
    }
}