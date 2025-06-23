public class Main {
    public static void main(String[] args) {
        Pair<Integer, String> pair = new Pair<Integer, String>(10, "Hello");
        System.out.println("First:" + pair.getFirst() + ",Second:" + pair.getSecond());
        pair.setSecond("World");
        System.out.println("First:" + pair.getFirst() + ",Second:" + pair.getSecond());
        pair.setFirst(20);
        System.out.println("First:" + pair.getFirst() + ",Second:" + pair.getSecond());
    }
}