public class Main {
    public static <T> boolean isEqualTo(T a, T b) {
        return a != null && a.equals(b);
    }

    public static void main(String[] args) {
        Object a = new Object();
        Object b = new Object();
        Object c = a;
        System.out.println("Object a=b :" + isEqualTo(a, b));
        System.out.println("Object a=c :" + isEqualTo(a, c));

        a = 10;
        b = 10;
        c = (Integer) a;
        System.out.println("Integer a=b :" + isEqualTo(a, b));
        System.out.println("Integer a=c :" + isEqualTo(a, c));
    }
}