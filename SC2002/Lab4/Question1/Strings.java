import java.util.Scanner;
public class Strings
{
// --------------------------------------------
// Reads in an array of Strings, sorts them,
// then prints them in sorted order.
// --------------------------------------------
	public static void main (String[] args)
	{
		// Initialisation
		String[] stringList;
		int sizeList;
		Scanner scObject = new Scanner(System.in);

		// Number of Strings to Sort
		System.out.print ("\nHow many strings do you want to sort? ");
		sizeList = scObject.nextInt();
		stringList = new String[sizeList];

		// User Input
		System.out.println ("\nEnter the strings to be sorted...");
		for (int i = 0; i < sizeList; i++) {
			stringList[i] = scObject.next();
		}

		// Sort the List of Strings by Length of String then Reverse Alphabetical Order
		Sorting.insertionSortDesc(stringList);

		// Print out Sorted Results
		System.out.println ("\nYour strings in sorted order...");
		for (int i = 0; i < sizeList; i++) {
			System.out.print(stringList[i] + " ");
			System.out.println ();
		}

		scObject.close();
			
	}

}