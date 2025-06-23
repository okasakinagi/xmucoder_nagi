import java.io.File;
import java.util.Date;
import java.text.SimpleDateFormat;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        File file;
        while (true) {
            System.out.print("Please enter the path of the file: ");
            String path = sc.nextLine();
            file = new File(path);
            if (file.exists()) {
                break;
            } else {
                System.out.println("File not found");
            }
        }
        if (file.isDirectory()) {
            System.out.println("This is a directory");
            int fileCount = 0, dirCount = 0;
            for (File f : file.listFiles()) {
                if (f.isDirectory()) {
                    dirCount++;
                } else {
                    fileCount++;
                }
            }
            System.out.println("Number of files: " + fileCount);
            System.out.println("Number of directories: " + dirCount);
        } else {
            System.out.println("This is a file");
            System.out.println("File size: " + file.length() + " bytes");
            long lastModified = file.lastModified();
            Date date = new Date(lastModified);
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            System.out.println("Last modified: " + sdf.format(date));
        }
    }
}