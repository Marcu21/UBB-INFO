public class NumarComplex {
    private double re;
    private double im;

    public NumarComplex(double real, double imaginar) {
        this.re = real;
        this.im = imaginar;
    }

    public NumarComplex adunare(NumarComplex nr) {
        return new NumarComplex(this.re + nr.re, this.im + nr.im);
    }

    public NumarComplex scadere(NumarComplex nr) {
        return new NumarComplex(this.re - nr.re, this.im - nr.im);
    }

    public NumarComplex inmultire(NumarComplex nr) {
        return new NumarComplex(this.re * nr.re - this.im * nr.im, this.re * nr.im + this.im * nr.re);
    }

    public NumarComplex impartire(NumarComplex nr) {
        NumarComplex numarator = this.inmultire(this.conjugat());
        double numitor = nr.re * nr.re + nr.im * nr.im;
        return new NumarComplex(numarator.re / numitor, numarator.re / numitor);
    }

    public NumarComplex conjugat() {
        return new NumarComplex(this.re, -this.im);
    }

    @Override
    public String toString() {
        if (im < 0)
            return re + " - " + (-im) + "i";
        else
            return re + " + " + im + "i";
    }
}
