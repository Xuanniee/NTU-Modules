#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//memory
int *r;

int cr_recursive(int *p, int n)
{
    // Base Case
    if (n == 0)
    {
        return 0;
    }

    // P is an int array containing the prices of different rods; N is the original length of the rod
    int current_max = -1;
    for (int i = 1; i <= n; i += 1)
    {
        // Calculate the Total Price of Cutting a Rod in N ways
        int current_price = p[i] + cr_recursive(p, (n-i));
        if (current_price > current_max)
        {
            current_max = current_price;
        }
    }
    return current_max;
    
}

int cr_top_down_dp(int *p, int n)
{
    // Top Down is to compute when we need the results and store them
    
    // Base Case
    if (n <= 0)
    {
        return 0;
    }

    // Recursive Case
    int current_max = -1;
    for (int i = 1; i <= n; i += 1)
    {
        // Calculate the Price of the Rods to be sold by Cutting i-cm out
        int current_value = p[i] + cr_top_down_dp(p, n-i);

        if (current_value > current_max)
        {
            current_max = current_value;
        }
        
    }

    // Write to Memroy
    r[n] = current_max;
    return current_max;
    
}

int cr_bottom_up_dp(int *p, int n)
{
    // Bottom-Up stores all of the solutions using Tabulation
    
    // First Array Value
    r[0] = 0;
    
    int placeholder = 0;
    // Iterate through the Rods of Various Lengths to fill the table
    for (int i = 1; i <= n; i += 1)
    {
        // Iterate through all the possibilities of cutting the rods into various lengths
        for (int j = 1; j <= i; j += 1)
        {
            // Calculating the Value of Cutting Rod into length i and max value of remaining pieces
            placeholder = p[j] + r[i-j]; // r[x] is the Max Value of Remaining Length
            if (placeholder > r[i])
            {
                r[i] = placeholder;
            }
        }
    }

    return r[n];    
}
 
int main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,5,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
    scanf("%d",&function);
    while (function != 0)
    {
        if (function == 1)
        {
            printf("The maximun value is: %d \n", cr_recursive(p,n));
        }
        else if (function == 2)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_top_down_dp(p,n));
        }
        else if (function == 3)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_bottom_up_dp(p,n));
        }
        printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
        scanf("%d",&function);
    }

    return 0;
}
