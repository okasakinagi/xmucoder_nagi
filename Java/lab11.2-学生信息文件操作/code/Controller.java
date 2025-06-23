package com.lab112;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Scanner;

public class Controller {
    @FXML
    private VBox rootpane;
    @FXML
    private Label resultlabel;
    @FXML
    private Label countlabel;
    @FXML
    private TextField sidtext;
    @FXML
    private TextField snametext;
    @FXML
    private TextField sphonetext;
    @FXML
    private TextField semailtext;
    @FXML
    private TextArea sothertext;
    @FXML
    private TextField squerytext;
    @FXML
    private Button savebutton;
    @FXML
    private Button querybutton;
    @FXML
    private Button deletebutton;
    @FXML
    private Button lastbutton;
    @FXML
    private Button nextbutton;
    @FXML
    private ImageView simage;

    final private String filename = "data/save.txt";
    private ArrayList<String> cur_data = new ArrayList<>();
    private int cur_index = 0;
    private String destDir = "data/picture";
    private Path temp_imagedir;

    public void initialize() {
        Image image = new Image("file:data/init.jpg");
        simage.setImage(image);
    }

    @FXML
    private void imageonmousepress() {
        resultlabel.setText("选择图片");
        Stage stage = (Stage) rootpane.getScene().getWindow();
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("选择图片文件");

        // 设置文件选择过滤器，只允许选择 JPEG 或 PNG 图片
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("JPG 图片", "*.jpg"));

        // 显示文件选择对话框
        File selectedFile = fileChooser.showOpenDialog(stage);
        temp_imagedir = selectedFile.toPath();

        if (selectedFile != null) {
            // 加载选择的图片
            Image image = new Image(selectedFile.toURI().toString());
            simage.setImage(image);
        }
    }

    private void showdata() {
        if (cur_index < cur_data.size()) {
            String[] temp = cur_data.get(cur_index).split(" ");
            sidtext.setText(temp[0]);
            snametext.setText(temp[1]);
            sphonetext.setText(temp[2]);
            semailtext.setText(temp[3]);
            sothertext.setText(temp[4]);
            countlabel.setText("当前：" + (cur_index + 1) + "/" + cur_data.size());
            File imagefile = new File("data/picture/" + sidtext.getText() + ".jpg");
            if (imagefile.exists()) {
                Image image = new Image("file:data/picture/" + sidtext.getText() + ".jpg");
                simage.setImage(image);
            } else {
                Image image = new Image("file:data/init.jpg");
                simage.setImage(image);
            }
        }
        if (cur_data.size() == 0) {
            sidtext.setText("");
            snametext.setText("");
            sphonetext.setText("");
            semailtext.setText("");
            sothertext.setText("");
            Image image = new Image("file:data/init.jpg");
            simage.setImage(image);
            countlabel.setText("当前：0/0");
        }
        if (cur_index == 0)
            lastbutton.setDisable(true);
        else
            lastbutton.setDisable(false);

        if (cur_index == cur_data.size() - 1 || cur_data.size() == 0)
            nextbutton.setDisable(true);
        else
            nextbutton.setDisable(false);
    }

    @FXML
    private void savebuttononaction() {
        try {
            if (sothertext.getText().isEmpty()) {
                sothertext.setText("无");
            }
            if (sidtext.getText().isEmpty() || snametext.getText().isEmpty() || sphonetext.getText().isEmpty()
                    || semailtext.getText().isEmpty()) {
                resultlabel.setText("请输入完整信息");
                return;
            }
            String target = new String(sidtext.getText() + ' ' + snametext.getText() + ' ' + sphonetext.getText() + ' '
                    + semailtext.getText() + ' ' + sothertext.getText());
            if (cur_data.size()!=0 && sidtext.getText().equals(cur_data.get(cur_index).split(" ")[0])) {
                Scanner filein = new Scanner(new File(filename));
                ArrayList<String> temp = new ArrayList<>();
                while (filein.hasNextLine()) {
                    String temp1 = filein.nextLine();
                    if (!temp1.equals(cur_data.get(cur_index))) {
                        temp.add(temp1);
                    } else {
                        temp.add(target);
                    }
                }
                PrintWriter fileout = new PrintWriter(new FileWriter(filename, false));
                fileout.println(temp.get(0));
                fileout.close();
                fileout = new PrintWriter(new FileWriter(filename, true));
                for (int i = 1; i < temp.size(); i++) {
                    fileout.println(temp.get(i));
                }
                fileout.close();
                filein.close();

                resultlabel.setText("修改成功");
            } else {
                PrintWriter fileout = new PrintWriter(new FileWriter(filename, true));
                System.out.println(target);
                fileout.println(target);
                fileout.close();
                cur_data.add(target);
                if(cur_index!=0)
                    cur_index++;
                resultlabel.setText("保存成功");
            }
            if (temp_imagedir!=null && !temp_imagedir.toString().isEmpty()) {
                Path targetDir = Paths.get(destDir + "/" + sidtext.getText() + ".jpg");
                Files.copy(temp_imagedir, targetDir, StandardCopyOption.REPLACE_EXISTING);
            }
        } catch (Exception e) {
            resultlabel.setText("保存失败");
            e.printStackTrace();
        }
    }

    @FXML
    private void querybuttononaction() {
        try {
            Scanner filein = new Scanner(new File(filename));
            resultlabel.setText("查询成功");
            cur_data.clear();
            cur_index = 0;
            while (filein.hasNextLine()) {
                String temp = filein.nextLine();
                if (temp.contains(squerytext.getText()) || squerytext.getText().isEmpty()) {
                    cur_data.add(temp);
                }
            }
            showdata();
            filein.close();
        } catch (FileNotFoundException e) {
            resultlabel.setText("查询失败");
            e.printStackTrace();
        }
    }

    @FXML
    private void deletebuttononaction() {
        try {
            Scanner filein = new Scanner(new File(filename));
            ArrayList<String> temp = new ArrayList<>();
            while (filein.hasNextLine()) {
                String temp1 = filein.nextLine();
                if (!temp1.equals(cur_data.get(cur_index))) {
                    temp.add(temp1);
                }
            }
            PrintWriter fileout = new PrintWriter(new FileWriter(filename, false));
            fileout.println(temp.get(0));
            fileout.close();
            fileout = new PrintWriter(new FileWriter(filename, true));
            for (int i = 1; i < temp.size(); i++) {
                fileout.println(temp.get(i));
            }
            fileout.close();
            filein.close();
            File imagefile = new File(destDir + "/" + sidtext.getText() + ".jpg");
            if(imagefile.exists())
                imagefile.delete();
            querybuttononaction();
            resultlabel.setText("删除成功");

        } catch (Exception e) {
            resultlabel.setText("删除失败");
            e.printStackTrace();
        }
    }

    @FXML
    private void nextbuttononaction() {
        cur_index++;
        showdata();
    }

    @FXML
    private void lastbuttononaction() {
        cur_index--;
        showdata();
    }
}