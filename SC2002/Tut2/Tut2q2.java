import java.util.Random;
import java.util.Scanner;

public class DiceApp {
    public static void main(String[] args) {
        Scanner scObject = new Scanner(System.in);
        int sumDice = 0;
        Dice dice = new Dice();
        System.out.println("Enter <1> to roll the first dice.");
        scObject.nextInt();
        dice.setDiceValue();
        sumDice += dice.getDiceValue();
        dice.printDiceValue();

        System.out.println("Enter <2> to roll the second dice.");
        scObject.nextInt();
        dice.setDiceValue();
        sumDice += dice.getDiceValue();
        dice.printDiceValue();

        System.out.printf("Your total number is: %d\n", sumDice);

    }
}

public class Dice {
    private int valueOfDice;

    // Constructor for Dice
    public Dice() {
        valueOfDice = 0;
    }

    // Helper Methods
    public void setDiceValue() {
        Random rand = new Random();
        valueOfDice = rand.nextInt(1, 7);
    }

    public int getDiceValue() {
        return valueOfDice;
    }

    public void printDiceValue() {
        System.out.printf("Current Value of Dice: %d\n", valueOfDice);
    }
}