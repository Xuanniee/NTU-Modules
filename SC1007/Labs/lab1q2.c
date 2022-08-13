#include <stdlib.h> // malloc() free()
#include <stdio.h>  // scanf()
#include <stdbool.h>    // For Booleans
#include <ctype.h>  // For isdigit()

typedef struct listnode
{
    int data;
    struct listnode *next; 
}ListNode;

typedef struct _linkedlist
{
    ListNode *head;
    int size;
} LinkedList;

int removeNode2(LinkedList **ll, int index);
void printLinkedList(ListNode *cursor, ListNode *head);

int main(void)
{
    int counter = 0;
    LinkedList *numeric_ll = (LinkedList*) malloc(sizeof(LinkedList)); 
    numeric_ll->head = (ListNode*) malloc(sizeof(ListNode));
    ListNode *cursor = numeric_ll->head;

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
            (numeric_ll->head)->data = (int) node_value;
            (numeric_ll->head)->next = NULL;
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
            counter += 1;
        }
    }

    // Set Length of Linked List
    numeric_ll->size = counter;
    
    // Print the Linked List
    printLinkedList(cursor, (numeric_ll->head));

    // Remove Node Loop
    while(true)
    {
        int index_removed = 0;
        printf("Enter the index of the node to be removed: ");
        scanf("%i", &index_removed);

        removeNode2(&numeric_ll, index_removed);
        printLinkedList(cursor, (numeric_ll->head));
    }

    return 0;

}

int removeNode2(LinkedList **ll, int index)
{
    // Validate not removing outside
    int ll_size = (*ll)->size;
    ListNode *headptr = (*ll)->head;
    ListNode *afterHead = headptr->next;    //  To be removed

    if ((ll_size == index) || (index > ll_size))
    {
        printf("This node cannot be removed.\n");
        return 1;
    }

    while (index != 1)
    {
        // Remove First Node
        if (index == 0)
        {
            free(headptr);
            // Make Next Node the Head Node
            (*ll)->head = afterHead;
            (*ll)->size -= 1;
            printf("After the removal operation, \n");
            return 0;
        }
        // Traverse afterHead to the Node to be removed
        headptr = afterHead;
        afterHead = afterHead->next;
        index -= 1;
    }

    // Remove afterHead's Node
    headptr->next = afterHead->next;
    free(afterHead);
    // Update Linked List Size
    (*ll)->size -= 1;

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