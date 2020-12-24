class Complex {
    float real, imag;

    Complex(float re, float im) {
        this.real = re;
        this.imag = im;
    }
    Complex(float re) { this(re, 0); }
    Complex() { this(0, 0); }

    float mag() {
        return this.real * this.real + this.imag * this.imag;
    }

    float angle() {
        return atan2(this.imag, this.real);
    }

    Complex add(Complex other) {
        float re = this.real + other.real;
        float im = this.imag + other.imag;
        return new Complex(re, im);
    }

    Complex sub(Complex other) {
        float re = this.real - other.real;
        float im = this.imag - other.imag;
        return new Complex(re, im);
    }

    Complex mul(Complex other) {
        float re = this.real * other.real - this.imag * other.imag;
        float im = this.real * other.imag + this.imag * other.real;
        return new Complex(re, im);
    }

    Complex div(Complex other) {
        float re = this.real * other.real + this.imag * other.imag;
        float im = this.imag * other.real - this.real * other.imag;
        float mg = other.mag();
        re /= mg; im /= mg;
        return new Complex(re, im);
    }

    void set(float re, float im) {
        this.real = re;
        this.imag = im;
    }

    void set(Complex other) {
        this.real = other.real;
        this.imag = other.imag;
    }

    void iadd(Complex other) {
        this.set(this.add(other));
    }

    void isub(Complex other) {
        this.set(this.sub(other));
    }

    void imul(Complex other) {
        this.set(this.mul(other));
    }

    void idiv(Complex other) {
        this.set(this.div(other));
    }
}