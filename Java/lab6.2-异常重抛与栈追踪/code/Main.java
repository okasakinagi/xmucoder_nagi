
public class Main {
    public static void main(String[] args) {
        SomeClass someclass = new SomeClass();
        try {
            someclass.someMethod2();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}