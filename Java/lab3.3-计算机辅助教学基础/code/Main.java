import java.util.Scanner;
import java.security.SecureRandom;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("System startup, self-test completed, device IO normal.");
        Memory[] memory = new Memory[10];
        int idx = 0;
        while (true) {
            System.out.println("******Welcome to a new start******");
            System.out.println("1.Start a test.");
            System.out.println("2.look for memory(nly the last 10 times).");
            System.out.println("3.Exit.");
            System.out.print("Please choose a function:");
            int choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    System.out.println("******Start a test******");
                    int temp = new_test(scanner);
                    idx = store_memory(memory, idx, temp);
                    System.out.println("Test completed!");
                    System.out.println("Your accuracy is " + String.format("%.2f", (temp / 10.0) * 100) + "%!");
                    if (temp >= 8)
                        System.out.println("Congratulations, you are ready to go to the next level！");
                    else
                        System.out.println("Please ask your teacher for extra help.");
                    break;
                case 2:
                    System.out.println("******Look for memory(nly the last 10 times)******");
                    look_for_memory(scanner, memory, idx);
                    break;
                case 3:
                    scanner.close();
                    System.out.println("******Thank you for using!******");
                    return;
                default:
                    System.out.println("******Invalid input, please try again!******");
                    continue;
            }
            System.out.println("******system restarting......******");
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static int new_test(Scanner scanner) {
        SecureRandom random = new SecureRandom();
        int count_rights = 0;
        for (int i = 0; i < 10; i++) {
            int a = random.nextInt(10);
            int b = random.nextInt(10);
            System.out.print(a + "*" + b + "=");
            int result = scanner.nextInt();
            if (result == a * b) {
                count_rights++;
                switch (random.nextInt(4)) {
                    case 0:
                        System.out.println("Very good!");
                        break;
                    case 1:
                        System.out.println("Excellent!");
                        break;
                    case 2:
                        System.out.println("Nice work!");
                        break;
                    case 3:
                        System.out.println("Keep up the good work!");
                        break;
                    default:
                        break;
                }
            } else {
                switch (random.nextInt(4)) {
                    case 0:
                        System.out.println("No. Please try again.");
                        break;
                    case 1:
                        System.out.println("Wrong. Try once more.");
                        break;
                    case 2:
                        System.out.println("Don't give up!");
                        break;
                    case 3:
                        System.out.println("No. Keep trying.");
                        break;
                    default:
                        break;
                }

            }
        }
        return count_rights;
    }

    public static int store_memory(Memory[] memory, int idx, int count) {
        if (idx >= 10)
            idx = 0;
        memory[idx++] = new Memory(count);
        return idx;
    }

    public static void look_for_memory(Scanner scanner, Memory[] memory, int idx) {
        while (true) {
            System.out.print("Please enter which test you want to look for(1-10):");
            int choice = scanner.nextInt();
            int temp;
            if (choice >= 1 && choice <= 10) {
                if (idx >= choice)
                    temp = idx - choice;
                else
                    temp = idx - choice + 10;
                if (memory[temp] == null)
                    System.out.println("No such test!");
                else
                    System.out.println("Your accuracy in the " + (memory[temp].getIdx() + 1) + "th test is "
                            + String.format("%.2f", (memory[temp].getGrade() / 10.0) * 100) + "%");

                return;
            }
            System.out.println("Invalid input, please try again!");
        }
    }
}