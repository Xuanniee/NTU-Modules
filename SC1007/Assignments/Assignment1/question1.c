#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Defining a New Node Data Type
struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

// Function Prototypes
void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);


int main()
{
	// Head Pointer at Null
    ListNode *head = NULL, *temp;

	// Get User Input
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);
	// Storing User Input into the Linked List
	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;	// Move to Next Node
		}
		temp->item = f;	// Storing Data
	}
	temp->next = NULL;	// Set End Pointer to Null

	// Function to Reverse the Linked List
	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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

// Need to add Input Validation
ListNode *reverseSegment(ListNode* head, int start, int end)
{
    // Input Validation
	int LL_length = 0;
	ListNode *length_counter = head;

	while (length_counter != NULL)
	{
		LL_length += 1;
		length_counter = length_counter->next;
	}
	if (start < 0)
	{
		// Quit the Function without changing anything
		return head;
	}
	else if (end > (LL_length - 1))
	{
		// Quit the Function without changing anything
		return head;
	}
    else if (start > end)
    {
        // Illegal
        return head;
    }

    // Create Node Pointers
    ListNode *prev_node = NULL, *before_start = NULL, *after_end = NULL, *reversed_list_head = NULL, *reversed_list_tail = NULL, *next_node = NULL;
    ListNode *curr_node = head;

    // Move the Current Node until the Start Node
    int current_node_num = 0;
    while (current_node_num != start)
    {
        // Save the Node before Start Node
        if (current_node_num == (start - 1))
        {
            before_start = curr_node;
        }
        // Move the Node
        curr_node = curr_node->next;
        current_node_num += 1;
    }
    // Save the Tail Node after Reversing
    next_node = curr_node;
    reversed_list_tail = curr_node;

    // Start Reversing the Linked List
    while (current_node_num != (end+1))
    {
        // Save the Start of Reversed List and After End Node
        if (current_node_num == end)
        {
            reversed_list_head = curr_node;
            after_end = curr_node->next;
        }
        // Save the Next Node before reversing
        next_node = curr_node->next;

        // Reverse the Node
        curr_node->next = prev_node;

        // Move the remaining Pointers
        prev_node = curr_node;
        curr_node = next_node;
        
        current_node_num += 1;
    }

    // Combine back into 1 Linked List
    if (start != 0)
    {
        // Connect Middle Segment with Top and Bottom of LL
        before_start->next = reversed_list_head;
        reversed_list_tail->next = after_end;
        return head;
    }  
    // Edge Case  
    else
    {
        // Change where the Head Pointer is pointing at
        head = reversed_list_head;
        reversed_list_tail->next = after_end;
        return head;
    }
    return head;
}