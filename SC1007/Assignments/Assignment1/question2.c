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

    // Input Validation
    if (!(*head))
    {
        return;
    }
    else if (K > ll_length)
    {
        return;
    } 
    else if (K == 1)
    {
        return;
    }
    else if (K==0)
    {
        return;
    }
    

	// Initialize Pointers for Segments
	ListNode *segment_prev = NULL;
	ListNode *segment_next = NULL;
	ListNode *first_node = *head;
	ListNode *linking_cursor_front = NULL, *linking_cursor_back = NULL;
    int temp_ll_length = ll_length;

    // As long as the Linked List can be segmented
    while (true)
    {
        // Reverse within the Segment
        for (int i = 0; i < K; i += 1)
        {
            // Save the Next Node
            segment_next = first_node->next;
            // Reverse
            first_node->next = segment_prev;
            // Move the Pointers
            segment_prev = first_node;
            first_node = segment_next;
            
        }
        // Since Next and First_Node [Current] are Pointing at the same thing.
        if (segment_next != NULL)
        {
            segment_next = segment_next->next;
        }        
        // Update the New First Node
        if (temp_ll_length == ll_length)
        {
            // First Reverse
            // Connect with Rest of Linked List
            (*head)->next = first_node;
            // Remember End of Segment
            linking_cursor_front = (*head);
            // Remember Start of Next Segment
            linking_cursor_back = first_node;
            // Update Head
            *head = segment_prev;
        }
        else
        {
            // Connect with Earlier Portion of Linked List
            linking_cursor_front->next = segment_prev;
            // Connect Segment with Rest of Linked List
            linking_cursor_back->next = first_node;

            // Update Linking Pointers
            linking_cursor_front = linking_cursor_back;
            linking_cursor_back = linking_cursor_front->next;
        }
        
        // Update Remaining the Number of Nodes
        temp_ll_length -= K;
        
        if (temp_ll_length < K)
        {
            break;
        }
    }
}

