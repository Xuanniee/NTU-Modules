import java.util.Scanner;
public class Numbers
{
// --------------------------------------------
// Reads in an array of integers, sorts them,
// then prints them in sorted order.
// --------------------------------------------
	public static void main (String[] args)
	{
		Integer[] intList;
		int size;
		Scanner scan = new Scanner(System.in);
		System.out.print ("\nHow many integers do you want to sort? ");
		size = scan.nextInt();
		intList = new Integer[size];
		System.out.println ("\nEnter the numbers...");
		for (int i = 0; i < size; i++){
			// Int doesn't work because it is not a class and does not have a comparison function
			intList[i] = scan.nextInt();
			// Hence we need to use autoboxing to convert int to Integer Class with Comparison Function
			Sorting.selectionSort(intList);
			System.out.println ("\nYour numbers in sorted order...");
		}
		for (int i = 0; i < size; i++) {
			System.out.print(intList[i] + " ");
			System.out.println ();
		}
		scan.close();	
	}
}