#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define a Queue
typedef struct listnode
{
    // Implementing a Queue using a Linked List
    char item;
    struct listnode *next;
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

    // Place the User Input into a Linked List
    int input_Iterable = 0;
    int queue_size = 0;
    ListNode *headPtr = NULL;
    ListNode *cursor = NULL;
    ListNode *tailPtr = NULL;
    while (userInput[input_Iterable] != '\0')
    {
        // Convert to Lowercase and Ignore Whitespaces
        if (headPtr == NULL)
        {
            ListNode *cursor = (ListNode*) malloc(sizeof(ListNode));
            cursor->item = tolower(userInput[input_Iterable]);
            cursor->next = NULL;

            headPtr = cursor;
            queue_size += 1;
        }

        // Storing every Char into my Linked List
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->item = tolower(userInput[input_Iterable]);
        newNode->next = NULL;
        
        cursor->next = newNode;
        cursor = cursor->next;
        queue_size += 1;

        // Place a Last Node Pointer
        if (userInput[input_Iterable + 1] == '\0')
        {
            tailPtr = newNode;
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