
// Fig. 24.13: TicTacToeServer.java
// This class maintains a game of Tic-Tac-Toe for two clients.
import java.awt.BorderLayout;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.io.IOException;
import java.util.Formatter;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;

public class TicTacToeServer extends JFrame {
   private String[] board = new String[9]; // tic-tac-toe board
   private JTextArea outputArea; // for outputting moves
   private Player[] players; // array of Players
   private ServerSocket server; // server socket to connect with clients
   private int currentPlayer; // keeps track of player with current move
   private final static int PLAYER_X = 0; // constant for first player
   private final static int PLAYER_O = 1; // constant for second player
   private final static String[] MARKS = { "X", "O" }; // array of marks
   private ExecutorService runGame; // will run players
   private Lock gameLock; // to lock game for synchronization
   private Condition otherPlayerConnected; // to wait for other player
   private Condition otherPlayerTurn; // to wait for other player's turn

   // set up tic-tac-toe server and GUI that displays messages
   public TicTacToeServer() {
      super("Tic-Tac-Toe Server"); // set title of window

      // create ExecutorService with a thread for each player
      runGame = Executors.newFixedThreadPool(2);
      gameLock = new ReentrantLock(); // create lock for game

      // condition variable for both players being connected
      otherPlayerConnected = gameLock.newCondition();

      // condition variable for the other player's turn
      otherPlayerTurn = gameLock.newCondition();

      for (int i = 0; i < 9; i++)
         board[i] = new String(""); // create tic-tac-toe board
      players = new Player[2]; // create array of players
      currentPlayer = PLAYER_X; // set current player to first player

      try {
         server = new ServerSocket(12345, 2); // set up ServerSocket
      } // end try
      catch (IOException ioException) {
         ioException.printStackTrace();
         System.exit(1);
      } // end catch

      outputArea = new JTextArea(); // create JTextArea for output
      add(outputArea, BorderLayout.CENTER);
      outputArea.setText("Server awaiting connections\n");

      setSize(300, 300); // set size of window
      setVisible(true); // show window
   } // end TicTacToeServer constructor

   // wait for two connections so game can be played
   public void execute() {
      // wait for each client to connect
      for (int i = 0; i < players.length; i++) {
         try // wait for connection, create Player, start runnable
         {
            players[i] = new Player(server.accept(), i);
            runGame.execute(players[i]); // execute player runnable
         } // end try
         catch (IOException ioException) {
            ioException.printStackTrace();
            System.exit(1);
         } // end catch
      } // end for

      gameLock.lock(); // lock game to signal player X's thread

      try {
         players[PLAYER_X].setSuspended(false); // resume player X
         otherPlayerConnected.signal(); // wake up player X's thread
      } // end try
      finally {
         gameLock.unlock(); // unlock game after signalling player X
      } // end finally
   } // end method execute

   // display message in outputArea
   private void displayMessage(final String messageToDisplay) {
      // display message from event-dispatch thread of execution
      SwingUtilities.invokeLater(
            new Runnable() {
               public void run() // updates outputArea
               {
                  outputArea.append(messageToDisplay); // add message
               } // end method run
            } // end inner class
      ); // end call to SwingUtilities.invokeLater
   } // end method displayMessage

   // determine if move is valid
   public boolean validateAndMove(int location, int player) {
      // while not current player, must wait for turn
      while (player != currentPlayer) {
         gameLock.lock(); // lock game to wait for other player to go

         try {
            otherPlayerTurn.await(); // wait for player's turn
         } // end try
         catch (InterruptedException exception) {
            exception.printStackTrace();
         } // end catch
         finally {
            gameLock.unlock(); // unlock game after waiting
         } // end finally
      } // end while

      // if location not occupied, make move
      if (!isOccupied(location)) {
         board[location] = MARKS[currentPlayer]; // set move on board
         currentPlayer = (currentPlayer + 1) % 2; // change player

         // let new current player know that move occurred
         players[currentPlayer].otherPlayerMoved(location);

         gameLock.lock(); // lock game to signal other player to go

         try {
            otherPlayerTurn.signal(); // signal other player to continue
         } // end try
         finally {
            gameLock.unlock(); // unlock game after signaling
         } // end finally

         return true; // notify player that move was valid
      } // end if
      else // move was not valid
         return false; // notify player that move was invalid
   } // end method validateAndMove

   // determine whether location is occupied
   public boolean isOccupied(int location) {
      if (board[location].equals(MARKS[PLAYER_X]) ||
            board[location].equals(MARKS[PLAYER_O]))
         return true; // location is occupied
      else
         return false; // location is not occupied
   } // end method isOccupied

   private void store_to_mysql(String WINNER, String LOSER) {
      try {
         Class.forName("com.mysql.cj.jdbc.Driver");
      } catch (ClassNotFoundException e) {
         System.out.println("MySQL JDBC 驱动未找到");
         e.printStackTrace();
      }

      String url = "jdbc:mysql://localhost:3306/java?useSSL=false&serverTimezone=UTC";
      String username = "tanjiheng";
      String password = "";

      try {
         Connection connection = DriverManager.getConnection(url, username, password);
         System.out.println("数据库连接成功！");
         Statement statement = connection.createStatement();
         String insertSQL = String.format("INSERT INTO JAVA_GAME (WINNER_USER, LOSER_USER) VALUES (\'%s \',\'%s\');",
               WINNER, LOSER);
         statement.executeUpdate(insertSQL);
         connection.close();
      } catch (SQLException e) {
         System.out.println("数据库连接失败");
         e.printStackTrace();
      }

      return;
   }

