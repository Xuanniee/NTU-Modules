#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

// Define a Queue
typedef struct listnode
{
    // Implementing a Queue using a Linked List
    char item;
    struct listnode *next;
    struct listnode *prev;
} ListNode;

typedef struct _queue
{
    int size;
    ListNode *head;
    ListNode *tail;
} Queue;

int palindrome(Queue *wordPtr);

int main(void)
{
    // Get User Input
    char userInput[MAX];
    printf("Enter a string of characters, terminated by a newline:\n");
    fgets(userInput, MAX, stdin);
    userInput[strcspn(userInput, "\n")] = '\0';
    // Place the User Input into a Linked List
    int input_Iterable = 0;
    int queue_size = 0;
    ListNode *headPtr = NULL;
    ListNode *cursor = NULL;
    ListNode *tailPtr = NULL;

    while (true)
    {
        if (userInput[input_Iterable] == '\0')
        {
            break;
        }
        // Prevent Whitespaces from being added into the Linked List
        else if (userInput[input_Iterable] == ' ')
        {
            input_Iterable += 1;
            continue;
        }
        if(headPtr == NULL)
        {
            // Create new Node
            ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
            newNode->item = userInput[input_Iterable];
            newNode->next = NULL;
            newNode->prev = NULL;

            // Shift Pointers
            headPtr = newNode;
            cursor = newNode;
            tailPtr = newNode;
            
            // Update Counters
            queue_size += 1;
            input_Iterable += 1;
        }

        else
        {
            // Storing every Char into my Linked List
            ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
            newNode->item = userInput[input_Iterable];
            newNode->next = NULL;
            newNode->prev = cursor;
            
            // Connect the New Node to the Queue
            cursor->next = newNode;
            cursor = cursor->next;

            // Update the Tail Pointers and Counters
            tailPtr = cursor;
            input_Iterable += 1;
            queue_size += 1;
        }
    }

    // Use Function to test if Palindrome
    Queue *wordPtr = (Queue*) malloc(sizeof(Queue));
    wordPtr->size = queue_size;
    wordPtr->head = headPtr;
    wordPtr->tail = tailPtr;

    palindrome(wordPtr);

    // Free the Memory Allocated to prevent leaks
    return 0;
}

int palindrome(Queue *wordPtr)
{
    // Create Pointers for Queue
    int queueSize = wordPtr->size;
    ListNode *headQueue = wordPtr->head;
    ListNode *tailQueue = wordPtr->tail;

    // Determine if Queue is Odd or Even, thus Number of Comparisons
    int numComparisons = 0;
    if ((queueSize % 2) == 0)
    {
        // Even
        numComparisons = queueSize / 2;
    }

    else
    {
        // Odd
        numComparisons = ceil(queueSize / 2);
    }

    // Check if a Palindrome
    for (int i = 0; i < numComparisons; i += 1)
    {
        // If the Chars are the same
        if (strcasecmp(&headQueue->item, &tailQueue->item) == 0)
        {
            // Move the Pointers
            headQueue = headQueue->next;
            tailQueue = tailQueue->prev;
            continue;
        }
        else
        {
            // Not a Palindrome
            printf("The string is not a palindrome.");
            return 0;
        }
    }
    // Is a Palindrome
    printf("The string is a palindrome.");
    return 1;
}