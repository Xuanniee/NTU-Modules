#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);
int traversalCost(BTNode **node, int targetValue, int traversal_path[SIZE], int *index, int *num_traversals);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}
void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%i",cur->nodeV);
    inOrder(cur->right);
}

int traversalCost(BTNode **node, int targetValue, int traversal_path[SIZE], int *index, int *num_traversals)
{
    int traversal_cost = 0;
    int left_cost = 0, right_cost = 0;
    BTNode *cursor = *node;

    // Add the Toll Cost of Target
    traversal_cost += (cursor->nodeV);

    // Base Case
    if ((cursor->nodeV) == targetValue)
    {
        return traversal_cost;
    }
    // If it is a leaf node
    else if ((cursor->left == NULL) && (cursor->right == NULL))
    {
        return -1;
    }

    // Search the Left & Right Subtree
    if (cursor->left != NULL)
    {
        left_cost = traversalCost(&(cursor->left), targetValue, traversal_path, index, num_traversals);
    }
    else
    {
        left_cost = -1;
    }
    if (cursor->right != NULL)
    {
        right_cost = traversalCost(&(cursor->right), targetValue, traversal_path, index, num_traversals);
    }
    else
    {
        right_cost = -1;
    }

    if ((left_cost != -1) && (left_cost != 0))
    {
        traversal_cost += left_cost;
        // 10 represents going Left, 20 going Right
        traversal_path[*index] = 10;
        *index += 1;
    }

    if ((right_cost != -1) && (right_cost != 0))
    {
        traversal_cost += right_cost;
        traversal_path[*index] = 20;
        *index += 1;
    }

    // If both subtrees return -1, it means that the target is in neither of the subtrees
    if ((left_cost == -1) && (right_cost == -1))
    {
        // Remove the Toll Cost of the Current Node
        traversal_cost = -1;
    }

    return traversal_cost;
}

int subtree_root_cost(BTNode **node, int nodeV1, int nodeV2, int nodeV1_path[SIZE], int nodeV2_path[SIZE], int *num_of_traversals)
{
    int current_node_value = ((*node)->nodeV);
    BTNode *cursor = *node;
    int array_length = 0, array_length2 = 0, final_array_length = 0, index = 0, index2 = 0;

    // Find Lowest Common Ancestor of the 2 Nodes
    while(true)
    {
        if ((nodeV2_path[index2] == 10) || (nodeV2_path[index2] == 20))
        {
            array_length2 += 1;
            index2 += 1;
            continue;
        }
        if ((nodeV1_path[index] == 10) || (nodeV1_path[index] == 20))
        {
            array_length += 1;
            index += 1;
        }
        else
        {
            break;
        }
    }

    int traversal_array_nodeV1[array_length];
    int traversal_array_nodeV2[array_length2];
    index = 0;

    // Determine the Largest Possible Pathway Iterations
    if (array_length2 < array_length)
    {
        final_array_length = array_length2;
    }
    else
    {
        final_array_length = array_length;
    }

    // Reverse the Order of the Array
    for (int i = final_array_length; i > 0; i -= 1)
    {
        traversal_array_nodeV1[index] = nodeV1_path[array_length - 1];
        traversal_array_nodeV2[index] = nodeV2_path[array_length2 - 1];
        index += 1;
        array_length2 -= 1;
        array_length -= 1;
    }

    // Add the Root Value [First Time]
    int duplicate_cost = 0;
    index = 0;
    while (true)
    {
        //  If either Node is the Root Node
        if ((nodeV1 == (*node)->nodeV) || (nodeV2 == (*node)->nodeV))
        {
            duplicate_cost += (*node)->nodeV;
            break;
        }
        // Check to see if they are moving in the same direction
        else if ((traversal_array_nodeV1[index]) == (traversal_array_nodeV2[index]))
        {
            // Went Left
            if (traversal_array_nodeV1[index] == 10)
            {
                // Add Value of Current Node then Move Left
                duplicate_cost += ((cursor->nodeV)*2);
                cursor = cursor->left;
            }

            // Went Right
            else if (traversal_array_nodeV1[index] == 20)
            {
                // Add Value of Current Node after Moving Right
                duplicate_cost += ((cursor->nodeV)*2);
                cursor = cursor->right;
            }
        }
        else
        {
            // Not the Same Direction
            duplicate_cost += cursor->nodeV;
            break;
        }
        index += 1;
    }
    return duplicate_cost;
}

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{
    if (nodeV1 == nodeV2)
    {
        return nodeV1;
    }
    // Create 2 Arrays of Ints to Record the direction taken;
    int nodeV1_path[SIZE], nodeV2_path[SIZE];
    int indexV1 = 0, indexV2 = 0;
    int *indexV1ptr = &indexV1;
    int *indexV2ptr = &indexV2;

    int traversal_num = 0;
    int *number_of_traversals = &traversal_num;

    // Calculate the Cost to traverse from Root to nodeV1  [CostX]
    int costV1 = 0, costV2 = 0, traversal_cost = 0, cost_subtract = 0;
    costV1 = traversalCost(&node, nodeV1, nodeV1_path, indexV1ptr, number_of_traversals);

    // Calculate the Cost to traverse from Root to nodeV2  [CostY]
    costV2 = traversalCost(&node, nodeV2, nodeV2_path, indexV2ptr, number_of_traversals);

    // Sum CostX and CostY  == CostZ
    traversal_cost = costV1 + costV2;

    // Subtract Cost of SubRoot and 2x Cost of Root (iif Root != Subroot)
    cost_subtract = subtree_root_cost(&node, nodeV1, nodeV2, nodeV1_path, nodeV2_path, number_of_traversals);   
    traversal_cost -= cost_subtract;

    return traversal_cost;

}