   private void displayResult(String result) {
      String WINNER = "", LOSER = "";
      for (int i = 0; i < players.length; i++) {
         if (players[i].mark.equals(result)) {
            players[i].output.format("You win\n");
            players[i].output.format("Connection closed");
            WINNER = players[i].mark;
            players[i].output.flush();
         } else {
            players[i].output.format("You lose\n");
            players[i].output.format("Connection closed");
            LOSER = players[i].mark;
            players[i].output.flush();
         }
      }
      store_to_mysql(WINNER, LOSER);
   }

   // place code in this method to determine whether game over
   public boolean isGameOver() {
      if (board[0].equals(board[1]) && board[1].equals(board[2]) && !board[0].equals("")) {
         displayResult(board[0]);
         return true;
      } else if (board[3].equals(board[4]) && board[4].equals(board[5]) && !board[3].equals("")) {
         displayResult(board[3]);
         return true;
      } else if (board[6].equals(board[7]) && board[7].equals(board[8]) && !board[6].equals("")) {
         displayResult(board[6]);
         return true;
      } else if (board[0].equals(board[3]) && board[3].equals(board[6]) && !board[0].equals("")) {
         displayResult(board[0]);
         return true;
      } else if (board[1].equals(board[4]) && board[4].equals(board[7]) && !board[1].equals("")) {
         displayResult(board[1]);
         return true;
      } else if (board[2].equals(board[5]) && board[5].equals(board[8]) && !board[2].equals("")) {
         displayResult(board[2]);
         return true;
      } else if (board[0].equals(board[4]) && board[4].equals(board[8]) && !board[0].equals("")) {
         displayResult(board[0]);
         return true;
      } else if (board[2].equals(board[4]) && board[4].equals(board[6]) && !board[2].equals("")) {
         displayResult(board[2]);
         return true;
      } else {
         return false;
      }
   } // end method isGameOver

   // private inner class Player manages each Player as a runnable
   private class Player implements Runnable {
      private Socket connection; // connection to client
      private Scanner input; // input from client
      private Formatter output; // output to client
      private int playerNumber; // tracks which player this is
      private String mark; // mark for this player
      private boolean suspended = true; // whether thread is suspended

      // set up Player thread
      public Player(Socket socket, int number) {
         playerNumber = number; // store this player's number
         mark = MARKS[playerNumber]; // specify player's mark
         connection = socket; // store socket for client

         try // obtain streams from Socket
         {
            input = new Scanner(connection.getInputStream());
            output = new Formatter(connection.getOutputStream());
         } // end try
         catch (IOException ioException) {
            ioException.printStackTrace();
            System.exit(1);
         } // end catch
      } // end Player constructor

      // send message that other player moved
      public void otherPlayerMoved(int location) {
         output.format("Opponent moved\n");
         output.format("%d\n", location); // send location of move
         output.flush(); // flush output
      } // end method otherPlayerMoved

      // control thread's execution
      public void run() {
         // send client its mark (X or O), process messages from client
         try {
            displayMessage("Player " + mark + " connected\n");
            output.format("%s\n", mark); // send player's mark
            output.flush(); // flush output

            // if player X, wait for another player to arrive
            if (playerNumber == PLAYER_X) {
               output.format("%s\n%s", "Player X connected",
                     "Waiting for another player\n");
               output.flush(); // flush output

               gameLock.lock(); // lock game to wait for second player

               try {
                  while (suspended) {
                     otherPlayerConnected.await(); // wait for player O
                  } // end while
               } // end try
               catch (InterruptedException exception) {
                  exception.printStackTrace();
               } // end catch
               finally {
                  gameLock.unlock(); // unlock game after second player
               } // end finally

               // send message that other player connected
               output.format("Other player connected. Your move.\n");
               output.flush(); // flush output
            } // end if
            else {
               output.format("Player O connected, please wait\n");
               output.flush(); // flush output
            } // end else

            // while game not over
            while (!isGameOver()) {
               int location = 0; // initialize move location

               if (input.hasNext())
                  location = input.nextInt(); // get move location

               // check for valid move
               if (validateAndMove(location, playerNumber)) {
                  displayMessage("\nlocation: " + location);
                  output.format("Valid move.\n"); // notify client
                  output.flush(); // flush output
               } // end if
               else // move was invalid
               {
                  output.format("Invalid move, try again\n");
                  output.flush(); // flush output
               } // end else
            } // end while
         } // end try
         finally {
            try {
               connection.close(); // close connection to client
            } // end try
            catch (IOException ioException) {
               ioException.printStackTrace();
               System.exit(1);
            } // end catch
         } // end finally
      } // end method run

      // set whether or not thread is suspended
      public void setSuspended(boolean status) {
         suspended = status; // set value of suspended
      } // end method setSuspended
   } // end class Player
} // end class TicTacToeServer

/**************************************************************************
 * (C) Copyright 1992-2005 by Deitel & Associates, Inc. and *
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
