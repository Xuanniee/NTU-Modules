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

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

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


	reverseKNodes(&head, K);
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

void reverseKNodes(ListNode** head, int K)
{
    // Initialize a Dummy Node
	ListNode *dummy = (ListNode*) malloc(sizeof(ListNode));
	dummy->next = *head;
	
	// Determine the Length of the Linked List
	ListNode *cursor = *head;
	int ll_length = 0;
	while (cursor != NULL)
	{
		ll_length += 1;
		cursor = cursor->next;
	}

	// Initialize Pointers for Segments
	ListNode *segment_prev = dummy;
	ListNode *segment_next = NULL;
	ListNode *first_node = dummy;
	ListNode *last_node = dummy;

	while (true)
	{
		// Find the Last Node of a Segmented List
		for (int i = 0; i < K; i += 1)
		{
			if (last_node->next != NULL)
			{
				
			}
			last_node = last_node->next;
		}

		// Find the Next Node outside of Segment
		segment_next = last_node->next;

		// Find First Node of a Segmented List
		first_node = segment_prev->next;

		// Reverse the Segmented List
		ListNode *prev = NULL;
		ListNode *next = NULL;

		while (first_node != segment_next)
		{
			// Save the Next Node
			next = first_node->next;
			// Reverse the Node
			first_node->next = prev;
			// Move the Pointers
			prev = first_node;
			first_node = next;
		}

		// Combine the Linked Lists
		// Update the First Node of Segment to point at segment_next
		(segment_prev->next)->next= segment_next;
		segment_prev->next = last_node;

	}


}



/*
void reverseKNodes(ListNode** head, int K)
{
	// Initialize a Pointer to point at First Node
	ListNode *cursor = *head;
	// Determine the Length of the Linked List
	int ll_length = 0;
	while (cursor != NULL)
	{
		ll_length += 1;
		cursor = cursor->next;
	}

	// Create 3 Pointers to reverse the Segmented Linked List
	int num_nodes = ll_length;
	int first_segment = false;
	ListNode *pre_node = NULL;
    ListNode *current_node = *head;
    ListNode *next_node = NULL;
	ListNode *original_start = NULL, *original_end = NULL;
	while (current_node != NULL)
	{
		// Check Number of Nodes remaining
		if (num_nodes >= K)
		{
			// Reverse Segment
			original_start = current_node;
			for (int i = 0; i < K; i += 1)
			{
				// Save the Next List Node
				next_node = current_node->next;
				// Reverse the Node
				current_node->next = pre_node;
				// Move the remaining pointers forward
				pre_node = current_node;
				current_node = current_node->next;
			}
			
			// Connect Segment to Linked List
			if (first_segment == false)
			{
				*head = current_node;
				original_start->next = next_node;
				// Save the Node after Segment for Future Connections
				original_end = next_node;

				first_segment = true;
				// Break Condition
				num_nodes -= K;
			}
			else
			{
				original_end->next = current_node;
				original_start->next = next_node;
				original_end = next_node;

				// Break Condition
				num_nodes -= K;
			}
		}
		// Leave the Remaining Nodes alone and Combine
		else
		{
			return;
		}
		
		return;
	}
}*/