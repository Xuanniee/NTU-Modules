#include <stdlib.h>
#include <stdio.h>

// Linked List Node
struct listnode
{
    // Data Field and Pointer to Node
    int item;
    struct listnode *next;
};
typedef struct listnode ListNode;

int insertNode(ListNode **ptrHead, int index, int item);
int recursive_InsertNode(ListNode **ptrHead, int *index_variable, int index, int item);

int main(void)
{
    // Create 2 Nodes
    ListNode *head = NULL;
    ListNode *second = NULL;
    ListNode *third = NULL;

    // Allocate Nodes in Heap
    head = malloc(sizeof(ListNode));
    second = malloc(sizeof(ListNode));
    third = malloc(sizeof(ListNode));

    // Assign Data
    head->item = 1;
    second->item = 2;
    third->item = 3;
    head->next = second;
    second->next = third;
    third->next = NULL;

    // Cursor Pointer
    ListNode *cursor = head;

    // Test Function
    // insertNode(&cursor, 2, 9);      // Creates a Pointer that points at the address of the Cursor
    int index = 2;
    int *index_variable = &index;
    recursive_InsertNode(&cursor, index_variable, index, 9);

    cursor = head;

    // Print out Values in Linked Liswt
    do {
        printf("Value: %i \n", cursor->item);
        cursor = cursor->next;
    } while (cursor != NULL);       // Stops when we are no longer in the Linked Lists

    // Free the Linked List
    ListNode *safe_to_free; // To Free Nodes
    cursor = head;
    safe_to_free = head;

    while(cursor != NULL)
    {
        // Move the Cursor to the Next Node in the Linked List
        cursor = cursor->next;
        // Free the Node we just traversed
        free(safe_to_free);
        // Move the Second Cursor to the Cursor
        safe_to_free = cursor;
    }
    return 0;    
}

// Write an InsertNode Function
int insertNode(ListNode **ptrHead, int index, int item)
{
    // Create a Pointer and New Node to store the information
    ListNode *before, *newNode;

    // Front of Linked List
    if (index == 0)
    {
        newNode = malloc(sizeof(newNode));
        newNode->item = item;
        // newNode will point at whatever the Head Pointer is pointing at
        newNode->next = *ptrHead;                    // address of First Node of Linked List
        // ptrHead will point at newNode
        *ptrHead = newNode;
        return 1;
    }
    
    // Middle / End of Index
    else
    {
        // Point at First Node
        before = *ptrHead;

        // Traverse the Linked List
        for(int i = 1; i < index; i += 1)
        {
            before = before->next;
        }

        // Create the Node to populate it with Data
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        // Point at the Next Node after "Before" Node
        newNode->next = before->next;
        // Before Node point at New Node
        before->next = newNode;

        return 1;
    }

}

int recursive_InsertNode(ListNode **ptrHead, int *index_variable, int index, int item)
{
    // Base Case
    if (*index_variable == 1)   // 1 because we need to put the New Node, 1 node before the index.
    {
        ListNode *newNode;
        // Initialize the New Node and Assign Data
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        
        // Point at After Node
        newNode->next = (*ptrHead)->next;
        // Before Node points at New Node
        (*ptrHead)->next = newNode;

        return 0;
    }   
    
    else 
    {
        *ptrHead = (*ptrHead)->next;
        *index_variable -= 1;
        recursive_InsertNode(ptrHead, index_variable, index, item);
        return 0;
    }
}