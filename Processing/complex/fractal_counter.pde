interface FractalCounter {
    int count(Complex, int);
}

class MandelCounter implements FractalCounter {
    int count(Complex first_c, int max_count) {
        Complex now_c = new Complex(first_c);
        for (int i = 0; i < max_count; i++) {
            now_c.imul(now_c).iadd(first_c);
            if (now_c.mag() >= 2) { return i; }
        }
        return max_count;
    }
}

class JuliaCounter implements FractalCounter {
    private Complex _progress;
    JuliaCounter(Complex progress) {
        this._progress = new Complex(progress);
    }

    int count(Complex first_c, int max_count) {
        Complex now_c = new Complex(first_c);
        for (int i = 0; i < max_count; i++) {
            now_c.imul(now_c).iadd(_progress);
            if (now_c.mag() >= 2) { return i; }
        }
        return max_count;
    }
}