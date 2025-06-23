public enum TrafficLight {
    RED("255,0,0"),
    GREEN("0,255,0"),
    YELLOW("255,255,0");

    private final String rgb;

    TrafficLight(String rgb) {
        this.rgb = rgb;
    }

    public String getRgb() {
        return rgb;
    }
}
