import java.util.Scanner; 

public class Lab2p1 {
    public static void main(String[] args) {
        int choice;
        Scanner sc = new Scanner(System.in); 
        do {
            System.out.println("1: multiplication test"); 
            System.out.println("2: quotient using division by subtraction"); 
            System.out.println("3: remainder using division by subtraction"); 
            System.out.println("4: count the number of digits");
            System.out.println("5: position of a digit");
            System.out.println("6: extract all odd digits"); 
            System.out.println("7: quit");
            choice = sc.nextInt();
            switch (choice) {
                case 1: /* add mulTest() call */
                    testMultiplication();
                    break;
                case 2: /* add divide() call */
                    System.out.println("What is the Dividend?");
                    int dividend = sc.nextInt();
                    System.out.println("What is the Divider?");
                    int divider = sc.nextInt();
                    int quotient = testDivision(dividend, divider);
                    System.out.printf("The Quotient is %d\n", quotient);
                    break;
                case 3: /* add modulus() call */
                    System.out.println("What is the Dividend?");
                    int dividend2 = sc.nextInt();
                    System.out.println("What is the Divider?");
                    int divider2 = sc.nextInt();
                    int remainder = testModulos(dividend2, divider2);
                    System.out.printf("The Remainder is %d\n", remainder);
                    break;
                case 4: /* add countDigits() call */
                    System.out.println("Provide a Number to count the Number of Digits");
                    int userNumber = sc.nextInt();
                    int numDigits = countDigits(userNumber);
                    if (numDigits == -1) {
                        System.out.printf("Number Provided: %d\nCount: Errorneous Input!!\n", userNumber);
                    }
                    else {
                        System.out.printf("Number Provided: %d\nCount: %d\n", userNumber, numDigits);
                    }
                    break;
                case 5: /* add position() call */
                    System.out.println("Number for Position: ");
                    int positionNumber = sc.nextInt();
                    System.out.println("Target Digit to Check: ");
                    int target = sc.nextInt();
                    int position = position(positionNumber, target);
                    System.out.printf("Position of Digit: %d\n", position);
                    break;
                case 6: /* add extractOddDigits() call */
                    System.out.println("Provide a Number for Extraction: ");
                    long userOdd = sc.nextLong();
                    long oddNumber = extractOddDigits(userOdd);
                    if (oddNumber == 0) {
                        System.out.println("Odd Digits: Errorneous Input");
                    }
                    else {
                        System.out.printf("Odd Digits: %d\n", oddNumber);
                    }
                    break;
                case 7: 
                    System.out.println("Program terminating ...."); 
            }
        } while (choice < 7); 
    }

    // 3.2 Multiplication Method
    public static void testMultiplication() {
        int score = 0;
        int upperBound = 9;
        int lowerBound = 1;
        int range = (upperBound - lowerBound) + 1;

        Scanner scObject = new Scanner(System.in); 
        for (int i = 0; i < 5; i += 1) {
            // Determine the 2 Operands in the Multiplication Operation randomly
            int firstDigit = (int) (Math.random() * range) + lowerBound;
            int secondDigit = (int) (Math.random() * range) + lowerBound;
            System.out.printf("How much is %d * %d?\n", firstDigit, secondDigit);
            int userAnswer = scObject.nextInt();

            if (userAnswer == (firstDigit * secondDigit)) {
                score += 1;
                System.out.println("Correct!!");
            }
            else {
                System.out.println("Incorrect!!");
            }   
        }

        System.out.printf("%d answers out of 5 are correct.\n", score);
    }

    public static int testDivision(int dividend, int divider) {
        // Division by Subtraction
        int remainder = 0;
        int quotient = 0;

        while (dividend >= divider) {
            dividend -= divider;
            quotient += 1;
        }
        return quotient;
    }

    public static int testModulos(int dividend, int divider) {
        // Division by Subtraction
        int remainder = 0;
        int quotient = 0;

        while (dividend >= divider) {
            dividend -= divider;
            quotient += 1;
        }
        remainder = dividend;
        return remainder;
    }

    public static int countDigits(long n) {
        if (n < 0) {
            return -1;
        }
        int numDigits = 0;
        // Every Division represents a single digit
        do {
            n /= 10;
            numDigits += 1;
        } while (n > 0);
        return numDigits;
    }

    public static int position(int n, int digit) {
        // Determine if number is present and their position
        int numDigits = countDigits(n);
        int digitPosition = 1;
        String nString = Integer.toString(n);

        for (int i = numDigits-1; i >= 0; i -= 1) {
            // Start from the Back of Array
            if (Character.getNumericValue(nString.charAt(i)) == digit) {
                return digitPosition;
            }
            digitPosition += 1;
        }
        return -1;
    }

    public static long extractOddDigits(long n) {
        // Input Validation
        if (n < 0) {
            // Errorneous or Negative Input
            return 0;
        }
        // Extracts the Odd Digit from Positive Number n and Combines them sequentially like a String
        String nString = Long.toString(n);
        int numDigits = countDigits(n);
        // Char Array to hold Long
        char ansString[] = new char[numDigits];
        int index = 0;
    
        for (int i = 0; i < numDigits; i += 1) {
            if (Character.getNumericValue(nString.charAt(i)) % 2 != 0) {
                // Odd Number; String is not an Array so we need charAt
                ansString[index] = nString.charAt(i);
                index += 1;
            }
        }
        
        // No Odd Numbers
        if (index == 0) {
            return -1;
        }

        // Convert Char Array into String, Remove Trailing Whitespace, then to Long
        String longAnsString = new String(ansString);
        long answer = Long.valueOf(longAnsString.trim());
        return answer;
    }
}