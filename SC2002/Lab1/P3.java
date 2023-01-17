package Lab1;

import java.util.Scanner;

/**
 *  Programs to generate tables of currency from SGD to USD
 *  Conversion Rate is 1 USD to 1.82 SGD
 */

public class P3 {
    public static void main(String args[]) {
        // Get User Input for Starting, Ending and Increment
        try(Scanner scObject = new Scanner(System.in)) {
            System.out.println("Provide a Starting Value: ");
            int starting = scObject.nextInt();

            System.out.println("Provide a Ending Value: ");
            int ending = scObject.nextInt();

            System.out.println("Provide an Increment Value: ");
            int increment = scObject.nextInt();

            // Input Validation
            if (ending < starting) {
                System.out.println("Errorneous Input!!");
                return;
            }

            // Generate 3 Output Tables
            // For Table
            System.out.println("US$                 S$");
            System.out.println("----------------------");
            for (int i = starting; i <= ending; i += increment) {
                System.out.print(i + "                ");
                System.out.println(i * 1.82);
            }
            System.out.println();

            // While Table
            System.out.println("US$                 S$");
            System.out.println("----------------------");
            int index = starting;
            while (index != (ending+increment)) {
                System.out.print(index + "                ");
                System.out.println(index * 1.82);
                // Increment Counter 
                index += increment;
            }
            System.out.println();

            // Do-While Table
            int index2 = starting;
            System.out.println("US$                 S$");
            System.out.println("----------------------");
            do {
                System.out.print(index2 + "                ");
                System.out.println(index2 * 1.82);
                index2 += increment;
            } while (index2 != (ending+increment));
            System.out.println();
        }

    }
}