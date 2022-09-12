// Infix to Prefix Linked List
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 // Size of Array

enum ExpType {OPT, OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);

void in2PreLL(char *infix, LinkedList *inExpLL);
void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    scanf("%[^\n]%*c", infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);
    printExpLL(inExpLL);

    //removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while(temp!=NULL)
    {
        if(temp->type == OPERAND)
        {
            printf(" %d ", temp->item);
        }
        else
        {
            printf(" %c ", (char)(temp->item));
        }
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *llPtr, int item, enum ExpType type)
{
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = llPtr->head;
    llPtr->head=newNode;
    llPtr->size++;
}

int deleteNode(LinkedList *llPtr)
{
    if(llPtr==NULL || llPtr->size==0){
        return 0;
    }
    else{
        ListNode *temp = llPtr->head;

        llPtr->head = llPtr->head->next;

        free(temp);
        llPtr->size--;
        return 1;
    }
}

void removeAllNodes(LinkedList *llPtr)
{
    while(deleteNode(llPtr));
}

int isEmptyLinkedList (LinkedList ll)
{
    if(ll.size==0) return 1;
    else return 0;
}

void push(Stack *sPtr, char item)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}
char peek(Stack s)
{
    return s.head->item;
}

int isEmptyStack(Stack s)
{
    if(s.size == 0) return 1;
    else return 0;
}

// Operator Precedence Function
int optPrecedence(char a)
{
    // The Higher the Value, the Higher the Precedence
    switch(a)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
void swap(char *head, char *tail)
{
    char tmp = *head;
    *head = *tail;
    *tail = tmp;
}
void in2PreLL(char* infix, LinkedList *inExpLL)
{
    // Reverse the String
    int infix_length = 0;

    // Set the Head and Tail Pointers
    char *head = infix;
    char *tail = NULL;
    while(*head != '\0')
    {
        if (*head == '(')
        {
            *head = ')';
        }
        else if (*head == ')')
        {
            *head = '(';
        }
        head += 1;
        infix_length += 1;
        if (*head != '\0')
        {
            tail = head;
        }
    }
    head = infix;

    // Swap Function to reverse the string
    for (int i = 0; i < (infix_length/2); i += 1)
    {
        // Swap the Head and Tail
        swap(head, tail);
        // Move the Pointers
        head += 1;
        tail -= 1;
    }
    printf("%s", infix);

    

}