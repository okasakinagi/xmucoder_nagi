package com.lab44;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Ellipse;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
import java.util.Random;
import java.util.Scanner;

public class DrawingAppController {
    private static final int MAX_SHAPES = 20;
    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;
    private int shapeCount = 0;

    @FXML
    private Pane root;

    public void initialize() {
        // 使用新线程处理输入，防止在输入过程中javafx窗口卡死
        Thread inputThread = new Thread(() -> {
            Scanner scanner = new Scanner(System.in);
            Random random = new Random();

            while (shapeCount < MAX_SHAPES) {
                int choice = random.nextInt(3);
                switch (choice) {
                    case 0:
                        drawLine(scanner);
                        break;
                    case 1:
                        drawRectangle(scanner);
                        break;
                    case 2:
                        drawEllipse(scanner);
                        break;
                }
            }
            scanner.close();
        });
        inputThread.setDaemon(true);//守护线程，主线程关闭时会一同关闭
        inputThread.start();
    }

    private void drawLine(Scanner scanner) {
        System.out.println("绘制直线，请输入起点和终点坐标（范围 0 - " + WIDTH + "）：");
        System.out.print("起点 x1: ");
        double x1 = getValidInput(scanner, 0, WIDTH);
        System.out.print("起点 y1: ");
        double y1 = getValidInput(scanner, 0, HEIGHT);
        System.out.print("终点 x2: ");
        double x2 = getValidInput(scanner, 0, WIDTH);
        System.out.print("终点 y2: ");
        double y2 = getValidInput(scanner, 0, HEIGHT);

        Platform.runLater(() -> {
            Line line = new Line(x1, y1, x2, y2);
            line.setStroke(Color.BLACK);
            root.getChildren().add(line);
        });//由于使用多线程，
        shapeCount++;
    }

    private void drawRectangle(Scanner scanner) {
        System.out.println("绘制矩形，请输入左上角坐标和宽高（范围 0 - " + WIDTH + "）：");
        System.out.print("左上角 x: ");
        double x = getValidInput(scanner, 0, WIDTH);
        System.out.print("左上角 y: ");
        double y = getValidInput(scanner, 0, HEIGHT);
        System.out.print("宽度: ");
        double width = getValidInput(scanner, 0, WIDTH - x);
        System.out.print("高度: ");
        double height = getValidInput(scanner, 0, HEIGHT - y);

        Platform.runLater(() -> {
            Rectangle rectangle = new Rectangle(x, y, width, height);
            rectangle.setFill(Color.TRANSPARENT);
            rectangle.setStroke(Color.BLACK);
            root.getChildren().add(rectangle);
        });
        shapeCount++;
    }

    private void drawEllipse(Scanner scanner) {
        System.out.println("绘制椭圆，请输入中心坐标和长短轴半径（范围 0 - " + WIDTH + "）：");
        System.out.print("中心 x: ");
        double centerX = getValidInput(scanner, 0, WIDTH);
        System.out.print("中心 y: ");
        double centerY = getValidInput(scanner, 0, HEIGHT);
        System.out.print("长轴半径: ");
        double radiusX = getValidInput(scanner, 0, Math.min(centerX, WIDTH - centerX));
        System.out.print("短轴半径: ");
        double radiusY = getValidInput(scanner, 0, Math.min(centerY, HEIGHT - centerY));

        Platform.runLater(() -> {
            Ellipse ellipse = new Ellipse(centerX, centerY, radiusX, radiusY);
            ellipse.setFill(Color.TRANSPARENT);
            ellipse.setStroke(Color.BLACK);
            root.getChildren().add(ellipse);
        });
        shapeCount++;
    }

    private double getValidInput(Scanner scanner, double min, double max) {
        double input;
        while (true) {
            try {
                input = scanner.nextDouble();//此处输入可能报错中断
                if (input >= min && input <= max) {
                    break;
                } else {
                    System.out.println("输入无效，请输入范围在 " + min + " - " + max + " 的值。");
                }
            } catch (Exception e) {
                System.out.println("输入无效，请输入一个有效的数字。");
                scanner.nextLine();
            }
        }
        return input;
    }
}    