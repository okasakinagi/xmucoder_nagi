public class Primr_number {
    public boolean judge1(int value) {
        for (int i = 2; i <= value / 2; i++) {
            if (value % i == 0)
                return false;
        }
        if (value == 1)
            return false;
        return true;
    }

    public boolean judge2(int value) {
        for (int i = 2; i * i <= value; i++) {
            if (value % i == 0)
                return false;
        }
        if (value == 1)
            return false;
        return true;
    }
}