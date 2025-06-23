public class Buliding implements CarbonFootprint {
    double energyConsumption;

    Buliding(double energyConsumption) {
        this.energyConsumption = energyConsumption;
    }

    @Override
    public double getCarbonFootprint() {
        return energyConsumption * 0.5;
    }

    @Override
    public String toString() {
        return "Buliding with energyConsumption：" + energyConsumption +
                '}';
    }
}
