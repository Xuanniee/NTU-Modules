#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
    bool BST;
    int size;
    int min;
    int max;
} BTNode;

typedef struct _queueNode{
	BTNode *data;
	struct _queueNode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * data);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode* createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

BTNode* findLargestBST (BTNode* root);

int main()
{
    BTNode* root = NULL;
    BTNode* temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag=1;
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(root==NULL)
        {
            if(item!=-1){
                root =createNode(item);
                enqueue(&q,root);
            }
        }
        else{
            while(!isEmptyQueue(q)){
                temp = getFront(q);
                if(flag){
                    if(item != -1){
                        temp->left = createNode(item);
                        enqueue(&q,temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if(temp->right==NULL){
                    if(item!=-1){
                        temp->right = createNode(item);
                        enqueue(&q,temp->right);
                    }
                    dequeue(&q);
                    flag=1;
                    break;
                }
                else  dequeue(&q);
            }
        }
    }
    scanf("%*s");
    printf("The input binary tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    BTNode* BSTnode = findLargestBST (root);
    printf("The largest binary search subtree:\n");
    if(BSTnode)
        printBTNode(BSTnode,0,0);
    else
        printf("No BST\n");
    deleteTree(&root);

    return 0;
}

BTNode* createNode(int item)
{
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
    node->BST = false;
    node->size = 0;
    node->min = 0;
    node->max = 0;
	return node;
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

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}
void enqueue(Queue *qPtr, BTNode *data){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
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
    return q.head->data;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}

void checkBST (BTNode *root)
{
    // Assign Left Child and Right Child
    BTNode *left_child = root->left, *right_child = root->right;

    // Check if it is a BST
    if ((left_child == NULL) && (right_child == NULL))
    {
        // Leaf Node --> BST of Size 1
        root->BST = true;
        root->size = 1;
        root->min = root->item;
        root->max = root->item;
    }
    // One of the Child is NULL
    else if ((left_child == NULL) || right_child == NULL)
    {
        // If Left Child is NULL but Right Child is a BST
        if ((left_child == NULL) && (right_child->BST == true))
        {
            // Check if Current Root is a BST
            if (root->item < right_child->min)
            {
                root->BST = true;
                root->size = right_child->size + 1;
                root->min = root->item;
                root->max = right_child->max;
            }
        }
        // Right Child NULL and LST is a BST
        else if ((right_child == NULL) && left_child->BST == true)
        {
            // Check if Current Root is a BST
            if (root->item > left_child->max)
            {
                root->BST = true;
                root->size = left_child->size + 1;
                root->min = left_child->min;
                root->max = root->item;
            }
        }
    }
    // BST
    else if ((root->item > left_child->max) && (root->item < right_child->min) && (left_child->BST == true) && (right_child->BST == true))
    {
        // Subtree BST
        root->BST = true;
        root->size = (left_child->size + right_child->size + 1);
        root->min = left_child->min;
        root->max = right_child->max;
    }
    // Not a BST but contains a BST in the subtrees
    else if ((left_child->BST == true) || (right_child->BST == true))
    {
        // Both Subtrees contain BST, take the Left One
        if ((left_child->BST == true) && (right_child->BST == true))
        {
            // Take Left BST
            root->BST = false;
            root->size = left_child->size;
        }
        else if (left_child->BST == false)
        // else if (left_child->size < right_child->size)
        {
            // RST contains the BST
            root->BST = false;
            root->size = right_child->size;
        }
        else if (right_child->BST == false)
        // else if (left_child->size > right_child->size)
        {
            // LST contains the BST
            root->BST = false;
            root->size = left_child->size;
        }
    }
}

BTNode *searchLargestBST(BTNode* root)
{
    BTNode *left_child = root->left, *right_child = root->right;
    BTNode *target = NULL;

    // Stop Condition
    if (root->BST == true)
    {
        return root;
    }

    // Compare the Sizes of BST in LST and RST
    if (left_child->size > right_child->size)
    {
        // BST in LST
        target = searchLargestBST(left_child);
    }
    else if (left_child->size < right_child->size)
    {
        // BST in RST
        target = searchLargestBST(right_child);
    }
    else if (left_child->size == right_child->size)
    {
        // BST in both. Take Left
        target = searchLargestBST(left_child);
    }

    return target;
}

BTNode* findLargestBST (BTNode* root)
{
    // Traverse the Root in a PostOrder Traversal Order [Left->Right->Root]
    // Base Case
    if ((root->left == NULL) && (root->right == NULL))
    {
        // Leaf Node
        return root;
    }

    // Check the Left Subtree
    if (root->left != NULL)
    {
        checkBST(findLargestBST(root->left)); 
    }

    // Check the Right Subtree
    if (root->right != NULL)
    {
        checkBST(findLargestBST(root->right));   
    }

    // Check the Subtree Root
    checkBST(root);

    // Determine if Root is Largest BST
    BTNode *left_child = root->left, *right_child = root->right;
    BTNode *target = NULL;
    if (root->BST == true)
    {
        return root;
    }
    // One of the Subtrees is NULL
    else if ((left_child == NULL) || (right_child == NULL))
    {
        return root;
    }
    // Check if LST and RST have BST
    else if ((left_child->size == 0) && (right_child->size == 0))
    {
        // No BST at all
        return NULL;
    }
    // Determine if BST is in LST or RST
    else
    {
        // LST and RST is equally big
        if (left_child->size == right_child->size) 
        {
            target= searchLargestBST(left_child);
        }
        // LST is Bigger than RST
        else if (left_child->size > right_child->size)
        {
            target = searchLargestBST(left_child);
        }
        // RST is Bigger than LST
        else if (left_child->size < right_child->size)
        {
            target = searchLargestBST(right_child);
        }
    }

    // Return the Current Node
    return target;
}