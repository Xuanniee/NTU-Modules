#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct _listNode{
    int item;
    struct _listNode* next;
};

typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);
void separate_linked_list(ListNode **original_list, ListNode **first_linked_list, ListNode **second_linked_list, int ll_length);
LinkedList rearrange (LinkedList ll);
void combine_linked_list(ListNode **original_list, ListNode *left_linked_list, ListNode *right_linked_list);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll)
{
    // Determine the Length of the Linked List
    int ll_length = ll.size;
    ListNode *head_ptr = ll.head;

    // Input Validation
    if (ll_length == 0)
    {
        return ll;
    }
    else if (ll_length == 1)
    {
        return ll;
    }

    // Create 2 Linked Lists
    ListNode *left_ll = NULL, *right_ll = NULL;

    // Separate the Linked List into 2 Lists
    separate_linked_list(&head_ptr, &left_ll, &right_ll, ll_length);
   
    // Rearrange the 2 Linked List into 1 Linked List
    // Left then Right Linked List
    combine_linked_list(&head_ptr, left_ll, right_ll);

    // Separate the Linked List into 2 Lists again
    separate_linked_list(&head_ptr, &left_ll, &right_ll, ll_length);
    
    // Combine the 2 Linked Lists tgh again
    // Second Time is Right then Left Linked List
    combine_linked_list(&head_ptr, right_ll, left_ll);

    // Return the Linked List
    return ll;
}

void combine_linked_list(ListNode **original_list, ListNode *left_linked_list, ListNode *right_linked_list)
{
    // Create Head & Traversing Pointers for the 3 Linked List
    ListNode *original_head = *original_list, *original_cursor = *original_list;
    ListNode *left_head = left_linked_list;
    ListNode *right_head = right_linked_list;
    ListNode *left_cursor = left_head, *right_cursor = right_head;

    // Combine
    while (true)
    {
        if (right_cursor != NULL)
        {
            // Start from Right Linked List. Overwrite the Value
            original_cursor->item = right_cursor->item;

            // Move Pointers
            original_cursor = original_cursor->next;
            right_cursor = right_cursor->next;
        }

        if (left_cursor != NULL)
        {
            // Overwrite using Left LL
            original_cursor->item = left_cursor->item;

            // Move the Pointers
            original_cursor = original_cursor->next;
            left_cursor = left_cursor->next;
        }

        // Break Condition
        if ((left_cursor == NULL) && (right_cursor == NULL))
        {
            // Do I need to Make sure Last Node is NULL?
            break;
        }
    }
}

void separate_linked_list(ListNode **original_list, ListNode **first_linked_list, ListNode **second_linked_list, int ll_length)
{
    // Determining if Number of Nodes is Even or Odd
    int first_ll_num_nodes = 0;
    if ((ll_length % 2) == 0)
    {
        first_ll_num_nodes = (int) ll_length / 2;
    }
    else
    {
        // Round Down the Quotient as Second List must have an additional node
        first_ll_num_nodes = (int) floor(ll_length / 2);
    }

    // Separating Linked List
    bool first_node = true;
    ListNode *cursor = *original_list;
    ListNode *left_ll = *first_linked_list, *left_cursor = *first_linked_list;
    ListNode *right_ll = *second_linked_list, *right_cursor = *second_linked_list;

    // Left Linked List
    while (first_ll_num_nodes != 0)
    {
        // Creating a New Node
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->item = cursor->item;
        newNode->next = NULL;

        if (first_node == true)
        {
            // Connect New Node
            left_ll = newNode;
            left_cursor = left_ll;
            first_ll_num_nodes -= 1;

            // Move Source Pointer to Next Node
            cursor = cursor->next;

            // Change the IF Condition
            first_node = false;
        }

        else
        {
            // Adding newNode to the Linked List and Moving the Cursor forward
            left_cursor->next = newNode;
            left_cursor = left_cursor->next;
            first_ll_num_nodes -= 1;

            // Move Source Pointer to Next Node
            cursor = cursor->next;
        }
    }

    // Right Linked List
    first_node = true;
    while (cursor != NULL)
    {
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->item = cursor->item;
        newNode->next = NULL;

        if (first_node == true)
        {
            // Connect New Node
            right_ll = newNode;
            right_cursor = right_ll;

            // Move Source Pointer to Next Node
            cursor = cursor->next;

            // Change the IF Condition
            first_node = false;
        }

        else
        {
            // Adding newNode to the Linked List and Moving the Cursor forward
            right_cursor->next = newNode;
            right_cursor = right_cursor->next;

            // Move Source Pointer to Next Node
            cursor = cursor->next;
        }
    }
    // Update the Head Pointers
    *first_linked_list = left_ll;
    *second_linked_list = right_ll;
}
