import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Spell_Check sc = new Spell_Check(
                "default handy birthday example test correct spelling checker program computer");
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Enter a word to check or # to quit: ");
            String word = scanner.next();
            if (word.startsWith("#"))
                break;
            String result = sc.check(word);
            if (result == null)
                System.out.println("Word is not spelled correctly.");
            else {
                if (result.equals(word))
                    System.out.println("Word is spelled correctly.");
                else {
                    System.out.println("Word is not spelled correctly. Did you mean: " + result + "?");
                }
            }
        }
        scanner.close();
    }
}