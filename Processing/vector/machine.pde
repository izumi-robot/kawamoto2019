class Machine {
    public Vector2D pos, vel;
    private float _rad;

    Machine(float pos_x, float pos_y, float vel_x, float vel_y, float rad) {
        this.pos = new Vector2D(pos_x, pos_y);
        this.vel = new Vector2D(vel_x, vel_y);
        this._rad = rad;
    }

    Machine(Vector2D pos, Vector2D vel, float rad) {
        this(pos.x, pos.y, vel.x, vel.y, rad);
    }

    Machine(Vector2D pos, Vector2D vel) {
        this(pos, vel, 30);
    }

    Machine() {
        this(0, 0, 0, 0, 30);
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

    Machine draw() {
        push();
        fill(255);
        ellipse(this.pos.x, this.pos.y, this._rad * 2, this._rad * 2);
        Vector2D pv = this.vel.mul(this._rad / 4).add(this.pos);
        line(this.pos.x, this.pos.y, pv.x, pv.y);
        pop();
        return this;
    }
}