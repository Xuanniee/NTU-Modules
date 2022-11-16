#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//memory
int *r;

int cr_bottom_up_dp_print(int *p, int n)
{
    // Bottom Up is to use Tabulation to form the Table then Index
    r[0] = 0;
    int rod1[n], rod2[n];
    memset(rod1, 0, sizeof(rod1));
    memset(rod2, 0, sizeof(rod2));

    int currentValue = 0;
    // Array to Contain Rods of Various Length

    // Iterate through the Max Value for Rods of Length <= n
    for (int i = 1; i <= n; i += 1)
    {
        // Using iteration, determine the optimum length to cut the rod
        for (int j = 1; j <= i; j += 1) // If i == 1, j == 1 means we don't cut the rod
        {
            // Sum Value of Rod of j Length & Max Value (that should have been calculated) of Remaining Length
            currentValue = p[j] + r[i-j];
            // If Greater than Current Max
            if (currentValue > r[i])
            {
                r[i] = currentValue;
                // Update the Rods Array
                rod1[i] = j;
                rod2[i] = i-j;
            }

        }

    }
    printf("The Rods are cut into Lengths %d and %d\n", rod1[n], rod2[n]);
    return r[n];
}

 
void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,4,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    
    
    //set all memory elements to -1
    for (i=0; i<=n; i++)
        r[i] = -1;
                
    printf("The maximun value is: %d \n", cr_bottom_up_dp_print(p,n));
}