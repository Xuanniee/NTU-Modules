#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a Global Array to act as the Memory to store subproblem solutions
int *Memory;

// Use Top - Down Dynamic Programming
int top_down_dp(int n)
{
    // Check if the solution to a subproblem is existing. If it isn't calculate and cache the result
    // Input Validation
    // if (n < 0)
    // {
    //     return 1;
    // }
    // Base Case
    if (n == 0)
    {
        Memory[0] = 0;
        return 0;
    }
    else if (n == 1)
    {
        Memory[1] = 1;
        return 1;
    }
    else if (n == 2)
    {
        Memory[2] = 2;
        return 2;
    }

    // Check if the Terms required to Compute are existing in memory
    if (Memory[n-1] == -1)
    {
        // Calculate if not in Memory
        Memory[n-1] = top_down_dp(n-1);
    }
    if (Memory[n-2] == -1)
    {
        Memory[n-2] = top_down_dp(n-2);
    }
    if (Memory[n-3] == -1)
    {
        Memory[n-3]= top_down_dp(n-3);
    }

    // Calculate the Solution
    int solution = Memory[n-1] + (2 * Memory[n-2]) - (3 * Memory[n-3]);
    return solution;

}


 
int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);

    // After knowing the value of the number n
    Memory = (int*) malloc(n*sizeof(int));
    memset(Memory, -1, (sizeof(int)*n));
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
        
}