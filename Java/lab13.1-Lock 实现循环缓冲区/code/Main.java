public class Main {
    public static void main(String[] args) {
        CycleBuffer buffer = new CycleBuffer(4);
        Thread produce = new Thread(new P_C_Thread(true, buffer));
        Thread consume = new Thread(new P_C_Thread(false, buffer));
        produce.setDaemon(true);

        produce.start();
        consume.start();
    }
}