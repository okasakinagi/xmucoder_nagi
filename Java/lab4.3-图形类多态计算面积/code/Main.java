import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextLine().charAt(0) - '0';
        for (int i = 0; i < N; i++) {
            String line = scanner.nextLine();
            if (line.length() <= 4) {
                Rectangle temp = new Rectangle(line.charAt(0) - '0', line.charAt(2) - '0');
                System.out
                        .println(String.format("%.2f", temp.Calculate_Area()));
            } else {
                Triangle temp = new Triangle(line.charAt(0) - '0', line.charAt(2) - '0', line.charAt(4) - '0');
                System.out
                        .println(String.format("%.2f", temp.Calculate_Area()));
            }
        }
        scanner.close();
    }
}