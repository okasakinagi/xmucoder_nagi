package com.finallab;

import java.util.ArrayList;

import javafx.fxml.FXML;
import javafx.scene.control.*;

public class SearchViewController {
    @FXML
    private TextField searchField;
    @FXML
    private TextField replaceField;
    @FXML
    private Button search_next_Button;
    @FXML
    private Button search_prev_Button;
    @FXML
    private Button replace_one_Button;
    @FXML
    private Button replace_all_Button;
    @FXML
    private CheckBox cycle;
    @FXML
    private CheckBox case_sensitive;
    @FXML
    private Label result_label;

    private finalController parentController;// 引用父窗口控制器
    private TextArea textarea;// 用于引用父窗口文本域
    private String text = "";// 用于临时存储文本域内容，单次判断文本变化
    private String cur_search_text = "";// 用于临时存储搜索框内容，单次判断文本变化
    private ArrayList<Integer> searched_idx = new ArrayList<>();// 用于存储搜索结果
    private int search_count = 0;// 用于记录当前搜索记录索引
    private boolean isReplace = false;// 用于记录是否处于替换状态，用于判断重新搜索是否更新索引
    protected boolean is_cycle = true;// 查找循环标记
    protected boolean is_case_sensitive = true;// 查找大小写敏感标记

    public void initialize() {
        cycle.setSelected(true);
        case_sensitive.setSelected(true);
    }

    // 父窗口调用，获取父窗口文本域
    public void gettext(TextArea text) {
        this.textarea = text;
    }

    // 父窗口调用，获取父窗口控制器
    public void set_parent(finalController parentController) {
        this.parentController = parentController;
    }

    // 回调函数，用于在父窗口文本域中高亮显示搜索结果
    private void callback_search() {
        parentController.select_text(searched_idx.get(search_count),
                searched_idx.get(search_count) + cur_search_text.length());
    }

    // 回调函数，用于在父窗口文本域中替换搜索结果
    private void callback_replace() {
        parentController.replace_text(searched_idx.get(search_count),
                searched_idx.get(search_count) + cur_search_text.length(), replaceField.getText());
    }

    // 判断函数，用于增加带有大小写敏感的判断
    private boolean is_equal_with_sensitive() {
        if (is_case_sensitive) {
            return (!cur_search_text.equals(searchField.getText())) || (!text.equals(textarea.getText()));
        } else {
            return (!cur_search_text.equals(searchField.getText().toLowerCase()))
                    || (!text.equals(textarea.getText().toLowerCase()));
        }
    }

    // 搜索函数，用于在文本域中搜索指定内容
    private void search() {
        int index = 0;
        text = textarea.getText();
        cur_search_text = searchField.getText();
        if (!is_case_sensitive) {
            text = text.toLowerCase();
            cur_search_text = cur_search_text.toLowerCase();
        }
        searched_idx.clear();
        index = text.indexOf(cur_search_text, index);
        while (index != -1 && index < text.length()) {
            searched_idx.add(index);
            index = text.indexOf(cur_search_text, index + 1);
        }
    }

    @FXML
    public void searchNext() {
        if (is_equal_with_sensitive()) {// 判断搜索文本和文本内容是否变化
            search();
            if (!isReplace) {// 判断是否处于替换状态，替换状态不更新索引，仅此处增加此内容，用于替换处的复用
                search_count = 0;
            }
        } else {
            search_count++;
        }
        if (searched_idx.size() != 0) {
            if (search_count >= searched_idx.size()) {
                if (is_cycle) {
                    search_count = 0;
                } else {
                    search_count = searched_idx.size() - 1;
                }
            }
            if (search_count == searched_idx.size() - 1) {
                result_label.setText("已查询至最后一项，查询结果：" + (search_count + 1) + "/" + searched_idx.size());
            } else {
                result_label.setText("查询结果：" + (search_count + 1) + "/" + searched_idx.size());
            }

            callback_search();

        } else {
            result_label.setText("未找到匹配项");
        }
    }

    @FXML
    public void searchPrev() {
        if (is_equal_with_sensitive()) {
            search();
            search_count = searched_idx.size() - 1;
        } else {
            search_count--;
        }
        if (searched_idx.size() != 0) {

            if (search_count < 0) {
                if (is_cycle) {
                    search_count = searched_idx.size() - 1;
                } else {
                    search_count = 0;
                }
            }
            if (search_count == 0) {
                result_label.setText("已查询至第一项，查询结果：" + (search_count + 1) + "/" + searched_idx.size());
            } else {
                result_label.setText("查询结果：" + (search_count + 1) + "/" + searched_idx.size());
            }
            callback_search();
        } else {
            result_label.setText("未找到匹配项");
        }
    }

    @FXML
    public void replaceOne() {
        if (searched_idx.size() != 0) {
            callback_replace();
            isReplace = true;
            searchNext();
            isReplace = false;
            result_label.setText("已替换一处，当前查询结果：" + (search_count + 1) + "/" + searched_idx.size());
        } else {
            searchNext();
            if (searched_idx.size() != 0) {
                replaceOne();
            } else {
                result_label.setText("未找到匹配项,无法替换");
            }
        }
    }

    @FXML
    public void replaceAll() {
        if (searched_idx.size() != 0) {
            for (search_count = 0; search_count < searched_idx.size(); search_count++) {
                callback_replace();
            }
            isReplace = true;
            searchNext();
            isReplace = false;
            result_label.setText("已替换全部");
        } else {
            searchNext();
            if (searched_idx.size() != 0) {
                replaceAll();
            } else {
                result_label.setText("未找到匹配项,无法替换");
            }
        }
    }

    @FXML
    public void cycle_onaction() {
        is_cycle = !is_cycle;
    }

    @FXML
    public void case_sensitive_onaction() {
        is_case_sensitive = !is_case_sensitive;
    }
}
