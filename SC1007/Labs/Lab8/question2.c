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
    // Top Down is to Store the Values if not Computed 
    
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

    return current_max;
    
}

int cr_bottom_up_dp(int *p, int n)
{
    // Bottom-Up stores all of the Subproblem Solutions before returning at the end.
    int placeholder = -1;
    for (int i = 1; i <= n; i += 1)
    {
        r[i] = p[i] + cr_bottom_up_dp(p, n-i);
    }

    for (int j = 1; j < n; j += 1)
    {
        if (r[j] > placeholder)
        {
            placeholder = r[j];
        }
    }

    return placeholder;
    
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
    printf("%d", n);
    
    
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
