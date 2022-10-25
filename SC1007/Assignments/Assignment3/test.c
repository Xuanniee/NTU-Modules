#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
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

// void numElementsBTree(BTNode *root, int *num_of_nodes, int *preorderPtr)
// {
//     // Add the Value of the Current Node
//     *num_of_nodes += 1;
//     // Save the Value in Array
//     *preorderPtr = root->item;
//     preorderPtr += 1;

//     // Return if is a Leaf Node
//     if ((root->left == NULL) && (root->right == NULL))
//     {
//         return;
//     }

//     // Recursively call itself on the LST and RST
//     numElementsBTree(root->left, num_of_nodes, preorderPtr);
//     numElementsBTree(root->right, num_of_nodes, preorderPtr);
// }

int checkLeafNode (BTNode *subtree_root)
{
    if (subtree_root == NULL)
    {
        return 1;
    }
    // Base Condition
    if ((subtree_root->left == NULL) && (subtree_root->right == NULL))
    {
        // Leaf Node
        return subtree_root->item;
    }

    // Check if it fulfil a Binary Search Tree Specifications
    BTNode *left_child = subtree_root->left, *right_child = subtree_root->right;
    if (left_child != NULL)
    {
        if (left_child->item > subtree_root->item)
        {
            // Not a valid BST
            return -1;

        }   
    }
    if (right_child != NULL)
    {
        if (right_child->item < subtree_root->item)
        {
            // Not a valid BST
            return -1;
        }
    }

    // Check LST & RST
    int valid_left = 0, valid_right = 0;
    if (left_child != NULL)
    {
        valid_left = checkLeafNode(left_child);
    }
    if (right_child != NULL)
    {
        valid_right = checkLeafNode(right_child);
    }

    if ((valid_left == -1) || (valid_right == -1))
    {
        return -1;
    }

    // if ((left_child == NULL) && (right_child == NULL))
    // {
    //     // Subtree is not a BST
    //     return NULL;
    // }
    // if ((left_child == NULL) && (right_child != NULL))
    // {
    //     return right_child;
    // }
    // if ((left_child != NULL) && (right_child == NULL))
    // {
    //     return left_child;
    // }
    return subtree_root->item;
    
}

BTNode* findNode(BTNode* root, int nodeValue)
{
    BTNode *target = root;
    if (root->item == nodeValue)
    {
        return target;
    }
    else if (root == NULL)
    {
        // Target Not Found
        return NULL;
    }

    target = findNode(root->left, nodeValue);
    if (target != NULL)
    {
        return target;
    }
    target = findNode(root->right, nodeValue);
    // Confirm must be in RST
    return target;
}

BTNode* findLargestBST (BTNode* root)
{
    // Base Condition
    



    // Set Subtree Root
    BTNode *subtree_root = root;
    BTNode *largestBTNode = NULL;
    int valid_BST = 0;
    int left_child = 0, right_child = 0;

    // Check if Subtree Node is a BST
    valid_BST = checkLeafNode(subtree_root);
    if (valid_BST == -1)
    {

        // Not a BST
        // Recursively Check the LST and RST
        if (root->left != NULL)
        {
            left_child = checkLeafNode(root->left);
        }
        if (root->right != NULL)
        {
            right_child = checkLeafNode(root->right);
        }

        // Both Subtress do not have BST
        if ((left_child == -1) && (right_child == -1))
        {
            return NULL;
        }
        else if ((left_child != -1) && (right_child == -1))
        {
            // Left Child has BST
            return findNode(root, left_child);
        }
        else if ((left_child == -1) && (right_child != -1))
        {
            // Right Child has BST
            return findNode(root, right_child);
        }
        else if ((left_child != -1) && (right_child != -1))
        {
            // If Equally Large Subtrees; Return Left
            // Check Size of LST & RST


            return findNode(root, left_child);
        }
    }

    return subtree_root;

}