#include <stdlib.h> // malloc() free()
#include <stdio.h>  // scanf()
#include <stdbool.h>    // For Booleans
#include <ctype.h>  // For isdigit()

typedef struct listnode
{
    int data;
    struct listnode *next; 
}ListNode;

int removeNode(ListNode **ptrHead, int index);
void printLinkedList(ListNode *cursor, ListNode *head);

int main(void)
{
    int counter = 0;
    ListNode *head = (ListNode*) malloc(sizeof(ListNode));
    ListNode *cursor = head;

    // Collect User Input for Linked List
    printf("Enter a list of numbers, terminated by any non-digit character:\n");
    while(true)
    {
        char node_value;
        scanf(" %c", &node_value);      // Gets rid of Whitespace

        // Validate to ensure User Input is an Int
        if (isdigit(node_value) == false)
        {
            // Character provided; Break
            break;
        }

        // Create Head Node
        if(counter == 0)
        {
            head->data = (int) node_value;
            head->next = NULL;
            counter += 1;
        }

        else
        {
            ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
            newNode->data = (int) node_value;
            newNode->next = NULL;
            cursor->next = newNode;

            // Move the Cursor Pointer to the Newly Created Node
            cursor = cursor->next;
        }
    }
    
    // Print the Linked List
    printLinkedList(cursor, head);

    // Remove Node Loop
    while(true)
    {
        int index_removed = 0;
        printf("Enter the index of the node to be removed: ");
        scanf("%i", &index_removed);

        removeNode(&head, index_removed);
        printLinkedList(cursor, head);
    }

    return 0;

}

int removeNode(ListNode **ptrHead, int index)
{
    // Points at the same node
    ListNode *after = (*ptrHead)->next;
    ListNode *current = (*ptrHead);
    int index_copy = index;

    if(index != 0)
    {
        index -= 1;     // Since After is to be removed
    }
    while(index != 0)
    {
        // Validate that User did not try to remove node outside of Linked List
        if(current->next == NULL)
        {
            printf("The node cannot be removed.\n");
            return 1;
        }
        // Pointer After will point at the node to be Removed
        current = after;
        after = after->next;
        index -= 1;
    }

    // Validate that User did not try to remove node outside of Linked List
    if(current->next == NULL)
    {
        printf("The node cannot be removed.\n");
        return 1;
    }

    // Start of Linked Lists
    if(index_copy == 0)
    {
        free(current);          // Only time we free current instead
        // Point to Second Node
        (*ptrHead) = after;
    }

    // End of Linked Lists
    else if(after == NULL)
    {   
        current->next = NULL;
        free(after);
    }

    // Middle of Linked Lists
    else
    {
        // *ptrHead will point at node after Pointer After
        current->next = after->next;
        // Free the Node that is deleted
        free(after);
    }
    printf("After the removal operation, \n");
    return 0;
}

void printLinkedList(ListNode *cursor, ListNode *head)
{
    printf("Current List: ");
    cursor = head;
    while(cursor != NULL)
    {
        printf("%c ", cursor->data);
        cursor = cursor->next;
    }
    printf("\n");   // Newline
}