public class Car implements CarbonFootprint {
    double fuelConsumption;

    Car(double fuelConsumption) {
        this.fuelConsumption = fuelConsumption;
    }

    @Override
    public double getCarbonFootprint() {
        return fuelConsumption * 2.3;
    }

    @Override
    public String toString() {
        return "Car with fuelConsumption：" + fuelConsumption +
                '}';
    }
}
