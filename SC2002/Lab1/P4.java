package Lab1;

import java.util.Scanner;

public class P4 {
    public static void main(String args[]) {
        try (Scanner scObject = new Scanner(System.in)) {
            // Get Height from User
            System.out.println("Provide the Height of the Pyramid here: ");
            int height = scObject.nextInt();
            
            // Input Validation
            if (height == 0) {
                System.out.println("Errorneous Input!!");
            }
            /* Prof's Answer */
            /*
            String[] label_arr = {"BB", "AA"};
            for (int i = 1; i <= height; i++) {
                for (int j = i; j > 0; j--) {
                    System.out.print(label_arr[j % 2]);
                }
                System.out.println();
            }
            */

            // Variables to keep track of Pyramid
            boolean AA = true;
            int currentLevel = 1;

            for (int i = 0; i < height; i += 1) {
                if (i % 2 == 0) {
                    AA = true;
                }
                else {
                    AA = false;
                }
                for (int j = currentLevel; j > 0; j -= 1) {
                    if (AA) {
                        System.out.print("AA");
                        AA = false;
                    }
                    else {
                        System.out.print("BB");
                        AA = true;
                    }
                }
                currentLevel += 1;
                System.out.println();
            }

        }
    }
}
