package com.finallab;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Font;
import javafx.stage.Stage;

import java.util.List;

public class FontViewController {
    @FXML
    private AnchorPane root_pane;
    @FXML
    private ChoiceBox font_choice;
    @FXML
    private Slider size_choice;
    @FXML
    private Label size_label;
    @FXML
    private Button ack_button;
    @FXML
    private TextArea text_area;

    private finalController controller;// 父控制器
    private String font;// 字体
    private int size;// 字体大小

    // 初始化，利于观察字体和大小更改效果
    @FXML
    private void initialize() {
        List<String> fontFamilies = Font.getFamilies();
        font_choice.getItems().addAll(fontFamilies);
        size_choice.valueProperty().addListener((observable, oldValue, newValue) -> {
            size_label.setText(String.valueOf(newValue.intValue()) + "px");
            size = newValue.intValue();
            updateFont();
        });
        font_choice.valueProperty().addListener((observable, oldValue, newValue) -> {
            font = newValue.toString();
            updateFont();
        });
        font_choice.setValue("宋体");
        size_choice.setValue(20);
    }

    // 更新测试字体和大小
    private void updateFont() {
        text_area.setFont(Font.font(font, size));
        text_area.setText("这是字体的测试内容\nThis is a test content of the font");
    }

    // 父窗口调用，设置父控制器
    public void set_parent(finalController controller) {
        this.controller = controller;
    }

    // 确认按钮点击事件，将字体和大小传给父窗口，关闭窗口
    @FXML
    private void onAckButtonClicked() {
        Stage stage = (Stage) root_pane.getScene().getWindow();
        controller.set_text_font(font, size);
        stage.close();
    }
}
