import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class TestHybridSort {
    // Attributes for tracking Array Size n and Threshold Value S
    private static int MIN_ARRAY_SIZE = 1000;
    private static int MAX_ARRAY_SIZE = 10000000;
    private static int HIGHEST_VALUE_PERMISSIBLE = 11000000;
    private static int MIN_VALUE = 1000;
    private static int MAX_VALUE = 10000000;
    private static int CURRENT_THRESHOLD = 10;

    // Methods to alter Private Attributes
    public static void setMaxArraySize(int arraySize) {
        MAX_VALUE = arraySize;
    }
    public static void setMinArraySize(int arraySize) {
        MIN_VALUE = arraySize;
    }
    public static void setHighestValue(int highestValue) {
        CURRENT_THRESHOLD = highestValue;
    }

    public static void main(String args[]) {
        // Instantiate the Necessary Objects
        int inputArray[] = {5, 4, 8, 3, 7, 1, 0, 9, 2, 6};
        SortingMethods sortObject = new SortingMethods();
        Comparisons trackComparisons = new Comparisons();

        // Scan in User Input
        Scanner scObject = new Scanner(System.in);
        System.out.println("Select the value to be kept constant: ");
        System.out.println("1. Threshold Value S");
        System.out.println("2. Input Array Size N");
        int userChoice = scObject.nextInt();

        // Fix either S or N
        int forLoopIterator = 0;
        if (userChoice == 1) {
            // Fixed S, changing Array Size
            forLoopIterator = MAX_VALUE;
        }
        else if (userChoice == 2) {
            // Fixed N, changing Threshold Value
            forLoopIterator = CURRENT_THRESHOLD;
        }

        System.out.println("Select the sort to be used: ");
        System.out.println("1. Merge Sort");
        System.out.println("2. Insertion Sort");
        System.out.println("3. Hybrid Sort");
        int sortSelection = scObject.nextInt();

        for (int i = MIN_ARRAY_SIZE; i <= forLoopIterator; i += 1000000) {
            trackComparisons.resetComparisons();
            if (userChoice == 1) {
                // Threshold Value is Fixed
                inputArray = generateArrays(i);
                sortObject.setThresholdValue(10);
            }
            else if (userChoice == 2) {
                // Array Size is Fixed
                inputArray = generateArrays(MIN_ARRAY_SIZE);
                sortObject.setThresholdValue(i);
            }
            

            long sortTimeTaken = 0, startTime = 0, endTime = 0;
            switch(sortSelection) {
                case 1:
                    printArray(inputArray);
                    startTime = System.nanoTime();
                    sortObject.mergeSort(inputArray, 0, inputArray.length - 1, trackComparisons);
                    endTime = System.nanoTime();
                    sortTimeTaken = endTime - startTime;
                    break;
                case 2:
                    startTime = System.nanoTime();
                    sortObject.insertionSort(inputArray, trackComparisons);
                    endTime = System.nanoTime();
                    sortTimeTaken = endTime - startTime;
                    break;
                case 3:
                    startTime = System.nanoTime();
                    sortObject.hybridSort(inputArray, 0, inputArray.length - 1, trackComparisons);
                    endTime = System.nanoTime();
                    sortTimeTaken = endTime - startTime;
                    break;
                default:
                    System.out.println("Error!!");
            }
        
            // Print Statements
            System.out.printf("The Sorting Method took %d nanoseconds\n", sortTimeTaken);
            System.out.printf("Number of Key Comparisons: %d\n",trackComparisons.getKeyComparisons());

        }
    }

    public static void printArray(int inputArray[]) {
        for (int i = 0; i < inputArray.length; i += 1) {
            System.out.printf("%d, ", inputArray[i]);
        }
        System.out.println();
    }

    // Method to generate Arrays of Increasing Sizes
    static int[] generateArrays(int arraySize) {
        // Input Validation
        if (arraySize < MIN_ARRAY_SIZE || arraySize > MAX_ARRAY_SIZE) {
            int nullArray[] = new int[1];
            return nullArray;
        }
        
        // Instantiate a Random Object
        Random randObject = new Random();
        int generatedArray[] = new int[arraySize];

        // Populate Array with Random Integers
        for (int i = 0; i < arraySize; i += 1) {
            // Generate Random Int from 0 to 11 million - 1
            generatedArray[i] = randObject.nextInt(HIGHEST_VALUE_PERMISSIBLE);
        }

        return generatedArray;
    }
    
}

public class Comparisons {
    // Track the Number of Key Comparisons
    private int NUM_KEY_COMPARISONS = 0;

    // Constructor
    Comparisons() {}

    public int getKeyComparisons() {
        return NUM_KEY_COMPARISONS;
    }

    public void incrementKeyComparisons(int incrementalValue) {
        NUM_KEY_COMPARISONS += incrementalValue;
    }

    public void decrementKeyComparisons(int decrementalValue) {
        NUM_KEY_COMPARISONS -= decrementalValue;
    }

    public void resetComparisons() {
        NUM_KEY_COMPARISONS = 0;
    }
}

// Algorithm for Merge Sort
public class SortingMethods {
    // Threshold to determine if Merge or Insertion Sort should be used
    private int THRESHOLD_VALUE = 10;

    // Constructor
    SortingMethods() {}

    /**
     *  Setter for Threshold Value
     */
    public void setThresholdValue(int threshold) {
        THRESHOLD_VALUE = threshold;
    }

