public class Course {
    private static int count = 0;
    private String courseId;
    private String courseName;
    private int coursekind;

    Course(String courseName, int kind) {
        this.courseId = Integer.toString(100 + count++);
        this.courseName = courseName;
        this.coursekind = kind;// 默认必修课=1，选修课=2
    }

    Course(Course course) {
        this.courseId = course.getCourseId();
        this.courseName = course.getCourseName();
        this.coursekind = course.getCoursekind();
    }

    public String getCourseId() {
        return courseId;
    }

    public String getCourseName() {
        return courseName;
    }

    public int getCoursekind() {
        return coursekind;
    }
}
