#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);
void bubble_sort(ListNode **head);
void swap_nodes(ListNode *current, ListNode *next);
void combine_linked_lists(ListNode **new_head, ListNode *smaller_ll, ListNode *larger_ll, int pivots[], int pivot_length);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

void triPartition(ListNode** head, int pivot)
{
    // Determine the Length of the Linked List
    int ll_length = 0;
    ListNode *cursor = *head;
    while (cursor != NULL)
    {
        ll_length += 1;
        cursor = cursor->next;
    }

    // Determine the Number of Elements with same value as Pivot
    int num_pivot = 0;
    cursor = *head;
    while (cursor != NULL)
    {
        if (cursor->item == pivot)
        {
            num_pivot += 1;
        }
        cursor = cursor->next;
    }

    // Create 2 Linked List [Larger than Pivot & Smaller than Pivot]
    int large_length = 0, small_length = 0;
    cursor = *head;
    ListNode *larger_head =  NULL;
    ListNode *cursor_larger = larger_head;
    bool set_head_ptr = false;

    // Larger Linked List
    while (cursor != NULL)
    {
        // Compare if Value Larger than Pivot
        if (cursor->item > pivot)
        {
            // Create New Node
            ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
            newNode->item = cursor->item;
            newNode->next = NULL;

            // Link with Linked List
            if (set_head_ptr == false)
            {
                // First Node
                set_head_ptr = true;

                // Set Head Pointer & Cursor to First Node
                larger_head = newNode;
                cursor_larger = larger_head;
                large_length += 1;
            }
            else
            {
                // Subsequent Nodes
                cursor_larger->next = newNode;
                cursor_larger = cursor_larger->next;
                large_length += 1;
            }
        }
        // Move the Copying Pointer
        cursor = cursor->next;
    }

    // Smaller Linked List
    cursor = *head;
    set_head_ptr = false;
    ListNode *smaller_head =  NULL;
    ListNode *cursor_smaller = smaller_head;
    while (cursor != NULL)
    {
        // Compare if Value Smaller than Pivot
        if (cursor->item < pivot)
        {
            // Create New Node
            ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
            newNode->item = cursor->item;
            newNode->next = NULL;

            // Link with Linked List
            if (set_head_ptr == false)
            {
                // First Node
                set_head_ptr = true;

                // Point at First Node
                smaller_head = newNode;
                cursor_smaller = smaller_head;
                small_length += 1;
            }
            else
            {
                // Subsequent Nodes
                cursor_smaller->next = newNode;
                cursor_smaller = cursor_smaller->next;
                small_length += 1;
            }
        }
        cursor = cursor->next;
    }

    // Create Array to store the Pivot Elements
    int pivot_array[num_pivot];
    for (int i = 0; i < num_pivot; i += 1)
    {
        pivot_array[i] = pivot;
    }

        // Check the Pivot is created properly


    // Delete the Original List [Later]

    // Bubble Sort the Larger and Smaller Linked List
    // bubble_sort(&larger_head);
    // bubble_sort(&smaller_head);

    // Create a New List using the 3 Linked Lists
    ListNode *newList = NULL;
    combine_linked_lists(&newList, smaller_head, larger_head, pivot_array, num_pivot);

    // Assign the Head to New List for "Return"
    *head = newList;
    return;
}

void bubble_sort(ListNode **head)
{
    // Another Pointer to Head of Linked List
    ListNode *cursor = *head;
    if (cursor == NULL)
    {
        return;
    }

    // Compare 2 Consecutive Nodes
    ListNode *current_ptr = cursor;
    ListNode *next_ptr = NULL;
    int num_swaps = 0;
    while (true)
    {
        num_swaps = 0;
        // Save the Next Node
        next_ptr = current_ptr->next;
        if (next_ptr != NULL)  //next_ptr causing the seg fault - (next_ptr->item) < (current_ptr->item)
        {
            // Swap the Item Values if not in ascending order
            num_swaps += 1;
            swap_nodes(current_ptr, next_ptr);
        }

        // Break Condition
        if (num_swaps == 0)
        {
            break;
        }

        // Move to the Next Nodes
        current_ptr = next_ptr;
        next_ptr = next_ptr->next;
    }
}

void swap_nodes(ListNode *current, ListNode *next)
{
    // Create a Temp Variable
    int temp_var = 0;
    
    // Swap
    temp_var = next->item;
    next->item = current->item;
    current->item = temp_var;
    
    return;
}

void combine_linked_lists(ListNode **new_head, ListNode *smaller_ll, ListNode *larger_ll, int pivots[], int pivot_length)
{
    ListNode *temp_head = NULL, *temp_head_cursor = NULL;
    ListNode *cursor_L = larger_ll;
    ListNode *cursor_S = smaller_ll;

    int first_node = 0;
    ListNode *last_ptr = NULL;
    while (cursor_S != NULL)
    {
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->item = cursor_S->item;
        newNode->next = NULL;
        
        if (cursor_S->next == NULL)
        {
            // Save the Last Node
            last_ptr = cursor_S;
        } 

        // First Node
        if (first_node == 0)
        {
            temp_head = newNode;
            temp_head_cursor = temp_head;
            first_node += 1;

            // Move the Pointer
            cursor_S = cursor_S->next;
        }
        // Subsequent Nodes
        else
        {
            // Link to Next Node
            temp_head_cursor->next = newNode;
            temp_head_cursor = temp_head_cursor->next;

            // Move Pointer
            cursor_S = cursor_S->next;
        }
    }
    // Add Pivots to the Linked List
    for (int i = 0; i < pivot_length; i += 1)
    {
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->item = pivots[i];
        newNode->next = NULL;

        temp_head_cursor->next = newNode;
        temp_head_cursor = temp_head_cursor->next;
    }

    // Add Larger Linked List
    while (cursor_L != NULL)
    {
        if (cursor_L->next == NULL)
        {
            // Save the Last Node
            cursor_L = cursor_L;
        }

        // Creating a New Node
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->item = cursor_L->item;
        newNode->next = NULL;

        // Subsequent Nodes
        temp_head_cursor->next = newNode;
        temp_head_cursor = temp_head_cursor->next;

        // Move Pointer
        cursor_L = cursor_L->next;
    }
    // Reassign Head
    *new_head = temp_head;
    return;

}