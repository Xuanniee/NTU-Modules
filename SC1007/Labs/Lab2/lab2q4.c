#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 100

// Function Prototypes
void in2Post(char* infix, char* postfix);

// Structs
typedef struct listnode
{
    char item;
    struct listnode *next;
} ListNode;

typedef struct stack
{
    int size;
    ListNode *head;
} Stack;

int main(void)
{
    // Get User Input
    char userInput[MAX];
    scanf("%[^\n]%*c", userInput);

    // Empty String to store Prefix
    char *postfix = NULL;
    in2Pre(&userInput, postfix);
    return 0;

}

void in2Post(char* infix, char* postfix)
{
    // Iterate through the Entire String
    char *cursor = infix;
    while (*cursor)
    {
        // Is an AlphaNumerical Character
        if (isalpha(*cursor) != 0)
        {
            // Add it to the PostFix String
        }
    }

}