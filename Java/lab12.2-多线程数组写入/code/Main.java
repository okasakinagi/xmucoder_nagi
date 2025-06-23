import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        int[] arr = new int[10000];
        Arrays.fill(arr, 0);

        WriteThread thread1 = new WriteThread(arr, 1, 10);
        WriteThread thread2 = new WriteThread(arr, 100, 1000);
        WriteThread thread3 = new WriteThread(arr, 2000, 3000);
        WriteThread thread4 = new WriteThread(arr, 4000, 5000);

        ExecutorService executorService = Executors.newFixedThreadPool(4);
        executorService.execute(thread1);
        executorService.execute(thread2);
        executorService.execute(thread3);
        executorService.execute(thread4);

        executorService.shutdown();

        System.out.print(arr[0]);
        for (int i = 1; i < arr.length; i++) {
            for (; i % 500 != 0; i++)
                System.out.print(arr[i]);
            System.out.println();
        }
    }
}