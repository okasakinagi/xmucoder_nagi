import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
    public static Set<Integer> isprime(int n) {
        Set<Integer> primes = new HashSet<>();
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                Set<Integer> temp = isprime(i);
                if (temp.isEmpty()) {
                    primes.add(i);
                } else {
                    primes.addAll(temp);
                }
            }
        }
        return primes;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Enter a number(end whit #): ");
            int n;
            try {
                n = scanner.nextInt();
            } catch (Exception e) {
                String input = scanner.nextLine();
                if (input.startsWith("#")) {
                    scanner.close();
                    System.exit(0);
                }
                System.out.println("Please input a number");
                continue;
            }
            Set<Integer> primes = isprime(n);
            if (primes.isEmpty()) {
                System.out.print("This is a PrimeNumber.");
            } else {
                System.out.print("This is not a PrimeNumber with factors: ");
                for (int i : primes) {
                    System.out.print(i + " ");
                }
            }
            System.out.println();

        }

    }
}