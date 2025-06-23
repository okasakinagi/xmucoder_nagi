public class Rational extends Number implements Comparable<Rational> {
    private int numerator;
    private int denominator;

    Rational(int value) {
        this.numerator = value;
        this.denominator = 1;
    }

    Rational(int numerator, int denominator) {
        this.numerator = numerator;
        this.denominator = denominator;
        this.Simplify();
    }

    Rational(String value)// 规范字符串格式，如1/2,3/4等
    {
        if (value.length() == 3 && value.charAt(1) == '/') {
            this.numerator = value.charAt(0) - '0';
            this.denominator = value.charAt(2) - '0';
        } else {
            throw new IllegalArgumentException("不合法的有理数格式");
        }
        this.Simplify();
    }

    private void Simplify() {
        for (int i = Math.min(Math.abs(this.numerator), Math.abs(this.denominator)); i > 1; i--) {
            if (this.numerator % i == 0 && this.denominator % i == 0) {
                this.numerator /= i;
                this.denominator /= i;
                break;
            }
        }
        if (denominator < 0) {
            this.numerator = -this.numerator;
            this.denominator = -this.denominator;
        }
    }

    public int getNumerator() {
        return numerator;
    }

    public int getDenominator() {
        return denominator;
    }

    public String toString() {
        return numerator + "/" + denominator;
    }

    public Rational add(Rational other) {
        int newNumerator = this.numerator * other.denominator + this.denominator * other.numerator;
        int newDenominator = this.denominator * other.denominator;
        Rational result = new Rational(newNumerator, newDenominator);
        result.Simplify();
        return result;
    }

    public Rational subtract(Rational other) {
        int newNumerator = this.numerator * other.denominator - this.denominator * other.numerator;
        int newDenominator = this.denominator * other.denominator;
        Rational result = new Rational(newNumerator, newDenominator);
        result.Simplify();
        return result;
    }

    public Rational multiply(Rational other) {
        int newNumerator = this.numerator * other.numerator;
        int newDenominator = this.denominator * other.denominator;
        Rational result = new Rational(newNumerator, newDenominator);
        result.Simplify();
        return result;
    }

    public Rational divide(Rational other) {
        if (other.numerator == 0)
            throw new IllegalArgumentException("除数不能为0");
        int newNumerator = this.numerator * other.denominator;
        int newDenominator = this.denominator * other.numerator;
        Rational result = new Rational(newNumerator, newDenominator);
        result.Simplify();
        return result;
    }

    public Rational absolute() {
        return new Rational(Math.abs(this.numerator), this.denominator);
    }

    boolean is_positive() {
        return this.numerator > 0;
    }

    boolean is_negative() {
        return this.numerator < 0;
    }

    boolean equals(Rational other) {
        return this.numerator == other.numerator && this.denominator == other.denominator;
    }

    public int compareTo(Rational other) {
        return (this.numerator * other.denominator - this.denominator * other.numerator);
    }

    @Override
    public int intValue() {
        return (int) ((double) this.numerator / this.denominator);
    }

    @Override
    public long longValue() {
        return (long) ((double) this.numerator / this.denominator);
    }

    @Override
    public float floatValue() {
        return (float) ((double) this.numerator / this.denominator);
    }

    @Override
    public double doubleValue() {
        return (double) this.numerator / this.denominator;
    }
}
