import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        Buliding buliding = new Buliding(300);
        Car car = new Car(20);
        Bicycle bicycle = new Bicycle();

        ArrayList<CarbonFootprint> arraylist = new ArrayList<CarbonFootprint>();

        arraylist.add(buliding);
        arraylist.add(car);
        arraylist.add(bicycle);

        for (CarbonFootprint cf : arraylist) {
            System.out.println(cf.toString() + " Have Carbon footprint: " + cf.getCarbonFootprint());
        }
    }
}