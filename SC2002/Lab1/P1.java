package Lab1;

import java.util.Scanner;

public class P1 {
    // Lab 1 Question 1 - Read a Character from the User and use a Switch Statement
    public static void main(String args[]) {
        // Get User Input
        try(Scanner scObject = new Scanner(System.in)) {
            System.out.println("Provide a Character here: ");
            char userInput = scObject.next().charAt(0);

            // Switch Statement
            switch(userInput) {
                case 'A', 'a': 
                    System.out.println("Action Movie Fan!!");
                    break;
                case 'C', 'c': 
                    System.out.println("Comedy Movie Fan!!");
                    break;
                case 'D', 'd':
                    System.out.println("Drama Movie Fan!!");
                    break;
                default:
                    System.out.println("Invalid Choice :<");
            }
        }
    }
}
