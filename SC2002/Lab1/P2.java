package Lab1;

import java.util.Scanner;

public class P2 {
    public static void main(String args[]) {
        // Read User's Salary & Merit Points
        try (Scanner scObject = new Scanner(System.in)) {
            System.out.println("Provide your Salary here: ");
            int userSalary = scObject.nextInt();
            System.out.println("Provide your Merit Points here: ");
            int meritPoints = scObject.nextInt();
            
            // Determine Grade & Display
            System.out.println("Your Grade is " + userGrade(userSalary, meritPoints));
        }
    }

    public static char userGrade(int salary, int meritPoints) {
        char currentGrade = 'd';
        if (salary >= 600 && salary <= 799) {
            currentGrade = 'B';
            
        }
        if (salary >= 700 && salary <= 899) {
            currentGrade = 'A';
        }
        if (salary >= 500 && salary <= 649) {
            currentGrade = 'C';
        }

        // Check for Demotion Criteria
        if (salary >= 600 && salary <= 649 && meritPoints < 10) {
            currentGrade = 'C';
        }
        else if (salary >= 600 && salary <= 649 && meritPoints >= 10) {
            currentGrade = 'B';
        }
        else if (salary >= 700 && salary <= 799 && meritPoints < 20) {
            currentGrade = 'B';
        }
        else if (salary >= 700 && salary <= 799 && meritPoints >= 20) {
            currentGrade = 'A';
        }
    
        return currentGrade;
    }
}
