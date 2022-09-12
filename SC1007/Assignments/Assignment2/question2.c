// Infix to Prefix Linked List
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void reverse(char array[30]) // for reverse of the given expression 
{
	int i,j;
	char temp[100];
	for (i=strlen(array)-1,j=0;i+1!=0;--i,++j) {
		temp[j]=array[i];
	}
	temp[j]='\0';
	strcpy(array,temp);
	return;
}

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

    // Reverse the String
    // char tmp;
    // int output[infix_length + 1];
    // int indexI = infix_length;
    // int tail_num = 0, head_num = 0;
    // for (int i = 0; i < infix_length; i += 1)
    // {
    //     sscanf(tail, "%d", &tail_num);
    //     output[i] = tail_num;
    //     output[indexI] = (int) *head;

    //     head ++;
    //     tail --;
    //     indexI --;
    // }
    reverse(infix);

    printf("This is reversed %s\n", infix);

    // Create a Stack to store all the Operators
    Stack *sPtr = (Stack*) malloc(sizeof(Stack));
    (*sPtr).size = 0;
    (*sPtr).head = NULL;

    // Scan the reversed expression from Left to Right
    char num_as_string[50];
    ListNode *cursor = (inExpLL->head);
    // Scan and Push all Operands into the Output
    printf("This is: %s\n", infix);
    while (*infix)
    {   
        int multi_digit_num = 0, digit_length = 0;
        // Check if Operand
        if ((*infix >= '0') && (*infix <= '9'))
        {
            // Scan the Number into the int
            sscanf(infix, "%d", &multi_digit_num);
            // Determine Length of int
            sprintf(num_as_string, "%d", multi_digit_num);
            
            int copy = multi_digit_num;
            while(copy > 1)
            {
                // Determine Number of Digits
                copy /= 10;
                digit_length += 1;
            }

            // Save the Number in the Output Expression
            ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
            newNode->item = multi_digit_num;
            newNode->next = NULL;
            newNode->type = OPERAND;

            if (isEmptyLinkedList(*inExpLL) == 1)
            {
                // Empty Linked List
                // Add new List Node into our Linked List and Update size
                (*inExpLL).head = newNode;
                cursor = newNode;
                inExpLL->size = 1;
            }
            else
            {
                // Not Empty Linked List
                cursor->next = newNode;
                cursor = cursor->next;
                inExpLL->size += 1;
            }
            // Move the Pointer to the Next Operator
            infix += digit_length;
            continue;
        }

        // Must be Operator or Brackets
        // Not equal to Brackets ((*infix) != ')' && (*infix) != '(')
        else
        {
            // Check if the Stack contains any Operator
            if ((isEmptyStack(*sPtr) == 1) || (*infix == '('))
            {
                // Empty Stack; Add Operator
                push(sPtr, *infix);
            }
            else
            {
                // Check if Existing Operator has a Higher Precedence
                if ((optPrecedence(*infix) > optPrecedence(peek(*sPtr))))
                {
                    // Existing has Higher --> Push to Stack
                    push(sPtr, *infix);
                }

                // Bracket Precedence
                else if (*infix == ')')
                {
                    while(peek(*sPtr) != '(')
                    {
                        // Add to Output
                        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
                        newNode->item = peek(*sPtr);
                        newNode->next = NULL;
                        newNode->type = OPT;

                        cursor->next = newNode;
                        cursor = cursor->next;
                        inExpLL->size += 1;
                        pop(sPtr);
                    }
                    // Remove the Bracket
                    pop(sPtr);
                }

                // Lower or Equal Precedence
                else if ((optPrecedence(*infix) <= optPrecedence(peek(*sPtr))))
                {
                    // Stack has Higher Operator --> Pop everything out of Stack & into Output. 
                    while(isEmptyStack(*sPtr) != 1)
                    {
                        // Add to Output
                        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
                        newNode->item = peek(*sPtr);
                        newNode->next = NULL;
                        newNode->type = OPT;

                        if (isEmptyLinkedList(*inExpLL) != 1)
                        {
                            cursor->next = newNode;
                            cursor = cursor->next;
                        }
                        else
                        {
                            cursor = newNode;
                        }
                        inExpLL->size += 1;
                       
                        // Remove Head of Stack
                        pop(sPtr);
                    }
                    // Push Existing into Stack after Popping
                    push(sPtr, *infix);

                }
            }

        }
        // Move the Pointer to skip the Bracket
        infix += 1;
    }

    // Ensure Stack is Empty
    while (isEmptyStack(*sPtr) == 0)
    {
        if ((*infix) != ')' && (*infix) != '(')
        {
            ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
            newNode->item = peek(*sPtr);
            newNode->next = NULL;
            newNode->type = OPT;

            cursor->next = newNode;
            cursor = cursor->next;
            inExpLL->size += 1;
        }
        pop(sPtr);
    }


    // Swap Function to reverse the string
    ListNode *cursorLL = inExpLL->head;
    ListNode *prev = NULL, *next = NULL;

    while (cursorLL != NULL)
    {
        // Save the Next Node
        next = cursorLL->next;
        // Reverse
        cursorLL->next = prev;
        // Move Pointers
        prev = cursorLL;
        cursorLL = next;
    }
    // Update the Head Pointer
    inExpLL->head = prev;
}