public class Memory {
    private static int count = 0;
    private int idx;
    private int grade;

    Memory(int grade) {
        this.idx = count++;
        this.grade = grade;
    }

    public int getIdx() {
        return this.idx;
    }

    public double getGrade() {
        return this.grade;
    }
}
