import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CycleBuffer {
    private final int[] buffer;
    private int writeidx;
    private int readidx;
    private final int size;
    private int count = 0;
    private Lock lock = new ReentrantLock();
    private Condition notFull = lock.newCondition();
    private Condition notEmpty = lock.newCondition();

    CycleBuffer(int size) {
        this.size = size;
        buffer = new int[size];
        writeidx = 0;
        readidx = 0;
    }

    public void put(int value) throws InterruptedException {
        lock.lock();
        try {
            while (count == size) {
                notFull.await();
            }
            buffer[(writeidx++) % size] = value;
            count++;
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }

    public int get() throws InterruptedException {
        lock.lock();
        int res = 0;
        try {
            while (count == 0) {
                notEmpty.await();
            }
            res = buffer[(readidx++) % size];
            count--;
            notFull.signal();
        } finally {
            lock.unlock();
        }
        return res;
    }
}
