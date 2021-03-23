class Ball {
    public Vector2D pos, vel;
    private float _radius;

    public Ball(float pos_x, float pos_y, float vel_x, float vel_y, float radius) {
        this.pos = new Vector2D(pos_x, pos_y);
        this.vel = new Vector2D(vel_x, vel_y);
        this._radius = radius;
    }

    public Ball(Vector2D pos, Vector2D vel, float radius) {
        this(pos.x, pos.y, vel.x, vel.y, radius);
    }

    public Ball(Vector2D pos, Vector2D vel) {
        this(pos, vel, 10);
    }

    public Ball() {
        this(0, 0, 0, 0, 10);
    }

    public float radius() {
        return this._radius;
    }

    public float radius(float radius) throws IllegalArgumentException {
        if (radius <= 0) {
            throw new IllegalArgumentException();
        }
        this._radius = radius;
        return radius;
    }

    public Ball draw() {
        push();
        fill(255, 0, 0);
        ellipse(this.pos.x, this.pos.y, this._radius * 2, this._radius * 2);
        pop();
        return this;
    }
}