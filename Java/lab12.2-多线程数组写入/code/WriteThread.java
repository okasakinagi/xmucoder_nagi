public class WriteThread implements Runnable {
    private int start, end;
    private int[] array;

    WriteThread(int[] array, int start, int end) {
        this.array = array;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        for (int i = start; i < end; i++) {
            array[i] = 1;
        }
    }

}
