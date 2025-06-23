import java.util.Scanner;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // 按要求仅输入两个学生，并同时选修输入的两门课程
        Student[] student;
        student = new Student[2];
        // 学生1
        System.out.println("please start enter the first student imformation:");
        System.out.print("name:");
        String name1 = scanner.next();
        System.out.print("class:");
        int class1 = scanner.nextInt();
        System.out.print("phone number(null with 0):");
        long phone1 = scanner.nextLong();
        if (phone1 == 0)
            student[0] = new Student(name1, class1);
        else {
            String phonetemp = Long.toString(phone1);
            student[0] = new Student(name1, class1, phonetemp);
        }
        // 学生2，与前者相同，放弃用循环
        System.out.println("please start enter the second student imformation:");
        System.out.print("name:");
        String name2 = scanner.next();
        System.out.print("class:");
        int class2 = scanner.nextInt();
        System.out.print("phone number(null with 0):");
        long phone2 = scanner.nextLong();
        if (phone2 == 0)
            student[1] = new Student(name2, class2);
        else {
            String phonetemp = Long.toString(phone2);
            student[1] = new Student(name2, class2, phonetemp);
        }
        // 测试课程两个
        Course[] course = new Course[2];
        course[0] = new Course("math");
        course[1] = new Course("english");
        // 分配课程
        for (int i = 0; i < student.length; i++) {
            student[i].addCourse(course[0]);
            student[i].addCourse(course[1]);
        }
        // 测试成绩设置
        Random rand = new Random();
        for (int i = 0; i < student.length; i++) {
            for (int j = 0; j < student[i].get_course_idx(); j++) {
                student[i].set_course_grade(course[j].getCourseName(), rand.nextInt(21) + 80);
            }
        }
        // 输出学生信息
        for (int i = 0; i < student.length; i++) {
            student[i].print();
        }
        scanner.close();

    }
}