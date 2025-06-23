import java.util.Random;

public class Main {
    public static void main(String[] args) {
        // 生成两个本科生和两个研究生对象
        Postgraduate_student[] postgraduate_students = new Postgraduate_student[2];
        Undergraduate_student[] undergraduate_students = new Undergraduate_student[2];

        postgraduate_students[0] = new Postgraduate_student("张三", 1, "Mr.Zhang");
        postgraduate_students[1] = new Postgraduate_student("李四", 1, "Mr.Li");
        undergraduate_students[0] = new Undergraduate_student("王五", 2);
        undergraduate_students[1] = new Undergraduate_student("赵六", 2);
        // 设置课程信息
        Course[] compulsory_course = new Course[2];
        Course[] optional_course = new Course[2];

        compulsory_course[0] = new Course("高等数学", 1);
        compulsory_course[1] = new Course("线性代数", 1);
        optional_course[0] = new Course("青年期红处方", 2);
        optional_course[1] = new Course("阿拉伯语入门", 2);

        // 设置本科生和研究生选修课程信息
        Random rand = new Random();
        for (int i = 0; i < 2; i++) {
            postgraduate_students[i].addCourse(compulsory_course[0]);
            postgraduate_students[i].addCourse(compulsory_course[1]);
            if (rand.nextBoolean()) {
                postgraduate_students[i].addCourse(optional_course[rand.nextInt(2)]);
            } else {
                postgraduate_students[i].addCourse(optional_course[0]);
                postgraduate_students[i].addCourse(optional_course[1]);
            }
        }
        for (int i = 0; i < 2; i++) {
            undergraduate_students[i].addCourse(compulsory_course[0]);
            undergraduate_students[i].addCourse(compulsory_course[1]);
            if (rand.nextBoolean()) {
                undergraduate_students[i].addCourse(optional_course[rand.nextInt(2)]);
            } else {
                undergraduate_students[i].addCourse(optional_course[0]);
                undergraduate_students[i].addCourse(optional_course[1]);
            }
        }

        // 打印本科生和研究生选修课程信息
        for (int i = 0; i < postgraduate_students.length; i++) {
            postgraduate_students[i].display();
        }
        for (int i = 0; i < undergraduate_students.length; i++) {
            undergraduate_students[i].display();
        }
    }
}