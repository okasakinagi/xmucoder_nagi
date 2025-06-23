package com.lab133;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class Ball {
    private Circle circle;
    private double dx, dy;

    Ball(double x, double y, double r, double dx, double dy, Color color) {
        this.circle = new Circle(x, y, r);
        this.circle.setFill(color);
        this.dx = dx;
        this.dy = dy;
    }

    public Circle getCircle() {
        return circle;
    }

    public void update() {
        circle.setCenterX(circle.getCenterX() + dx);
        circle.setCenterY(circle.getCenterY() + dy);
    }

    public void checkCollision(int Width, int Height) {
        if (circle.getCenterX() + circle.getRadius() >= Width || circle.getCenterX() - circle.getRadius() <= 0)
            dx = -dx;
        if (circle.getCenterY() + circle.getRadius() >= Height || circle.getCenterY() - circle.getRadius() <= 0)
            dy = -dy;

    }
}
