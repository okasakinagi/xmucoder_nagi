public class Rectangle extends Graph {
    private double width, height;

    Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    @Override
    public double Calculate_Area() {
        return width * height;
    }

}
