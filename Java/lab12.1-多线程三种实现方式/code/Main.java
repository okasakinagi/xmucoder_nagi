import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        // 使用继承Thread的方式完成
        System.out.println("使用继承Thread的方式完成");
        Threadway thread1 = new Threadway("Thread1"), thread2 = new Threadway("Thread2");
        thread1.start();
        thread2.start();
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
        }
        // 使用实现Runnable接口的方式完成
        System.out.println("使用实现Runnable接口的方式完成");
        Runnableway runnable1 = new Runnableway("Runnable1"), runnable2 = new Runnableway("Runnable2");
        Thread thread3 = new Thread(runnable1), thread4 = new Thread(runnable2);
        thread3.start();
        thread4.start();
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
        }
        // 使用线程池管理
        System.out.println("使用线程池管理");
        ExecutorService threadExecutor = Executors.newFixedThreadPool(2);
        Runnableway ThreadPool1 = new Runnableway("ThreadPool1"), ThreadPool2 = new Runnableway("ThreadPool2");
        threadExecutor.execute(ThreadPool1);
        threadExecutor.execute(ThreadPool2);
        threadExecutor.shutdown();
    }
}