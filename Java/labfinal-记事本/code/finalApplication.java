package com.finallab;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class finalApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(finalApplication.class.getResource("final-lab.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);
        stage.setMinHeight(150);
        stage.setMinWidth(250);
        stage.setTitle("记事本");
        Image icon = new Image("file:relatedata/icons.png");
        stage.getIcons().add(icon);
        stage.setScene(scene);
        finalController controller = fxmlLoader.getController();
        stage.show();
        stage.setOnCloseRequest(event -> {
            event.consume();
            if (controller.close_onaction()) {
                stage.close();
            }
        });
    }

    public static void main(String[] args) {
        launch();
    }
}