import java.util.Random;
import java.util.Scanner;

class Player {
    int[] award;

    Player() {
        award = new int[6];
    }

    void get_award(int idx) {
        award[idx]++;
    }

    void being_snatched() {
        award[0] = 0;
    }
}

public class Main {
    public static void main(String[] args) {
        // 玩家初始化
        Scanner scanner = new Scanner(System.in);
        System.out.print("Please enter how many players you have(6-10):");
        int players = scanner.nextInt();
        Player[] Players = new Player[players];
        for (int i = 0; i < players; i++) {
            Players[i] = new Player();
        }
        // 奖品初始化
        int[] Award = { 0, 2, 4, 8, 16, 32 };// 状元奖项用0代表仍有，预防后续冲突
        // 开始掷骰子
        Random random_dice = new Random();
        int[] temp_dice = { 0, 0, 0, 0, 0, 0 };
        int sum = get_sum(Award);
        int round = 1;
        while (Award[0] == 0 || sum != 0) {
            System.out.printf("Round%d:", round);
            System.out.println();
            for (int i = 0; i < players; i++)// 玩家循环
            {
                for (int j = 0; j < 6; j++)// 掷骰子循环
                {
                    temp_dice[j] = random_dice.nextInt(6) + 1;
                    // temp_dice[j]=6-j;
                }
                System.out.printf("Player%d's dice:", i + 1);
                dice_print(temp_dice);
                System.out.print("      ");
                // 奖项判断
                int temp_award = judge_award(temp_dice);
                if (temp_award == 0)
                    System.out.println("getting no award!");
                else if ((temp_award % 10) != 0) {
                    if (Award[temp_award] != 0) {
                        Award[temp_award]--;
                        Players[i].get_award(temp_award);
                        switch (temp_award) {
                            case 1:
                                System.out.println("getting award(\"对堂\")!");
                                break;
                            case 2:
                                System.out.println("getting award(\"三红\")!");
                                break;
                            case 3:
                                System.out.println("getting award(\"四进\")!");
                                break;
                            case 4:
                                System.out.println("getting award(\"二举\")!");
                                break;
                            case 5:
                                System.out.println("getting award(\"一秀\")!");
                                break;

                        }
                    } else
                        System.out.println("no this kind of award,getting no award!");
                } else {
                    if (Award[0] == 0) {
                        Award[0] = i + (temp_award / 10) * 10;// 个位记录获奖者，十位记录奖大小
                        Players[i].get_award(0);
                        System.out.println("congratulations！getting the biggest award(\"状元\")!");
                    } else {
                        if ((Award[0] / 10) >= (temp_award / 10))
                            System.out.println("you are not bigger enough to snatch award(\"状元\"),getting no award!");
                        else {
                            if (i != Award[0] % 10) // 抢夺成功，被抢者奖项归零
                            {
                                Players[i].get_award(0);
                                Players[Award[0] % 10].being_snatched();
                                System.out.printf(
                                        "congratulations！you are successfully snatched Player%d award(\"状元\")!",
                                        Award[0] % 10);
                                System.out.println();
                            } else// 自己抢自己，不算获奖
                            {
                                System.out
                                        .println("you are not bigger than yourself in award(\"状元\"),getting no award!");
                            }
                            Award[0] = i + (temp_award / 10) * 10;// 出现抢夺，重新记录
                        }
                    }
                }
            }
            round++;
            sum = get_sum(Award);
        }
        // 此处循环结束
        System.out.println("");
        System.out.println("this game is over!below are all the players' award:");
        for (int i = 0; i < players; i++) {
            System.out.printf("Player%d get \"状元\":%d,\"对堂\":%d,\"三红\":%d,\"四进\":%d,\"二举\":%d,\"一秀\":%d.", i + 1,
                    Players[i].award[0], Players[i].award[1], Players[i].award[2], Players[i].award[3],
                    Players[i].award[4], Players[i].award[5]);
            System.out.println();
        }
        scanner.close();
    }

    public static int get_sum(int[] Award) {
        int sum = 0;
        for (int i = 1; i < 6; i++)
            sum += Award[i];
        return sum;
    }

    public static void dice_print(int[] temp_dice) {
        for (int i = 0; i < 6; i++)
            System.out.print(temp_dice[i]);
    }

    public static int judge_award(int[] temp_dice) {
        int[] dice_count = { 0, 0, 0, 0, 0, 0 };
        for (int i = 0; i < 6; i++)
            dice_count[temp_dice[i] - 1]++;
        // 状元七种情况列举
        if (dice_count[0] == 6)
            return 70;// 十位数表示状元大小，各位表示奖项
        if (dice_count[5] == 6)
            return 60;
        if (dice_count[3] == 6)
            return 50;
        if (dice_count[3] == 4 && dice_count[0] == 2)
            return 40;
        if (dice_count[3] == 5)
            return 30;
        if (dice_count[1] >= 5)
            return 20;
        if (dice_count[3] == 4)
            return 10;
        // 除状元外五种情况列举
        if ((dice_count[0] == 1) && (dice_count[1] == 1) && (dice_count[2] == 1) && (dice_count[3] == 1)
                && (dice_count[4] == 1) && (dice_count[5] == 1))
            return 1;
        if (dice_count[3] == 3)
            return 2;
        if (dice_count[0] >= 4)
            return 3;
        if (dice_count[3] == 2)
            return 4;
        if (dice_count[3] == 1)
            return 5;
        return 0;// 未中奖
    }
}