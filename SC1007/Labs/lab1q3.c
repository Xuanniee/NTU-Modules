#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

typedef struct listnode
{
    int data;
    struct listnode *next;
} ListNode;

typedef struct linkedlist
{
    int size;
    struct ListNode *head;
} LinkedList;

int split(ListNode *curr, ListNode **ptrEvenList, ListNode **ptrOddList);
void printLinkedList(ListNode **ptrHead);

int main(void)
{
    // Get User Input
    char user_input[MAX];
    int num_array[MAX];
    memset(num_array, 0, MAX);
    printf("Get a List of Numbers, terminated by any non-digit character:\n");
    fgets(user_input, MAX, stdin);

    // Make a Copy of the String
    char *token = strtok(user_input, "  ");
    int array_len = 0;
    while (token != NULL)
    {
        num_array[array_len] = atoi(token);
        array_len += 1;
        // Get the Next Token
        token = strtok(NULL, " ");
    }
    // For the Non-Numeric Character
    array_len -= 1;

    // Create Linked List to store
    ListNode *head = (ListNode*) malloc(sizeof(ListNode));
    ListNode *curr = head;
    for (int i = 0; i < array_len; i += 1)
    {
        // Fill the Nodes with Data
        if (i == 0)
        {
            head->data = num_array[i];
            head->next = NULL;
            continue;
        }
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->data = num_array[i];
        newNode->next = NULL;   // Ensures Last Node points to Null
        curr->next = newNode;

        // Move the Cursor to the Latest Node
        curr = curr->next;   
    }

    // Before Split
    printf("Before split() is called:\n");
    printf("The Original List:\n");
    printLinkedList(&head);

    // After Split
    ListNode *evenList = (ListNode*) malloc(sizeof(ListNode));
    ListNode *oddList = (ListNode*) malloc(sizeof(ListNode));

    split(head, &evenList, &oddList);

    printf("After split() was called:\n");
    printf("The Original List:\n");
    printLinkedList(&head);
    printf("The Even List:\n");
    printLinkedList(&evenList);
    printf("The Odd List:\n");
    printLinkedList(&oddList);

    // Qn dictated 1 is success
    return 1; 
}

int split(ListNode *curr, ListNode **ptrEvenList, ListNode **ptrOddList)
{
    ListNode *headptr = curr;
    int counter = 0;
    // Have the Pointers Point at the Head Nodes
    ListNode *evenptr = (*ptrEvenList);
    ListNode *oddptr = (*ptrOddList);

    while (headptr != NULL)
    {
        // Even Indices
        if ((counter % 2) == 0)
        {
            if (counter == 0)
            {
                evenptr->data = headptr->data;
                evenptr->next = NULL;

                headptr = headptr->next;
                counter += 1;
            }
            
            else
            {
                ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
                newNode->data = headptr->data;
                newNode->next = NULL;
                evenptr->next = newNode;

                // Move to New Node
                evenptr = evenptr->next;
                headptr = headptr->next;
                counter += 1;
            }
        }

        // Odd Indices
        else
        {
            if (counter == 1)
            {
                oddptr->data = headptr->data;
                oddptr->next = NULL;

                headptr = headptr->next;
                counter += 1;
            }

            else
            {
                ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
                newNode->data = headptr->data;
                newNode->next = NULL;
                oddptr->next = newNode;

                // Move to New Node
                oddptr = oddptr->next;
                headptr = headptr->next;
                counter += 1;
            }
        }
    }

}

void printLinkedList(ListNode **ptrHead)
{
    printf("Current List: ");
    ListNode *curr = *ptrHead;
    while (curr != NULL)
    {
        printf("%i ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}