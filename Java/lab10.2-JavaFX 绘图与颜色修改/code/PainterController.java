package com.lab102;

// Fig. 26.6: PainterController.java
// Controller for the Painter app
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;

public class PainterController {
   // enum representing pen sizes
   private enum PenSize {
      SMALL(2),
      MEDIUM(4),
      LARGE(6);

      private final int radius;

      PenSize(int radius) {
         this.radius = radius;
      }

      public int getRadius() {
         return radius;
      }
   };

   // instance variables that refer to GUI components
   @FXML
   private RadioButton blackRadioButton;
   @FXML
   private RadioButton redRadioButton;
   @FXML
   private RadioButton greenRadioButton;
   @FXML
   private RadioButton blueRadioButton;
   @FXML
   private RadioButton smallRadioButton;
   @FXML
   private RadioButton mediumRadioButton;
   @FXML
   private RadioButton largeRadioButton;
   @FXML
   private RadioButton penRadioButton;
   @FXML
   private RadioButton rectangleRadioButton;
   @FXML
   private RadioButton circleRadioButton;
   @FXML
   private RadioButton lineRadioButton;
   @FXML
   private AnchorPane drawingAreaAnchorPane;
   @FXML
   private ToggleGroup colorToggleGroup;
   @FXML
   private ToggleGroup sizeToggleGroup;
   @FXML
   private ToggleGroup shapeToggleGroup;

   // instance variables for managing Painter state
   private PenSize radius = PenSize.MEDIUM; // radius of circle
   private Paint brushColor = Color.BLACK; // drawing color
   private int kind = 0;// 0-pen;1-rectangle;2-circle;3-line
   private double startx, starty, endx, endy;

   // set user data for the RadioButtons
   public void initialize() {
      // user data on a control can be any Object
      blackRadioButton.setUserData(Color.BLACK);
      redRadioButton.setUserData(Color.RED);
      greenRadioButton.setUserData(Color.GREEN);
      blueRadioButton.setUserData(Color.BLUE);
      smallRadioButton.setUserData(PenSize.SMALL);
      mediumRadioButton.setUserData(PenSize.MEDIUM);
      largeRadioButton.setUserData(PenSize.LARGE);
      penRadioButton.setUserData((int) 0);
      rectangleRadioButton.setUserData((int) 1);
      circleRadioButton.setUserData((int) 2);
      lineRadioButton.setUserData((int) 3);
   }

   // handles drawingArea's onMouseDragged MouseEvent
   @FXML
   private void MouseDragged(MouseEvent e) {
      if (kind == 0)
         drawing(e);
//      System.out.println("MouseDragged");
   }

   @FXML
   private void MousePressed(MouseEvent e) {
      startx = e.getX();
      starty = e.getY();
//      System.out.println("MousePressed");
   }

   @FXML
   private void MouseReleased(MouseEvent e) {
      endx = e.getX();
      endy = e.getY();
//      System.out.println("MouseReleased");
      if (kind != 0)
         drawing(e);
   }

   private void drawing(MouseEvent e) {
      switch (kind) {
         case 0:
            Circle newCircle1 = new Circle(e.getX(), e.getY(),
                  radius.getRadius(), brushColor);
            drawingAreaAnchorPane.getChildren().add(newCircle1);
            break;

         case 1:
            if (endx < startx) { // swap points if end is left of start
               double temp = startx;
               startx = endx;
               endx = temp;
               }
            if (endy < starty) { // swap points if end is above start
               double temp = starty;
               starty = endy;
               endy = temp;
               }
            Rectangle newRectangle = new Rectangle(startx, starty, endx - startx, endy - starty);
            newRectangle.setFill(brushColor);
            drawingAreaAnchorPane.getChildren().add(newRectangle);
            break;

         case 2:
            double x = (startx + endx) / 2, y = (starty + endy) / 2,
                  r = Math.sqrt((startx - endx) * (startx - endx) + (starty - endy) * (starty - endy)) / 2;
            Circle newCircle2 = new Circle(x, y, r, brushColor);
            drawingAreaAnchorPane.getChildren().add(newCircle2);
            break;

         case 3:
            Line newLine = new Line(startx, starty, endx, endy);
            newLine.setStroke(brushColor);
            newLine.setStrokeWidth(radius.getRadius());
            drawingAreaAnchorPane.getChildren().add(newLine);
            break;
      }
   }

   // handles color RadioButton's ActionEvents
   @FXML
   private void colorRadioButtonSelected(ActionEvent e) {
      // user data for each color RadioButton is the corresponding Color
      brushColor = (Color) colorToggleGroup.getSelectedToggle().getUserData();
   }

   // handles size RadioButton's ActionEvents
   @FXML
   private void sizeRadioButtonSelected(ActionEvent e) {
      // user data for each size RadioButton is the corresponding PenSize
      radius = (PenSize) sizeToggleGroup.getSelectedToggle().getUserData();
   }

   @FXML
   private void shapeRadioButtonSelected(ActionEvent e) {
      // user data for each size RadioButton is the corresponding PenSize
      kind = (int) shapeToggleGroup.getSelectedToggle().getUserData();
   }

   // handles Undo Button's ActionEvents
   @FXML
   private void undoButtonPressed(ActionEvent event) {
      int count = drawingAreaAnchorPane.getChildren().size();

      // if there are any shapes remove the last one added
      if (count > 0)
         drawingAreaAnchorPane.getChildren().remove(count - 1);
   }

   // handles Clear Button's ActionEvents
   @FXML
   private void clearButtonPressed(ActionEvent event) {
      drawingAreaAnchorPane.getChildren().clear(); // clear the canvas
   }
}

/**************************************************************************
 * (C) Copyright 1992-2018 by Deitel & Associates, Inc. and *
 * Pearson Education, Inc. All Rights Reserved. *
 * *
 * DISCLAIMER: The authors and publisher of this book have used their *
 * best efforts in preparing the book. These efforts include the *
 * development, research, and testing of the theories and programs *
 * to determine their effectiveness. The authors and publisher make *
 * no warranty of any kind, expressed or implied, with regard to these *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or *
 * consequential damages in connection with, or arising out of, the *
 * furnishing, performance, or use of these programs. *
 *************************************************************************/
