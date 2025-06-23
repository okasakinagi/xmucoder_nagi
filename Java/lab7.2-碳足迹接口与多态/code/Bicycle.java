public class Bicycle implements CarbonFootprint {
    @Override
    public double getCarbonFootprint() {
        return 0;
    }

    @Override
    public String toString() {
        return "Bicycle";
    }
}
