package com.lab133;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class BallApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(BallApplication.class.getResource("ball-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);
        stage.setMinHeight(400);
        stage.setMaxHeight(400);
        stage.setMinWidth(600);
        stage.setMaxWidth(600);
        stage.setTitle("Balls!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}