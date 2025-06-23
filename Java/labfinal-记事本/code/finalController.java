package com.finallab;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class finalController {
    @FXML
    private GridPane root_pane;
    @FXML
    private Label label_place;
    @FXML
    private Label label_count;
    @FXML
    private TextArea Text;
    @FXML
    private MenuItem new_file;
    @FXML
    private MenuItem open_file;
    @FXML
    private MenuItem save_file;
    @FXML
    private MenuItem save_file_as;
    @FXML
    private MenuItem undo;
    @FXML
    private MenuItem redo;
    @FXML
    private MenuItem cut;
    @FXML
    private MenuItem copy;
    @FXML
    private MenuItem paste;
    @FXML
    private MenuItem word_type;
    @FXML
    private MenuItem search;
    @FXML
    private MenuItem auto_enter;
    @FXML
    private MenuItem about;

    private Stage searchstage;// 搜索窗口存储，用于控制仅会打开一个搜索窗口
    private Path save_path;
    protected boolean is_change = false;// 文件是否有更改标记
    protected boolean is_cover = false;// 确认窗口返回的覆盖标记
    protected boolean can_close = false;// 确认窗口返回的可以关闭标记
    protected boolean is_save_as = false;// 确认窗口返回的是否另存为标记（关闭窗口询问保存时标记是否保存）
    protected boolean is_auto_enter = false;// 自动换行标记

    public void initialize() {
        set_label_place();// 初始化时设置光标位置和字符数
        Text.caretPositionProperty().addListener((observable, oldValue, newValue) -> {
            set_label_place();
        });// 监听光标位置变化，实时更新位置和字符数
        Text.textProperty().addListener((observable, oldValue, newValue) -> {
            is_change = true;
            set_label_place();
        });// 监听文本变化，实时更新文件更改标记
    }

    private void set_label_place() {
        int offset = Text.getCaretPosition();
        String text = Text.getText();

        int row = 0, col = 0, lastlinestart = 0;
        for (int i = 0; i < offset || i < text.length();) {
            lastlinestart = text.indexOf('\n', i);
            if (lastlinestart != -1) {
                if (offset >= lastlinestart + 1) {
                    row++;
                    col = offset - lastlinestart - 1;
                }
                i = lastlinestart + 1;
            } else {
                break;
            }
        } // 计算光标所在位置
        if (row == 0)
            col = offset;
        label_place.setText(String.format("行%d，列%d", row + 1, col + 1));
        label_count.setText(String.format("%d个字符", Text.getText().length()));
    }

    // 子窗口调用，用于设置字体
    public void set_text_font(String font, int size) {
        Text.setFont(Font.font(font, size));
        Text.positionCaret(0);
    }

    @FXML
    private void word_type_onaction() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(finalApplication.class.getResource("font-view.fxml"));
            Scene scene = new Scene(fxmlLoader.load(), 400, 200);
            Stage stage = new Stage();
            stage.setTitle("字体设置");
            stage.setScene(scene);
            Image icon = new Image("file:relatedata/icons.png");
            stage.getIcons().add(icon);
            FontViewController controller = fxmlLoader.getController();
            controller.set_parent(this);
            stage.initModality(Modality.WINDOW_MODAL);
            stage.initOwner((Stage) root_pane.getScene().getWindow());
            stage.showAndWait();
        } catch (Exception e) {
            e.printStackTrace();
        } // 字体设置窗口，点击字体按钮时展开，同时在子窗口未关闭时，父窗口无法更改
    }

    // 子窗口调用，用于选择查找到的内容
    public void select_text(int start, int end) {
        Text.deselect();
        Text.selectRange(start, end);
    }

    // 子窗口调用，用于替换查找到的内容
    public void replace_text(int start, int end, String text) {
        Text.replaceText(start, end, text);
    }

    @FXML
    private void search_onaction() {
        try {
            if (searchstage != null && searchstage.isShowing()) {
                if (searchstage.isIconified()) {
                    searchstage.setIconified(false);
                }
                searchstage.toFront();
                searchstage.requestFocus();
            } else {
                FXMLLoader fxmlLoader = new FXMLLoader(finalApplication.class.getResource("search-view.fxml"));
                Scene scene = new Scene(fxmlLoader.load(), 300, 200);
                searchstage = new Stage();
                searchstage.setTitle("查找和替换");
                searchstage.setScene(scene);
                Image icon = new Image("file:relatedata/icons.png");
                searchstage.getIcons().add(icon);
                SearchViewController controller = fxmlLoader.getController();
                controller.set_parent(this);
                controller.gettext(Text);
                searchstage.show();
            }
        } catch (Exception e) {
            e.printStackTrace();
        } // 查找和替换窗口，点击查找按钮时展开，同时在子窗口不会重复打开，在重复点击时会将窗口置于最前
    }

    @FXML
    private void new_file_onaction() {
        if (is_change) {
            open_ack_window(true);// 新建文件前如果有更改询问是否保存
            if (is_save_as) {// 如果用户选择另存为，则另存为
                save_file_onaction();
            }
        }
        Text.setText("");
        is_change = false;
        save_path = null;
    }

    // 自动换行
    @FXML
    private void auto_enter_onaction() {
        if (is_auto_enter) {
            auto_enter.setText("自动换行");
            Text.setWrapText(false);
            is_auto_enter = false;
        } else {
            auto_enter.setText("取消自动换行");
            Text.setWrapText(true);
            is_auto_enter = true;
        }
    }

    // 打开文件
    @FXML
    private void open_file_onaction() {
        if (is_change) {
            open_ack_window(true);// 打开文件前如果有更改询问是否保存
            if (is_save_as) {// 如果用户选择另存为，则另存为
                save_file_onaction();
            }
        }
        Stage stage = (Stage) root_pane.getScene().getWindow();
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("打开文件");

        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("TXT文件", "*.txt"),
                new FileChooser.ExtensionFilter("所有文件", "*.*"));

        File selectedFile = fileChooser.showOpenDialog(stage);

        if (selectedFile != null) {
            save_path = selectedFile.toPath();
            try {
                String content = Files.readString(save_path);
                Text.setText(content);
                Text.positionCaret(0);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    // 保存文件
    @FXML
    private void save_file_onaction() {
        if (save_path == null) {
            save_file_as_onaction();// 如果没有保存过，则另存为
        } else {
            try {
                Files.writeString(save_path, Text.getText());
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    // 另存为文件
    @FXML
    private void save_file_as_onaction() {
        Stage stage = (Stage) root_pane.getScene().getWindow();
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("另存为文件");
        fileChooser.setInitialFileName("新建文本文档.txt");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("TXT文件", "*.txt"),
                new FileChooser.ExtensionFilter("所有文件", "*.*"));// 设置文件后缀名选择

        File selectedFile = fileChooser.showSaveDialog(stage);// 获取用户选择保存的文件对象

        if (selectedFile != null) {
            FileChooser.ExtensionFilter selectedFilter = fileChooser.getSelectedExtensionFilter();// 获取用户选择的文件类型过滤器

            String fileName = selectedFile.getName();
            if (selectedFilter != null && selectedFilter.getExtensions().contains("*.*")) {
                // 用户选择了“所有文件”，不进行扩展名检查
            } else if (!fileName.contains(".")) {
                // 用户未输入扩展名，根据所选文件类型补全
                String extension = selectedFilter.getExtensions().get(0).substring(2); // 提取扩展名（如 .txt → txt）
                selectedFile = new File(selectedFile.getParentFile(), fileName + "." + extension);
            }

            save_path = selectedFile.toPath();
            try {
                Files.writeString(save_path, Text.getText());
            } catch (Exception e) {
                e.printStackTrace();
            }

            // 根据测试，发现windows给的保存api已经包含覆盖处理，故不在重复处理
            // if (!Files.exists(save_path)) {// 如果文件不存在，则创建新文件
            // try {
            // Files.writeString(save_path, Text.getText());
            // } catch (Exception e) {
            // e.printStackTrace();
            // }
            // } else {// 如果文件已存在，则询问用户是否覆盖
            // open_ack_window(false);
            // if (is_cover) {// 如果用户选择覆盖，则直接覆盖
            // is_cover = false;
            // try {
            // Files.writeString(save_path, Text.getText());
            // } catch (Exception e) {
            // e.printStackTrace();
            // }
            // } else if (is_save_as) {// 如果用户选择另存为，则另存为
            // is_save_as = false;
            // save_file_as_onaction();
            // }
            // }
        }
    }

    protected Boolean close_onaction() {// 关闭时调用
        if (is_change) {// 如果内容已更改，则询问用户是否保存
            open_ack_window(true);
            if (is_save_as) {// 如果用户选择另存为，则另存为
                save_file_onaction();
            }
            return can_close;// 返回是否可以关闭

        } else {
            return true;// 如果内容未更改，则直接关闭
        }
    }

    protected void open_ack_window(Boolean is_first_save) {// 打开确认窗口
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(finalApplication.class.getResource("save-ack-view.fxml"));
            Scene scene = new Scene(fxmlLoader.load(), 300, 150);
            Stage stage = new Stage();
            if (is_first_save) {
                stage.setTitle("内容尚未保存");
            } else {
                stage.setTitle("文件已存在");
            }
            stage.setScene(scene);
            Image icon = new Image("file:relatedata/icons.png");
            stage.getIcons().add(icon);
            SaveAckViewController controller = fxmlLoader.getController();
            controller.set_flag_controller(is_first_save, this);
            controller.change_sence();
            stage.initModality(Modality.WINDOW_MODAL);
            stage.initOwner((Stage) root_pane.getScene().getWindow());
            stage.setOnCloseRequest(event -> {
                event.consume();
                can_close = false;
                is_cover = false;
                is_save_as = false;
                stage.close();
            });// 窗口关闭时，将标志位重置，不做任何操作
            stage.showAndWait();
        } catch (Exception e) {
            can_close = false;// 如果出现异常，也重置标志位，不做任何操作
            is_cover = false;
            is_save_as = false;
            e.printStackTrace();
        }
    }

    @FXML
    private void cut_onaction() {// 剪切
        Text.cut();
    }

    @FXML
    private void copy_onaction() {// 复制
        Text.copy();
    }

    @FXML
    private void paste_onaction() {// 粘贴
        Text.paste();
    }

    @FXML
    private void select_all_onaction() {// 全选
        Text.selectAll();
    }

    @FXML
    private void undo_onaction() {// 撤销
        Text.undo();
    }

    @FXML
    private void redo_onaction() {// 重做
        Text.redo();
    }

    @FXML
    private void about_onaction() {// 关于
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(finalApplication.class.getResource("help-view.fxml"));
            Scene scene = new Scene(fxmlLoader.load(), 300, 150);
            Stage stage = new Stage();
            stage.setTitle("关于");
            stage.setScene(scene);
            Image icon = new Image("file:relatedata/icons.png");
            stage.getIcons().add(icon);
            stage.initModality(Modality.WINDOW_MODAL);
            stage.initOwner((Stage) root_pane.getScene().getWindow());
            stage.showAndWait();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}