
public class Test {
    public static void main(String[] args) {
        System.out.println("更换为交通工具");
        Vehicle vehicle = new Vehicle();
        vehicle.run();

        System.out.println("更换为船");
        vehicle = new Ship();
        vehicle.run();

        System.out.println("更换为飞机");
        vehicle = new Aeroplane();
        vehicle.run();

        System.out.println("更换为汽车");
        vehicle = new Motor();
        vehicle.run();

        System.out.println("更换为公共汽车");
        vehicle = new Bus();
        vehicle.run();

        System.out.println("更换为轿车");
        vehicle = new Car();
        vehicle.run();
    }
}