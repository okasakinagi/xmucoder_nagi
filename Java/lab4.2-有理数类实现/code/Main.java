public class Main {
    public static void main(String[] args) {
        // 创建两个有理数对象
        Rational rational1 = new Rational(1, 2);
        Rational rational2 = new Rational(3, 4);

        // 加法
        Rational sum = rational1.add(rational2);
        System.out.println("加法结果: " + rational1 + " + " + rational2 + " = " + sum);

        // 减法
        Rational difference = rational1.subtract(rational2);
        System.out.println("减法结果: " + rational1 + " - " + rational2 + " = " + difference);

        // 乘法
        Rational product = rational1.multiply(rational2);
        System.out.println("乘法结果: " + rational1 + " * " + rational2 + " = " + product);

        // 除法
        Rational quotient = rational1.divide(rational2);
        System.out.println("除法结果: " + rational1 + " / " + rational2 + " = " + quotient);
    }
}
