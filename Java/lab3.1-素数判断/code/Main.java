
public class Main {
    public static void main(String[] args) {
        Primr_number judger = new Primr_number();
        int count = 0;// 加入计数器
        // 寻找10000以内的素数，前5000个用judge1,后5000个用judge2
        System.out.println("the number is prime between 1 and 10000:");
        for (int i = 1; i <= 5000; i++) {
            if (judger.judge1(i)) {
                System.out.println(i);
                count++;
            }
        }
        for (int i = 5001; i <= 10000; i++) {
            if (judger.judge2(i)) {
                System.out.println(i);
                count++;
            }
        }
        System.out.println("there is " + count + " prime numbers in total.");
    }
}