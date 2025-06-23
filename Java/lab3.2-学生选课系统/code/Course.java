public class Course {
    private static int count = 0;
    private String courseId;
    private String courseName;
    private int coursegrade;

    Course(String courseName) {
        this.courseId = Integer.toString(100 + count++);
        this.courseName = courseName;
    }

    Course(Course course) {
        this.courseId = course.getCourseId();
        this.courseName = course.getCourseName();
    }

    public String getCourseId() {
        return courseId;
    }

    public String getCourseName() {
        return courseName;
    }

    public void setCoursegrade(int coursegrade) {
        this.coursegrade = coursegrade;
    }

    public int getCoursegrade() {
        return coursegrade;
    }
}
