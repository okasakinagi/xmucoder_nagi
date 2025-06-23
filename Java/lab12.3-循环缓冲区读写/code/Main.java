public class Main {
    public static void main(String[] args) {
        String input = "写入线程", output = "读取线程";
        CycleBuffer buffer = new CycleBuffer(input, output);
        Thread in = new Thread(buffer), out = new Thread(buffer);
        in.setName(input);
        out.setName(output);
        in.start();
        out.start();
    }
}