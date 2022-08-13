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

int duplicateReverse(ListNode *curr, ListNode **ptrNewHead);
void printLinkedList(ListNode **ptrHead);

int main(void)
{
    // Get User Input
    char user_input[MAX];
    int num_array[MAX];
    memset(num_array, 0, MAX);
    printf("Get a List of Numbers, terminated by any non-digit character:\n");
    fgets(user_input, MAX, stdin);

    // Parsing to create an array of Ints
    char *token = strtok(user_input, "  ");
    int array_len = 0;
    while (token != NULL)
    {
        num_array[array_len] = atoi(token);
        array_len += 1;
        // Get the Next Token
        token = strtok(NULL, " ");
    }
    // Final Array Length for the Non-Numeric Character
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

    // Before Reverse
    printf("\n");
    printf("Before duplicateReverse() is called:\n");
    printLinkedList(&head);
    printf("\n");

    ListNode *ptrNewHead;
    duplicateReverse(head, &ptrNewHead);

    // After Reverse
    printf("After duplicateReverse() is called:\n");
    printf("The Original List:\n");
    printLinkedList(&head);
    printf("The duplicated reverse list:\n");
    printLinkedList(&ptrNewHead);

    // Qn dictated 1 is success
    return 1; 
}

int duplicateReverse(ListNode *curr, ListNode **ptrNewHead)
{
    // Pointer on Original List and New List
    ListNode *prev_node = curr;
    ListNode *current_node = curr->next;
    ListNode *next_node = current_node->next;

    // Copy the Linked List
    ListNode *copyLL = (ListNode*) malloc(sizeof(ListNode));
    copyLL->data = prev_node->data;
    copyLL->next = NULL;
    (*ptrNewHead) = copyLL;
    prev_node = prev_node->next;

    while (true)
    {
        if (prev_node == NULL)
        {
            break;
        }

        // Transfer Data
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->data = prev_node->data;
        newNode->next = NULL;
        copyLL->next = newNode;

        copyLL = copyLL->next;
        prev_node = prev_node->next;
    }

    // Reset Pointers by Having the 3 Pointers point at Copied List
    prev_node = NULL;
    current_node = *ptrNewHead;
    next_node = NULL;
    ListNode *newCursor = *ptrNewHead;

    // Reverse the Linked List
    while (current_node != NULL)
    {
        // Save the Next Node
        next_node = current_node->next;
        // Reverse the Link
        current_node->next = prev_node;
        // Move Nodes Forward
        prev_node = current_node;
        current_node = next_node;

        if (next_node != NULL)
        {
            next_node = next_node->next;
        }

        // // Have the Middle Pointer point at the First Pointer
        // middlePtr->next = reversePtr;

        // // Make First Node Point at Null
        // if (reversePtr == newCursor)
        // {
        //     reversePtr->next = NULL;
        // }

        // // Move all the Pointers forward by 1 Node
        // reversePtr = middlePtr;
        // middlePtr = forwardPtr;
        // forwardPtr = forwardPtr->next;

        // // Break Condition: Forward at Last Node
        // if (forwardPtr->next == NULL)
        // {
        //     // // Have Forward Ptr Point at Second Last Node
        //     // forwardPtr->next = middlePtr;
        //     // // Head Pointer point at Last node
        //     // *ptrNewHead = forwardPtr;
        //     // Break
        //     return 1;
        // }
    }
    // Set the Head Pointer to Previous Node because the other 2 Nodes are pointing at NULL
    *ptrNewHead = prev_node;
    return 1;
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