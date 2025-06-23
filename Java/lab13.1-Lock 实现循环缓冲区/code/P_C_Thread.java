import java.util.Random;
import java.util.Scanner;

public class P_C_Thread implements Runnable {
    boolean isProducer = false;
    CycleBuffer buffer;

    public P_C_Thread(boolean isProducer, CycleBuffer buffer) {
        this.isProducer = isProducer;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        if (isProducer) {
            try {
                Random rand = new Random();
                while (true) {
                    buffer.put(rand.nextInt(10) + 1);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } else {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter the number of elements to be consumed:");
            int n = sc.nextInt();
            for (int i = 0; i < n; i++) {
                try {
                    System.out.println("Consumed: " + buffer.get());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            sc.close();
        }

    }
}
