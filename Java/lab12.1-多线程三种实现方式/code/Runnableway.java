public class Runnableway implements Runnable {
    private String name;

    Runnableway(String name) {
        this.name = name;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            System.out.println(name + ": " + i);
        }
    }

}
