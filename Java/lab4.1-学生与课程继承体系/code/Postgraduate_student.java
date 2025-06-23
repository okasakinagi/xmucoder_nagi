public class Postgraduate_student extends Student {
    private String tutor_name;

    Postgraduate_student(String sname, int sClass, String tutor_name) {
        super(sname, sClass, 2);
        this.tutor_name = tutor_name;
    }

    public void display() {
        super.print_student();
        System.out.println("Tutor Name : " + tutor_name);
        super.print_course();
    }
}
