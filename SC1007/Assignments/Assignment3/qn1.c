#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);
void insert_treeNode(BTNode **node, char item);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

// Basic Operation Functions

// Finding the Left-Most Descendant Node, i.e. the First Node in the Subtree for InOrder
void insert_treeNode(BTNode **node, char item){
    BTNode *left_descendant = *node;
    BTNode *right_descendant = *node;

    // Create a New Node for the Binary Tree
    BTNode *newNode = (BTNode*) malloc(sizeof(BTNode));
    newNode->id = item;
    newNode->left = NULL;
    newNode->right = NULL;

    // Check if Tree is Empty
    if (*node == NULL)
    {
        // Make New Node the Root of the Binary Tree
        *node = newNode;
        return;
    }

    // Else Insert into Left Node if Possible. Not then Right Node
    if ((*node)->left == NULL)
    {
        // Insert into Left
        (*node)->left = newNode;
    }
    else if ((*node)->right == NULL)
    {
        // Insert into Right
        (*node)->right = newNode;
    }


}

void buildTree(BTNode** node, char* preO, char* postO){
    char *pre_cursor = preO;
    char *post_cursor = postO;
    char current_root;
    BTNode **current_root_node = node;

    // Determine the Value of the Root of the Current Subtree
    if (*node == NULL)
    {
        current_root = *preO;
    }
    else
    {
        current_root = (*node)->id;
    }

    // Determine Left Child and Right Child Contents
    while (*pre_cursor != current_root)
    {
        pre_cursor += 1;
    }
    char left_child = *(pre_cursor + 1);
    while (*post_cursor != current_root)
    {
        post_cursor += 1;
    }
    char right_child = *(post_cursor - 1);

    // Recursion Break Condition
    if ((left_child > right_child) || (current_root > left_child) || (current_root > right_child))
    {
        return;
    }

    // Recursively add Tree Nodes
    if (*node == NULL)
    {
        // If Actual Root
        insert_treeNode(node, current_root);
    }

    // Ensure Left and Right Child are not the SAME
    insert_treeNode(&((*node)->left), left_child);
    if (left_child != right_child)
    {
        insert_treeNode(&((*node)->right), right_child);
    }

    // Recursively Call the Function for Left & Right Subtree
    buildTree(&((*node)->left), preO, postO);
    if (left_child != right_child)
    {
        buildTree(&((*node)->right), preO, postO);
    }

}