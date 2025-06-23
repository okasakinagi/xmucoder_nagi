import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

//测试输入：李建国 王秀英 张建军 刘淑芳 陈丽华 杨宇航 杨宇航 赵诗雨 李建国 吴明轩 周佳怡 刘淑芳 郑浩宇 #
//不重复的共十个名字
public class Main {
    public static void main(String[] args) {
        Set<String> name = new HashSet<>();

        Scanner scanner = new Scanner(System.in);

        while (true) {
            String input = scanner.next();
            if (input.equals("#")) {
                break;
            }
            name.add(input);
        }

        System.out.println(name);
        scanner.close();
    }
}