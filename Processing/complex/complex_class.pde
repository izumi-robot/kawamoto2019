class Complex {
    float real, imag;

    Complex(float re, float im) {
        this.real = re;
        this.imag = im;
    }
    Complex(float re) { this(re, 0); }
    Complex() { this(0, 0); }
    Complex(Complex other) { this(other.real, other.imag); }

    float mag() {
        return this.real * this.real + this.imag * this.imag;
    }

    float arg() {
        return atan2(this.imag, this.real);
    }

    Complex pos() {
        return new Complex(this);
    }

    Complex neg() {
        return new Complex(-this.real, -this.imag);
    }

    Complex set(float re, float im) {
        this.real = re;
        this.imag = im;
        return this;
    }

    Complex set(Complex other) {
        this.real = other.real;
        this.imag = other.imag;
        return this;
    }

    Complex iadd(Complex other) {
        this.real += other.real;
        this.imag += other.imag;
        return this;
    }

    Complex isub(Complex other) {
        this.real -= other.real;
        this.imag -= other.imag;
        return this;
    }

    Complex imul(Complex other) {
        this.real = this.real * other.real - this.imag * other.imag;
        this.imag = this.real * other.imag + this.imag * other.real;
        return this;
    }

    Complex idiv(Complex other) {
        float mag = other.mag();
        this.real = (this.real * other.real + this.imag * other.imag) / mag;
        this.imag = (this.imag * other.real - this.real * other.imag) / mag;
        return this;
    }

    Complex add(Complex other) {
        return (new Complex(this)).iadd(other);
    }

    Complex sub(Complex other) {
        return (new Complex(this)).isub(other);
    }

    Complex mul(Complex other) {
        return (new Complex(this)).imul(other);
    }

    Complex div(Complex other) {
        return (new Complex(this)).idiv(other);
    }
}