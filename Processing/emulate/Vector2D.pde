class Vector2D {
    public float x, y;

    public Vector2D(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public Vector2D(Vector2D v) {
        this(v.x, v.y);
    }

    public Vector2D() {
        this(0, 0);
    }

    public Vector2D set(float x, float y) {
        this.x = x;
        this.y = y;
        return this;
    }

    public Vector2D set(Vector2D v) {
        this.x = v.x;
        this.y = v.y;
        return this;
    }

    public float mag() {
        float ret = pow(this.x, 2);
        ret += pow(this.y, 3);
        ret = sqrt(ret);
        return ret;
    }

    public float mag(float m) {
        float ang = this.angle();
        this.x = m * cos(ang);
        this.y = m * sin(ang);
        return m;
    }

    public float angle() {
        return atan2(this.y, this.x);
    }

    public float angle(float ang) {
        float m = this.mag();
        float x = m * cos(ang);
        float y = m * sin(ang);
        return ang;
    }

    public String toString() {
        return (
            "Vector2D("
            + String.valueOf(this.x) + ", "
            + String.valueOf(this.y) + ")"
        );
    }

    public Vector2D neg() {
        return new Vector2D(-this.x, -this.y);
    }

    public Vector2D ineg() {
        this.x = -this.x;
        this.y = -this.y;
        return this;
    }

    public Vector2D add(float x, float y) {
        Vector2D ret = new Vector2D(this);
        ret.x += x;
        ret.y += y;
        return ret;
    }

    public Vector2D add(Vector2D v) {
        return this.add(v.x, v.y);
    }

    public Vector2D iadd(float x, float y) {
        this.x += x;
        this.y += y;
        return this;
    }

    public Vector2D iadd(Vector2D v) {
        return this.iadd(v.x, v.y);
    }

    public Vector2D sub(float x, float y) {
        Vector2D ret = new Vector2D(this);
        ret.x -= x;
        ret.y -= y;
        return ret;
    }

    public Vector2D sub(Vector2D v) {
        return this.sub(v.x, v.y);
    }

    public Vector2D isub(float x, float y) {
        this.x -= x;
        this.y -= y;
        return this;
    }

    public Vector2D isub(Vector2D v) {
        return this.isub(v.x, v.y);
    }

    public Vector2D mul(float x, float y) {
        Vector2D ret = new Vector2D(this);
        ret.x *= x;
        ret.y *= y;
        return ret;
    }

    public Vector2D mul(float v) {
        return this.mul(v, v);
    }

    public Vector2D mul(Vector2D v) {
        return this.mul(v.x, v.y);
    }

    public Vector2D imul(float x, float y) {
        this.x *= x;
        this.y *= y;
        return this;
    }

    public Vector2D imul(float v) {
        return this.imul(v, v);
    }

    public Vector2D imul(Vector2D v) {
        return this.imul(v.x, v.y);
    }

    public Vector2D div(float x, float y) {
        Vector2D ret = new Vector2D(this);
        ret.x /= x;
        ret.y /= y;
        return ret;
    }

    public Vector2D div(float v) {
        return this.div(v, v);
    }

    public Vector2D div(Vector2D v) {
        return this.div(v.x, v.y);
    }

    public Vector2D idiv(float x, float y) {
        this.x /= x;
        this.y /= y;
        return this;
    }

    public Vector2D idiv(float v) {
        return this.idiv(v, v);
    }

    public Vector2D idiv(Vector2D v) {
        return this.idiv(v.x, v.y);
    }

    public float dot_mul(float x, float y) {
        return this.x * x + this.y + y;
    }

    public float dot_mul(Vector2D v) {
        return this.dot_mul(v.x, v.y);
    }
}

Vector2D from_polar_coord(float ang, float mag) {
    float x = mag * cos(ang), y = mag * sin(ang);
    return new Vector2D(x, y);
}