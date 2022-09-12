#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

enum ExpType {OPT,OPERAND};

typedef struct _queueNode
{
    int item;
    enum ExpType type;
    struct _queueNode *next;
}QueueNode;

typedef struct _queue{
    int size;
    QueueNode *head;
    QueueNode *tail;
}Queue;

void enqueue (Queue *qptr, int item, enum ExpType type);
int dequeue(Queue *qPtr);
QueueNode* getFront(Queue q);
int isEmptyQueue(Queue q);

void expressionQ(char *infix, Queue* qPtr);
void printExpQ(Queue* qPtr);

int main()
{
    char infix[SIZE];
    scanf("%[^\n]%*c",infix);

    Queue inExpQ;
    inExpQ.head = NULL;
    inExpQ.tail = NULL;
    inExpQ.size = 0;

    expressionQ(infix,&inExpQ);
    printf("Output:\n");
    printExpQ(&inExpQ);

    return 0;
}

void enqueue (Queue *qPtr, int item, enum ExpType type)
{
    QueueNode *newNode;
    newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->type = type;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail =newNode;
    qPtr->size++;

}
int dequeue(Queue *qPtr)
{
    if(qPtr == NULL || qPtr->head ==NULL)
        return 0;
    else{
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;

        if(qPtr->head == NULL)
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

QueueNode* getFront(Queue q)
{
    return q.head;
}

int isEmptyQueue(Queue q){
   if(q.size==0) return 1;
    else return 0;
}

void printExpQ(Queue *qPtr){
    if(qPtr==NULL) return;

    QueueNode* temp = NULL;
    temp = getFront(*qPtr);

    while(temp!=NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        dequeue(qPtr);
        temp = getFront(*qPtr);
    }
    printf("\n");

}

void expressionQ(char *infix, Queue* qPtr)
{
    // Iterate through the entire string until NULL
    char *cursor = infix;
    while (*cursor)
    {
        // Separate Pointer to Point at Cursor
        int temp = (int) *cursor;
        int digit_length = 0;
        // String to place multi-digit numbers
        char buffer[100];
        // Determine if the Current Char is a Digit
        if ((temp >= '0') && (temp <= '9'))
        {
            int multi_digit_num = 0;

            // Use sscanf to get the Multi-Digit Number
            sscanf(cursor, "%d", &multi_digit_num);
            // Convert Multi-Digit Number into a String to get Digit Length
            sprintf(buffer, "%d", multi_digit_num);
            digit_length = strlen(buffer);

            // Is a Digit; Add to Queue
            enqueue(qPtr, multi_digit_num, OPERAND);
            cursor += digit_length;
            // Skip to the next loop to prevent cursor += 1 from running
            continue;
        }

        // Determine if Operator
        else if ((temp == 43) || (temp == 45) || (temp == 42) || (temp == 47) || (temp == 37) || (temp == 40) || (temp == 41))
        {
            // Is a Operator
            enqueue(qPtr, (char) *cursor, OPT);
        }
        // Cursor needs to be outside because of brackets
        cursor += 1;
    }
}