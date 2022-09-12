// Function that determines if an expression containing brackets is balanced
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

// Function Prototype
int balanced(char *expression); 

int main(void)
{
    char userInput[MAX];
    // Get User Input
    printf("Enter an expression, terminated by a newline:\n");
    fgets(userInput, MAX, stdin);

    // Call the Helper Function
    balanced(userInput);
    return 0;
}

int balanced(char *expression)
{
    // Initialize Counters for Different Types of Brackets
    int num_bracket1 = 0;
    int num_bracket2 = 0;
    int num_bracket3 = 0;

    // Save the Head of String and Look for the Different Type of Brackets
    char *cursor = expression;
    while (*cursor != '\n')
    {
        if (*cursor == "(")
        {
            num_bracket1 += 1;
        }
        else if (strcmp(cursor, "[") == 0)
        {
            num_bracket2 += 1;
        }
        else if (strcmp(cursor, "{") == 0)
        {
            num_bracket3 += 1;
        }
        // Move Pointer to Next Char
        cursor += 1;
    }

    // Check if there is a corresponding Number of Complementary Brackets
    cursor = expression;
    while (*cursor != '\n')
    {
        if (strcmp(cursor, ")") == 0)
        {
            num_bracket1 -= 1;
            
        }
        else if (strcmp(cursor, "]") == 0)
        {
            num_bracket2 -= 1;
        }
        else if (strcmp(cursor, "}") == 0)
        {
            num_bracket3 -= 1;
        }

        if ((num_bracket1 < 0) || (num_bracket2 < 0) || (num_bracket3 < 0))
        {
            // Expression is not balanced
            printf("The expression is not balanced\n");
            return 0;
        }
    }

    if ((num_bracket1 < 0) && (num_bracket2 < 0) && (num_bracket3 < 0))
    {
        // Expression is Balanced
        printf("The expression is balanced\n");
        return 1;
    }
    // Fail Check
    printf("The expression is not balanced\n");
    return 0;
}