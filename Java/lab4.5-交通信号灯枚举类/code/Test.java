public class Test {
    public static void main(String[] args) {
        for (TrafficLight light : TrafficLight.values()) {
            System.out.println(light.name() + "的RGB值是：" + light.getRgb());
        }
    }
}
