
public class Main {
    public static void main(String[] args) {
        String name1 = "张三", name2 = "", name3 = "李一二三四五", name4 = "赵武";
        String address1 = "厦门", address2 = "上海市", address3 = "福建省", address4 = "123456";
        try {
            Student student1 = new Student(name1, address1);
        } catch (Exception e) {
            System.out.println("first student creation error:" + e.getMessage());
        }
        try {
            Student student2 = new Student(name2, address2);
        } catch (Exception e) {
            System.out.println("second student creation error:" + e.getMessage());
        }
        try {
            Student student3 = new Student(name3, address3);
        } catch (Exception e) {
            System.out.println("third student creation error:" + e.getMessage());
        }
        try {
            Student student4 = new Student(name4, address4);
        } catch (Exception e) {
            System.out.println("fourth student creation error:" + e.getMessage());
        }
        System.out.println("4 students have been created.");
    }
}