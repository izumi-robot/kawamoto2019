class Ball {
    public Vector2D pos, vel;
    private float _rad;

    Ball(float pos_x, float pos_y, float vel_x, float vel_y, float rad) {
        this.pos = new Vector2D(pos_x, pos_y);
        this.vel = new Vector2D(vel_x, vel_y);
        this._rad = rad;
    }

    Ball(Vector2D pos, Vector2D vel, float rad) {
        this(pos.x, pos.y, vel.x, vel.y, rad);
    }

    Ball(Vector2D pos, Vector2D vel) {
        this(pos, vel, 10);
    }

    Ball() {
        this(0, 0, 0, 0, 10);
    }

    float rad() {
        return this._rad;
    }

    float rad(float rad) throws IllegalArgumentException {
        if (rad <= 0) {
            throw new IllegalArgumentException();
        }
        this._rad = rad;
        return rad;
    }

    Ball draw() {
        push();
        fill(255, 0, 0);
        ellipse(this.pos.x, this.pos.y, this._rad * 2, this._rad * 2);
        pop();
        return this;
    }
}