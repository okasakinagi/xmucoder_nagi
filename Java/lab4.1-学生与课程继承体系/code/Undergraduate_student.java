public class Undergraduate_student extends Student {
    Undergraduate_student(String sname, int sClass) {
        super(sname, sClass, 1);
    }

    void display() {
        super.print_student();
        super.print_course();
    }
}
