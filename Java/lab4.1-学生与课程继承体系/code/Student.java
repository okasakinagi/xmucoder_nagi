public class Student {
    private static int cout = 0;
    private String ID;
    private String name;
    private int Class;
    private Course[] courses;
    private int course_idx;

    Student(String sname, int sClass, int kind) {
        this.ID = Integer.toString(kind * 10000 + cout++);// 默认本科生kind=0,研究生kind=1
        this.name = sname;
        this.Class = sClass;
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

    void print_student() {
        System.out.println("Student:");
        System.out.println("ID: " + ID + ", Name: " + name + ", Class: " + Class);
    }

    void print_course() {
        System.out.println("chosen courses: ");
        for (int i = 0; i < course_idx; ++i) {
            System.out.print(courses[i].getCourseId() + ':' + courses[i].getCourseName());
            if (courses[i].getCoursekind() == 1)
                System.out.println(" coursekind:必修课");
            else
                System.out.println(" coursekind:选修课");
        }
    }

}
