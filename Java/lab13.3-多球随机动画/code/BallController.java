package com.lab133;

import javafx.animation.AnimationTimer;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;

import java.util.ArrayList;

public class BallController {
    @FXML
    private Label label;
    @FXML
    private Pane pane;
    private final int Width = 590, Height = 380;
    private final ArrayList<Ball> balls = new ArrayList<>();
    private AnimationTimer timer;

    @FXML
    public void initialize() {

    }

    @FXML
    public void OnMouseClicked_Pane(MouseEvent e) {
        if (timer != null)
            timer.stop();
        Color color = Color.rgb((int) (Math.random() * 255), (int) (Math.random() * 255), (int) (Math.random() * 255));
        double angle = Math.random() * 2 * Math.PI;
        double dx = 5 * Math.cos(angle);
        double dy = 5 * Math.sin(angle);
        double radius = 20;
        Ball ball = new Ball(e.getX(), e.getY(), radius, dx, dy, color);
        balls.add(ball);
        pane.getChildren().add(ball.getCircle());
        if (timer == null)
            startAnimationTimer();
        else
            timer.start();
    }

    private void startAnimationTimer() {
        timer = new AnimationTimer() {
            @Override
            public void handle(long now) {
                if (!balls.isEmpty()) {
                    for (Ball b : balls) {
                        b.update();
                        b.checkCollision(Width, Height);
                    }
                }
            }
        };
        timer.start();
    }
}