    /**
     * Hybrid Sort is to combine Merge and Insertion Sorts together, using Insertion only for small input array sizes
     * @param inputArray
     * @param startIndex
     * @param endIndex
     */
    public void hybridSort(int inputArray[], int startIndex, int endIndex, Comparisons trackComparisons) {
        // Determine Input Array Size
        int arraySize = inputArray.length;

        trackComparisons.incrementKeyComparisons(1);
        if (arraySize <= THRESHOLD_VALUE) {
            insertionSort(inputArray, trackComparisons);
        }
        else {
            mergeSort(inputArray, startIndex, endIndex, trackComparisons);
        }

    }

    /**
     * Merge Sort and their Helper Functions
     * @param inputArray
     * @param startIndex
     * @param endIndex
     */
    public void mergeSort(int inputArray[], int startIndex, int endIndex, Comparisons trackComparisons) {
        // Determine the Paritition Element
        int middleIndex = (startIndex + endIndex) / 2;

        // Base Case
        trackComparisons.incrementKeyComparisons(1);
        if (endIndex - startIndex <= 0) {
            // 1 Element
            return;
        }

        // Recursive Call for Merge Sort
        else if (endIndex - startIndex > 1) {
            trackComparisons.incrementKeyComparisons(1);
            // 3 or More Elements in SubArray; Further divide into 2 subarrays
            mergeSort(inputArray, startIndex, middleIndex, trackComparisons);
            mergeSort(inputArray, (middleIndex+1), endIndex, trackComparisons);
        }

        // Merge the 2 SubArrays tgh while Sorting; Can also Skip to here if Array has 2 Elements only
        mergeFunction(inputArray, startIndex, endIndex, trackComparisons);
    }

    public void mergeFunction(int inputArray[], int startIndex, int endIndex, Comparisons trackComparisons) {
        // Keeping track of the number of comparisons made
        trackComparisons.incrementKeyComparisons(1); 
        // Base Case
        if (endIndex - startIndex <= 0) {
            // 1 Element not required to merge
            return;
        }

        // Determine the Sizes of the 2 Subarrays
        int middleIndex = (startIndex + endIndex) / 2;
        // +1 to list 1 since we subtracted the middle Index which needs to be in list1, not list2
        int list1Size = middleIndex - startIndex + 1;
        int list2Size = endIndex - middleIndex;

        // Create and Copy Elements into 2 Temporary Arrays
        int list1[] = new int[list1Size];
        int list2[] = new int[list2Size];
        for (int i = 0; i < list1Size; i += 1){
            list1[i] = inputArray[startIndex + i];
        }
        for (int j = 0; j < list2Size; j += 1) {
            list2[j] = inputArray[middleIndex + 1 + j];
        }

        // Initial Indices of Arrays
        int i = 0, j = 0;
        int mergedIndex = startIndex;

        // Sort and Merge until 1 Subarray is Empty
        while(i < list1Size && j < list2Size) {
            trackComparisons.incrementKeyComparisons(1);
            if (list1[i] < list2[j]) {
                trackComparisons.incrementKeyComparisons(1);
                // First Subarray Element is Smaller
                inputArray[mergedIndex] = list1[i];
                mergedIndex += 1;
                i += 1;
            }
            else if (list1[i] > list2[j]) {
                trackComparisons.incrementKeyComparisons(2);
                // Second Subarray Element is Smaller
                inputArray[mergedIndex] = list2[j];
                mergedIndex += 1;
                j += 1;

            }
            else {
                trackComparisons.incrementKeyComparisons(3);
                // Equal Value, Best Case as 2 Elements removed
                inputArray[mergedIndex] = list1[i];
                mergedIndex += 1;
                // Removing 2nd Element
                inputArray[mergedIndex] = list2[j];
                mergedIndex += 1;
                i += 1;
                j += 1;
            }
        }

        // Copy Remaining Elements of Left / Right Subarrays if any; works as i,j are indices
        while (i < list1Size) {
            trackComparisons.incrementKeyComparisons(1);
            inputArray[mergedIndex] = list1[i];
            mergedIndex += 1;
            i += 1;
        }
        while (j < list2Size) {
            trackComparisons.incrementKeyComparisons(1);
            inputArray[mergedIndex] = list2[j];
            mergedIndex += 1;
            j += 1;
        }
    }

    /**
     * Insertion Sort & Helper Methods
     * @param inputArray
     */
    public void insertionSort(int inputArray[], Comparisons trackComparisons) {
        // Constantly select an element from the unsorted subarray and place it in the correct position in the sorted subarray
        int arrayLength = inputArray.length;

        // Selecting an element, start from the Second Position
        for (int i = 1; i < arrayLength; i += 1) {
            // Compare the selected element with all the elements in the sorted subarray
            for (int j = i; j > 0; j -= 1) {
                trackComparisons.incrementKeyComparisons(1);
                if (inputArray[j] < inputArray[j-1]) {
                    swap(inputArray, (j-1), j);
                }
                else {
                    break;
                }
            }
        }

    }

    /**
     * Function to swap 2 elements in an Arrays
     * @param inputArray
     * @param index1
     * @param index2
     */
    public void swap(int inputArray[], int index1, int index2) {
        int temp = inputArray[index1];
        inputArray[index1] = inputArray[index2];
        inputArray[index2] = temp;
    }
}