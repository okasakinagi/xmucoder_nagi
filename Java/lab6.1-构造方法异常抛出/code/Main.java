public class Main {
    public static void main(String[] args) throws Exception {
        try {
            SomeClass someclass = new SomeClass();
        } catch (Exception e) {
            System.err.println("successfully caught exception");
            throw e;//重抛中断程序
        }
        System.out.println("failed to caught exception");
    }
}