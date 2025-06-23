public class SomeClass {
    private void someMethod1() throws Exception {
        throw new Exception();
    }

    public void someMethod2() throws Exception {
        try {
            someMethod1();
        } catch (Exception e) {
            System.out.println("someMethod2 caught exception");
            throw e;
        }
    }
}
