import java.util.Scanner;

public class Main {

    public static String get_check(Scanner sc, int type) {
        String temp = sc.next();
        switch (type) {
            case 1:
                if (temp.equals("#"))
                    System.exit(0);
                while (!Match.match_user(temp)) {
                    System.out.println("Invalid User Name! Please Re-Enter:");
                    temp = sc.next();
                }
                return temp;
            case 2:
                while (!Match.match_password(temp)) {
                    System.out.println("Invalid Password! Please Re-Enter:");
                    temp = sc.next();
                }
                return temp;
            case 3:
                while (!Match.match_email(temp)) {
                    System.out.println("Invalid Email! Please Re-Enter:");
                    temp = sc.next();
                }
                return temp;
            default:
                return null;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int count = 0;
        System.out.println("System Start,use # in User Name to exit");
        while (true) {
            System.out.println("User " + count);
            System.out.print("Enter User Name:");
            String user_name = get_check(sc, 1);
            System.out.print("Enter Password:");
            String password = get_check(sc, 2);
            System.out.print("Enter Email:");
            String email = get_check(sc, 3);
            System.out.println("User " + (++count) + ':' + user_name + ' ' + password + ' ' + email);
        }
    }
}