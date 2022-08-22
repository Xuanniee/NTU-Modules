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

	// Traversing Pointer
	int current_node = 0;
	ListNode *cursor = head;
	ListNode *prev_node, *next_node = NULL;
	ListNode *before_start, *after_end;
	ListNode *reversed_list = NULL;

	// Record Address of Before Start & After End
	while (current_node != start)
	{
		// Move to the Next Node
		cursor = cursor->next;
		current_node += 1;

		// Save the First Half of Original Linked List
		if (current_node == (start - 1))
		{
			before_start = cursor;
		}
	}
	while (current_node != end)
	{
		// Move to Next Node
		cursor = cursor->next;
		current_node += 1;

		// Save the Third Half of the Original Linked List
		if (current_node == (end + 1))
		{
			after_end = cursor->next;
		}
	}
	// Pointer at Original End of Segmented List
	reversed_list = cursor;

	// Move the 3 Pointers to Starting Positions [Other 2 in Position]
	cursor = before_start->next;
	prev_node = NULL;
	next_node = cursor->next;

	// Break Condition
	current_node = start;

	// Reverse the Segmented Linked List
	while (true)
	{
		// Reverse the Nodes
		cursor->next = prev_node;
		
		// Move the 3 Pointers
		prev_node = cursor;
		cursor = next_node;
		if (next_node->next != NULL)
		{
			next_node = next_node->next;
		}


		current_node += 1;
		if (current_node == end)
		{
			break;
		}
	}

	// Append the Reversed Linked List within Before Start & After End
	before_start->next = reversed_list;
	cursor->next = after_end;

	return head;
}





















