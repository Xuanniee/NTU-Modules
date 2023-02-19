import java.util.Scanner;

public class VendingMachineApp {
    public static void main(String args[]) {
        VendingMachine vendingMachine = new VendingMachine();
        int userSelection = vendingMachine.selectDrink();

        switch(userSelection) {
            case 1:
                vendingMachine.insertCoins(3.00);
                break;
            case 2:
                vendingMachine.insertCoins(1.00);
                break;
            case 3:
                vendingMachine.insertCoins(5.00);
                break;
            default:
                System.out.println("Invalid Option");
        }        
    }
    
}

public class VendingMachine {
    // Constructor
    public VendingMachine() {}

    // Methods
    // 1. Returns Cost of Selected Drinl
    public int selectDrink() {
        Scanner scObject = new Scanner(System.in);
        System.out.println("====== Vending Machine ======");
        System.out.println("|1. Buy Beer ($3.00)        |");
        System.out.println("|2. Buy Coke ($1.00)        |");
        System.out.println("|3. Buy Green Tea ($5.00)   |");
        System.out.println("=============================");
        System.err.println("Please enter your selection:");

        return scObject.nextInt();
    }
    // 2. Returns Amount of Coin Inserted
    public double insertCoins(double drinkCost) {
        Scanner scObject = new Scanner(System.in);
        System.out.println("Please insert coins:");
        System.out.println("======== Coins Input ========");
        System.out.println("|Enter 'Q' for Ten Cents    |");
        System.out.println("|Enter 'T' for Twenty Cents |");
        System.out.println("|Enter 'F' for Fifty Cents  |");
        System.out.println("|Enter 'N' for a Dollar     |");
        System.out.println("=============================");

        double totalAmount = 0;
        while(totalAmount < drinkCost) {
            char insertedCoin = scObject.next().charAt(0);

            switch(insertedCoin) {
                case 'Q':
                    totalAmount += 0.10;
                    break;
                case 'T':
                    totalAmount += 0.20;
                    break;
                case 'F':
                    totalAmount += 0.50;
                    break;
                case 'N':
                    totalAmount += 1.00;
                    break;
                default:
                    System.out.println("Invalid Input!!");
            }
            System.out.printf("Coins inserted: $ %.2f\n", totalAmount);
        }

        checkChange(totalAmount, drinkCost);
        printReceipt();
        return totalAmount;
    }
    // 3. Print the Change of the Drinks
    public void checkChange(double amount, double drinkCost) {
        double change = amount - drinkCost;
        System.out.printf("Change: $ %.2f\n", change);
    }
    // 4. Print the Receipt
    public void printReceipt() {
        System.out.println("Please collect your drink!!");
        System.out.println("Thank you!!!");
    }
}