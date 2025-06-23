import java.util.Random;
import java.util.Scanner;

public class CycleBuffer implements Runnable {
    int[] buffer = new int[4];
    int writeidx = 0, readidx = 0, vaild = 0;
    String inputname, outputname;

    CycleBuffer(String inputname, String outputname) {
        this.inputname = inputname;
        this.outputname = outputname;
    }

    public void run() {
        if (Thread.currentThread().getName().equals(inputname)) {
            while (vaild != -1)
                write_read(true);
        } else if (Thread.currentThread().getName().equals(outputname)) {
            Scanner sc = new Scanner(System.in);
            System.out.print("请输入读取次数：");
            int num = sc.nextInt();
            read_print(num);
            sc.close();
        }
    }

    public synchronized int write_read(boolean iswrite) {
        if (iswrite) {
            while (vaild == 4) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
            Random rand = new Random();
            buffer[(writeidx++) % 4] = rand.nextInt(10) + 1;
//            System.out.println("第" + (writeidx) + "次写入：" + buffer[(writeidx - 1) % 4]);
            vaild++;
            notifyAll();

        } else {
            while (vaild == 0) {
                try {
                    wait();
                } catch (InterruptedException e) {

                    Thread.currentThread().interrupt();
                }
            }
            vaild--;
            notifyAll();
            return buffer[(readidx++) % 4];
        }

        return 0;
    }

    public void read_print(int readtimes) {
        for (int i = 0; i < readtimes; i++) {
            int temp = write_read(false);
            if (temp != 0)
                System.out.println("第" + (readidx) + "次读取：" + temp);
        }
        vaild = -1;
        write_read(false);
    }
}
