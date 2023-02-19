// Issue is not Importing the Sorts as well
import Sorting.selectionSort;
import java.util.Scanner;

/**
 * Reads in an array of integers, sorts them,
 * then prints them in sorted order.
 */
public class Numbers {
    public static void main (String[] args){
        // Initialisation
        int[] intList;
        int size;

        // Determine List Size
        Scanner scan = new Scanner(System.in);
        System.out.print ("\nHow many integers do you want to sort? ");
        size = scan.nextInt();
        intList = new int[size];

        // Adding Numbers into the List
        System.out.println ("\nEnter the numbers...");
        for (int i = 0; i < size; i++)
            intList[i] = scan.nextInt();
            Sorting.selectionSort(intList);
            System.out.println ("\nYour numbers in sorted order...");
        for (int i = 0; i < size; i++)
            System.out.print(intList[i] + " ");
        // Error with initial code not compiling is the whitespace in println() 
        System.out.println ();
    }
}