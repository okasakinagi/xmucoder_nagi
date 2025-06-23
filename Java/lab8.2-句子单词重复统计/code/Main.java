import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;


//The quick brown fox jumps over the lazy dog. The quick brown fox is very fast. The lazy dog sleeps all day. The quick brown fox and the lazy dog are in the yard.
//上一行为测试输入，理论输出为6
public class Main {
    public static void main(String[] args) {
        Map<String, Integer> map = new HashMap<>();
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        scanner.close();
        input = input.toLowerCase();
        int start = 0, flag = 0;
        for (int i = 0; i < input.length(); i++) {
            if ((input.charAt(i) >= 'a' && input.charAt(i) <= 'z')
                    || (input.charAt(i) >= 'A' && input.charAt(i) <= 'Z')) {
                if (flag == 0) {
                    start = i;
                    flag = 1;
                }
            } else {
                if (flag == 1) {
                    String temp = input.substring(start, i);
                    if (map.containsKey(temp)) {
                        map.put(temp, map.get(temp) + 1);
                    } else {
                        map.put(temp, 1);
                    }
                    flag = 0;
                }
            }
        }
        int sum = 0;
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            if (entry.getValue() > 1) {
                sum += 1;
            }
        }
        System.out.println(sum);
    }
}