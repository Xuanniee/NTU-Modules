#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2D Array to hold Total Value


int bottom_up_dp(int n, int *s, int *v, int C)
{
    // Bottom - Up Approach involves caching and filling up all the possible values for the table first!!
    int numItems = n;
    int capacity = C;
    int *sizeArray = s;
    int *valueArray = v;

    // Creating the Columns to be Capacity of 1 unit in difference each
    int table[numItems][capacity];
    for (int i = 0; i < numItems; i += 1)   // First For Loop is Downwards Row
    {
        for (int j = 0; j< capacity; j += 1)
        {
            table[i][j] = 0;
        }
    }

    // Arrange the Items in sequence of Increasing Weights
    for (int i = 1; i < numItems; i += 1)
    {
        // First Item is Larger than Second in size
        if (sizeArray[i] > sizeArray[i+1])
        {
            // Swap both the Item in Size and Value Array
            int tmp = 0;
            tmp = sizeArray[i+1];
            sizeArray[i+1] = sizeArray[i];
            sizeArray[i] = tmp;

            // Swap Price
            tmp = valueArray[i+1];
            valueArray[i+1] = valueArray[i];
            valueArray[i] = tmp;
        }
    }

    // Fill up the Table
   for (int i = 0; i < numItems; i += 1)
    {
        // For each unit of Capacity
        int itemPrice = valueArray[i+1];
        
        for (int j = 0; j < capacity; j += 1)
        {
            // Each Entry is the higher of i) Previous Row's Value (i.e. Increase in Capacity did not help to sell more items)
            //                             ii) New Item Added + Prev Row[Remaining Capacity]
            
            // Fill First Row; i.e. Capacity = 1 to 5, only can choose first item
            if (i == 0)
            {
                // If Size of Item < Current Capacity
                if (sizeArray[i] <= j+1)
                {
                    table[i][j] = itemPrice;
                }
                else
                {
                    table[i][j] = 0;
                }
                continue;
            }

            // printf("I IS %d, ",i);
            
            // Subsequent Rows
            int first_value = table[i-1][j];
          
            // Current Item + Item that fits remaining capacity
            int second_value = 0;
            // IF ITEM TAKES UP ENTIRE CAPACITY
            if ((j+1) == sizeArray[i+1])
            {
                second_value = itemPrice;
            }
            else
            {
                second_value = itemPrice + table[i-1][j - sizeArray[i+1]];
            }
                        
            if (sizeArray[i+1] > (j+1))
            {
                // If New Item's Size is larger than Current Capacity, we will follow prev rows results (as tho we dont have new item)
                //printf("current row is %d first is %d\n", i, first_value);
                table[i][j] = first_value;
                continue;
            }

            // New Item is included
            else
            {
                // Will take the Max of Current Item with some other item that fills remaining capacity or Previous row
               // printf("First %d Second %d\n", first_value, second_value);
                if (first_value < second_value)
                {
                    // Current Combi is larger
                    table[i][j] = second_value;
                    continue;
                }
                else
                {
                    table[i][j] = first_value;
                    continue;
                }
            }
        }
    }

    // Take the Bottom Right Case (Entire Capacity and All Items is available to us)
    return table[numItems-1][capacity-1];
}

 
int main ()
{
    // n - Number of Items, C - Capacity of our bag
    int n,C;
    int function;
    // Sizes of our Items
    int *s;
    // Values of all Items
    int *v;

    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    // Creating an Array to store all Size & Values
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}