#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

typedef struct _queue{
    int size;
    StackNode *head;
    StackNode *tail;
}Queue;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
        {
            printf(" %i ",temp->item);
        }
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

// Operator Precedence Function
int optPrecedence(char op)
{
    if(op == '-' || op == '+')
        return 1;
    else if(op == '*' || op == '/')
        return 2;
    else if(op == '^')
        return 3;
    else return 0;
}

// Need to strip Whitespace and when atoi(zero) as 980 becomes 089
void in2PreLL(char* infix, LinkedList *inExpLL)
{
    // Reverse the infix expression
    int infix_length = 0;
    int temp_no = 0;

    // Set the Head and Tail Pointers
    char *head = infix;
    char *tail = head;
    while(*head != '\0')
    {
        head += 1;
        infix_length += 1;
        if (*head == '(')
        {
            *head = ')';
        }
        else if (*head == ')')
        {
            *head = '(';
        }
        if (*head == '\0')
        {
            tail = head - 1;
        }
    }    
    head = infix;
    head -= 1;
    *head = '\0';
    
    // Step 2 - Convert to Almost Postfix
    Stack *sPtr = (Stack*) malloc(sizeof(Stack));
    sPtr->size = 0;
    sPtr->head = NULL;

    // Iterate over every Char in Reversed Expression
    ListNode *cursor = (inExpLL->head);
    infix = tail;
    int nDigits = 0;
    int operands_array[infix_length];
    int operandIndex = 0;
    char num_as_string[50];
    char *reverseDigit = NULL;
    // Linked List need Output as Int
    int llItem = 0;
    while (*infix)
    {
        int multi_digit_num = 0;
        // Operand
        if (isdigit(*infix) == 1)
        {
            while (isdigit(*infix) == 1)
            {
                infix -= 1;
            }
            infix += 1;
            // Extract the Operand as an int
            multi_digit_num = atoi(infix);

            // Insert a Char into the List Node as a PlaceHolder
            insertNode(inExpLL, multi_digit_num, OPERAND);
        }
        else if (*infix == ')')
        {
            while (peek(*sPtr) != '(')
            {
                llItem = (int) peek(*sPtr);
                insertNode(inExpLL, llItem, OPT);
                pop(sPtr);
            }
            // Remove the Additional '('
            pop(sPtr);
        }
        else if (*infix == '(')
        {
            // Push Parentheses
            push(sPtr, *infix);
        }
        else
        {
            while (((isEmptyStack(*sPtr) != 1) && (peek(*sPtr)) != '(') && (optPrecedence(peek(*sPtr)) > optPrecedence(*infix)))
            {
                // Push to Postfix Expression
                if((peek(*sPtr)=='*' || peek(*sPtr)=='/') && (*infix == '+' || *infix == '-'))
                {
                    insertNode(inExpLL, peek(*sPtr), OPT);
                    pop(sPtr);
                }
                else
                {
                    break;
                }
            }
            // Add lower precedence Operators in
            push(sPtr, *infix);
        }
        infix -= 1;
    }

    // Pop remaining Operators
    while (sPtr->head != NULL)
    {   
        llItem = (int) peek(*sPtr);
        insertNode(inExpLL, llItem, OPT);
        pop(sPtr);
    }
    return;

}

