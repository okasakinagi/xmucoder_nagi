import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello, World!");

        Scanner input = new Scanner(System.in);
        System.out.println("Enter the first number:");
        int a = input.nextInt();
        System.out.println("Enter the second number:");
        int b = input.nextInt();
        int sum = a + b;
        System.out.printf("%s%d%n", "The sum is:", sum);
        input.close();
    }
}
