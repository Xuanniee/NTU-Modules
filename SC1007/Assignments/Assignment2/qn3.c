#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);
int non_adjacent_pairs(int hmin, CDblListNode *marker_mountain, CDblListNode *target_mountain, bool clockwise);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}

int numMountainPairs(CDblLinkedList CDLL){
    // Initialize Pointers
    CDblListNode *marker = CDLL.head;
    CDblListNode *stop = marker;
    CDblListNode *target = marker->next;

    // Number of Loops for Distinct Marker
    int num_of_mountains = CDLL.size;
    int num_of_pairs = num_of_mountains;
    int hmin = 0;
    int placeholder = 0;
    int loop_counter = 0;
    bool clockwise = true;

    // Input Validation
    if (num_of_mountains == 1)
    {
        return 0;
    }
    else if (num_of_mountains == 2)
    {
        return 1;
    }

    // For Loop to Loop through all the Mountains ONCE
    for (int i = 0; i < num_of_mountains; i += 1)
    {
        // Changing the Second Number of the Pair
        while (true)
        {
            // Break Condition
            if (target == stop)
            {
                loop_counter += 1;
                target = marker->next;
                break;
            }
            else if (loop_counter == (num_of_mountains - 1))
            {
                loop_counter = 0;
                break;
            }
            // Check if Adjacent
            else if ((target == marker->next) || (target == marker->pre) || (target == marker))
            {
                // Move Second Number of Pair if Adjacent
                target = target->next;
                continue;
            }

            // Determine Minimum Height
            if (marker->item > target->item)
            {
                hmin = target->item;
            }
            else
            {
                hmin = marker->item;
            }

            // Check if Visible in Clockwise Direction
            clockwise = true;
            placeholder = non_adjacent_pairs(hmin, marker, target, clockwise);

            // Check if Visible in AntiClockwise Direction
            if (placeholder == 0)
            {
                clockwise = false;
                placeholder = non_adjacent_pairs(hmin, marker, target, clockwise);
            }
            
            // Add to Pairs
            num_of_pairs += placeholder;
            // Reset Placeholder
            placeholder = 0;

            // Move the Target to the Next Mountain
            target = target->next;
        }
        
        // Move the Marker Mountain
        marker = marker->next;
    }
    return num_of_pairs;
}


int non_adjacent_pairs(int hmin, CDblListNode *marker_mountain, CDblListNode *target_mountain, bool clockwise)
{
    // Check if there are non-adjacent visible pairs
    CDblListNode *cursor = NULL;
    if (clockwise == true)
    {
        cursor = marker_mountain->next;
    }
    else if (clockwise == false)
    {
        cursor = marker_mountain->pre;
    }
    int non_adjacent_visible_pairs = 0;

    while (true)
    {
        // Checking if Middle Mountains' Heights are Greater than Hmin
        if (cursor->item > hmin)
        {
            return 0;
        }
        // Move to Next Mountain
        if (clockwise == true)
        {
            cursor = cursor->next;
        }
        else
        {
            cursor = cursor->pre;
        }
        
        if (cursor == target_mountain)
        {
            break;
        }
    }
    non_adjacent_visible_pairs += 1;
    return non_adjacent_visible_pairs;
}