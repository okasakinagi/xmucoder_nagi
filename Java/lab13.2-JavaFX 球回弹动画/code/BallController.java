package com.lab132;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class BallController {
    @FXML
    private Label label;
    @FXML
    private Pane pane;
    private final int Width = 590, Height = 380;
    private Circle ball;
    private double dx = 0, dy = 0;
    private AnimationTimer timer;
    private final double radius = 20;

    @FXML
    public void initialize() {

    }

    @FXML
    public void OnMouseClicked_Pane(MouseEvent e) {
        if (timer != null)
            timer.stop();
        if (ball == null) {
            ball = new Circle(e.getX(), e.getY(), radius);
            ball.setFill(Color.BLUE);
            pane.getChildren().add(ball);
        } else {
            ball.setCenterX(e.getX());
            ball.setCenterY(e.getY());
        }
        double angle = Math.random() * 2 * Math.PI;
        dx = 5 * Math.cos(angle);
        dy = 5 * Math.sin(angle);
        if (timer == null)
            startAnimationTimer();
        else
            timer.start();
    }

    private void startAnimationTimer() {
        timer = new AnimationTimer() {
            @Override
            public void handle(long now) {
                if (ball != null) {
                    ball.setCenterX(ball.getCenterX() + dx);
                    ball.setCenterY(ball.getCenterY() + dy);
                    if (ball.getCenterX() + radius >= Width || ball.getCenterX() - radius <= 0)
                        dx = -dx;
                    if (ball.getCenterY() + radius >= Height || ball.getCenterY() - radius <= 0)
                        dy = -dy;
                }
            }
        };
        timer.start();
    }
}