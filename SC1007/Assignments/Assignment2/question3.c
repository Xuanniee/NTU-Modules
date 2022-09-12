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

int non_adjacent_pairs(int hmin, CDblListNode *middle_mountains, CDblListNode *target_mountain);
int numMountainPairs(CDblLinkedList CDLL);

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

int numMountainPairs(CDblLinkedList CDLL)
{
    // Input Validation
    if (CDLL.size == 0)
    {
        return 0;
    }
    // Count the Number of Adjacent Mountains
    int num_visible_pairs = CDLL.size;

    // Determine the Number of Visible Non-Adjacent Mountains
    CDblListNode *first_mountain = CDLL.head;
    // Ensure Second Pointer points at non-adjacent mountain
    CDblListNode *sec_mountain = NULL;
    CDblListNode *cursor = NULL;

    // Loop in the Clockwise Direction
    int hmin = 0;
    for (int j = 0; j < (CDLL.size); j += 1)
    {
        // Ensure Target Mountain is Not Adjacent
        sec_mountain = (first_mountain->next)->next;
        // Set Cursor to point at First Node after Marking Mountain (first_mountain)
        cursor = first_mountain->next;

        // Loop until the Target Mountain is the first_mountain again
        while(sec_mountain != first_mountain)
        {
            // Get the Min of the 2 Mountains
            if (first_mountain->item > sec_mountain->item)
            {
                hmin = sec_mountain->item;
            }
            else
            {
                hmin = first_mountain->item; 
            }

            // Check & Add if mountains are non-adjacent and visible
            if ((first_mountain->next != sec_mountain) && (first_mountain->pre != sec_mountain))
            // if (first_mountain->item < sec_mountain->item)
            {
                num_visible_pairs += non_adjacent_pairs(hmin, cursor, sec_mountain);
            }

            // Continue Changing Targets so long as Not Adjacent with first_mountain
            if (sec_mountain->next != first_mountain->pre)
            {
                // Continue comparing with first_mountain; but change the target mountain to a further one
                sec_mountain = sec_mountain->next;
            }
            // Compared all the mountains with CURRENT first_mountain
            // else if ((sec_mountain->next == first_mountain) && (sec_mountain->pre == first_mountain))
            // {
            //     break;
            // }
            else
            {
                break;
            }
        }
        // Update the first_mountain (marking mountain)
        first_mountain = first_mountain->next;

    }
    
    return num_visible_pairs;
}

int non_adjacent_pairs(int hmin, CDblListNode *middle_mountains, CDblListNode *target_mountain)
{
    // Check if there are non-adjacent visible pairs
    CDblListNode *cursor = middle_mountains;
    int non_adjacent_visible_pairs = 0;
    while (true)
    {
        // Checking if Middle Mountains' Heights are Greater than Hmin
        if (cursor->item > hmin)
        {
            return 0;
        }
        // Move to Next Mountain
        cursor = cursor->next;
        
        if (cursor == target_mountain)
        {
            break;
        }
    }
    printf("These are the Mountains (%d, %d)\n", (middle_mountains->pre)->item, target_mountain->item);
    non_adjacent_visible_pairs += 1;
    return non_adjacent_visible_pairs;
}