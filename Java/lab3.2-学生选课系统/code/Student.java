public class Student {
    private static int cout = 0;
    private String ID;
    private String name;
    private int Class;
    private String phone_number;
    private Course[] courses;
    private int course_idx;

    Student(String sname, int sClass, String sphone_number) {
        this.ID = Integer.toString(10000 + cout++);
        this.name = sname;
        this.Class = sClass;
        this.phone_number = sphone_number;
        this.courses = new Course[10];
    }

    Student(String sname, int sClass) {
        this.ID = Integer.toString(10000 + cout++);
        this.name = sname;
        this.Class = sClass;
        this.phone_number = null;
        this.courses = new Course[10];
    }

    boolean addCourse(Course course) {
        if (course_idx < 10) {
            courses[course_idx++] = new Course(course);
            return true;
        } else
            return false;
    }

    int get_course_idx() {
        return course_idx;
    }

    void set_course_grade(String coursename, int grade) {
        for (int i = 0; i < course_idx; ++i) {
            if (courses[i].getCourseName().equals(coursename)) {
                courses[i].setCoursegrade(grade);
                return;
            }
        }
    }

    void print() {
        System.out.println("Student:");
        System.out.println("ID: " + ID + ", Name: " + name + ", Class: " + Class + ", Phone Number: " + phone_number);
        System.out.println("chosen courses and grade: ");
        for (int i = 0; i < course_idx; ++i) {
            System.out.println(courses[i].getCourseId() + ':' + courses[i].getCourseName() + ",grade: "
                    + courses[i].getCoursegrade());
        }
    }
}
