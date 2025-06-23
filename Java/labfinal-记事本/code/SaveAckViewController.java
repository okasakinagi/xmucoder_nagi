package com.finallab;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class SaveAckViewController {
    @FXML
    private AnchorPane root_pane;
    @FXML
    private Label Text;
    @FXML
    private Button First;
    @FXML
    private Button Second;
    @FXML
    private Button Third;

    private Stage this_stage;// 窗口存储，用于控制关闭窗口
    private finalController controller;// 父控制器
    //后续测试此标志位无用，但保留
    private Boolean is_first_save;// 父窗口打开的标记，实现窗口复用，同时实现内容未保存确认和文件已存在确认

    private void initialize() {
    }

    public void set_flag_controller(Boolean is_first_save, finalController controller) {// 父窗口调用，设置标记和父控制器
        this.is_first_save = is_first_save;
        this.controller = controller;
    }

    @FXML
    public void change_sence() {// 父窗口调用，更改窗口内容，实现复用
        this_stage = (Stage) root_pane.getScene().getWindow();// 获取窗口
        if (is_first_save) {
            Text.setText("你的内容尚未保存，是否确认退出？");
            First.setText("保存");
            Second.setText("放弃");
            Third.setText("取消");
        } else {
            Text.setText("此文件已经存在，是否需要覆盖？");
            First.setText("覆盖");
            Second.setText("另存为");
            Third.setText("取消");
        }
    }

    @FXML
    public void First_onaction() {// 确认按钮点击事件，将标记传给父窗口，关闭窗口
        if (is_first_save) {
            controller.is_save_as = true;// 标记另存为
            controller.can_close = true;// 标记可以关闭
            controller.is_cover = false;// 排除其他标志干扰
            this_stage.close();
        } else {
            controller.is_cover = true;// 标记覆盖
            controller.can_close = false;// 排除其他标志干扰
            controller.is_save_as = false;// 排除其他标志干扰
            this_stage.close();
        }
    }

    @FXML
    public void Second_onaction() {// 确认按钮点击事件，将标记传给父窗口，关闭窗口
        if (is_first_save) {
            controller.can_close = true;// 标记放弃情况可以关闭
            controller.is_save_as = false;// 排除其他标志干扰
            controller.is_cover = false;// 排除其他标志干扰
            this_stage.close();
        } else {
            controller.is_save_as = true;// 标记另存为
            controller.can_close = false;// 排除其他标志干扰
            controller.is_cover = false;// 排除其他标志干扰
            this_stage.close();
        }
    }

    @FXML
    public void Third_onaction() {// 确认按钮点击事件，将标记传给父窗口，关闭窗口
        controller.can_close = false;// 标记取消情况不可以关闭
        controller.is_save_as = false;// 标记取消情况不是另存为
        controller.is_cover = false;// 标记取消情况不是覆盖
        this_stage.close();
    }
}
