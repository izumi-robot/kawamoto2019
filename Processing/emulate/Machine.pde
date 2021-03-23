class Machine {
    public Vector2D pos, vel;
    private float _radius, _heading;

    public Machine(float pos_x, float pos_y, float vel_x, float vel_y, float radius, float heading) {
        this.pos = new Vector2D(pos_x, pos_y);
        this.vel = new Vector2D(vel_x, vel_y);
        this._radius = radius;
        this._heading = heading;
    }

    public Machine(Vector2D pos, Vector2D vel, float radius, float heading) {
        this(pos.x, pos.y, vel.x, vel.y, radius, heading);
    }

    public Machine(Vector2D pos, Vector2D vel) {
        this(pos, vel, 30, 0);
    }

    public Machine() {
        this(0, 0, 0, 0, 30, 0);
    }

    public float radius() {
        return this._radius;
    }

    public float radius(float n_radius) throws IllegalArgumentException {
        if (n_radius <= 0) {
            throw new IllegalArgumentException();
        }
        this._radius = n_radius;
        return this._radius;
    }

    public float heading() {
        return this._heading;
    }

    public float heading(float n_heading) {
        this._heading = n_heading;
        return this._heading;
    }

    public Machine draw() {
        push();
        translate(this.pos.x, this.pos.y);
        ellipse(0, 0, this._radius * 2, this._radius * 2);
        Vector2D pv = this.vel.mul(this._radius / 4);
        line(0, 0, pv.x, pv.y);
        float hx = this._radius * cos(this._heading), hy = this._radius * sin(this._heading);
        line(-hx / 5, -hy / 5, hx, hy);
        pop();
        return this;
    }
}