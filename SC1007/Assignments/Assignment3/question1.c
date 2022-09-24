#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    // Create Pointers and Variables
    char *pre_cursor = preO;
    char *post_cursor = postO;
    char *LST_cursor = NULL, *RST_cursor = NULL;
    char current_root;
    BTNode *current_root_node = *node;

    if (*preO == '\0')
    {
        return;
    }

    current_root = *preO;

    // Determine Left Child and Right Child Contents
    char left_child, right_child;
    while (*pre_cursor != current_root)
    {
        pre_cursor += 1;
    }
    // Ensure RHS of Preorder is not Empty
    if ((preO + 1) != NULL)
    {
        left_child = *(pre_cursor + 1);
    }

    while (*post_cursor != current_root)
    {
        post_cursor += 1;
        // End of Preorder Expression
        if (*post_cursor == '\0')
        {
            break;
        }
    }
    // Ensure that RHS of PreOrder is not Empty
    if ((preO + 1) != NULL)
    {
        right_child = *(post_cursor - 1);
    }

    // Insert for Current Node
    if (*node == NULL)
    {
        // If Actual Root
        insert_treeNode(node, current_root);
    }

    // Ensure Left and Right Child are not the SAME before Inserting Child Nodes
    char *check = preO;
    while(*check)
    {
        if (*check == '\0')
        {
            break;
        }
        if (left_child == *check)
        {
            insert_treeNode(&((*node)->left), left_child);
        }
        if ((left_child != right_child) && (right_child == *check))
        {
            insert_treeNode(&((*node)->right), right_child);
        }
        check += 1;
    }

    // Recursion Break Condition
    if(strlen(preO) == 1)
    {
        return;
    }

    // Create PreO for LST and PreO for RST
    // Pointing at LST Root
    LST_cursor = preO + 1;
    post_cursor = postO;
    int RST_elements = 0;

    // Find the LST Root in Post Order
    while(*post_cursor != *LST_cursor)
    {
        post_cursor += 1;
    }

    // Point at Next Element after LST Root
    // post_cursor += 1;

    // Find the First Element of RST in PostOrder
    while (true)
    {
        post_cursor += 1;        
        if ((*post_cursor == current_root) || (*post_cursor == '\0'))
        {
            RST_elements += 1;
            break;
        }   
        RST_elements += 1;
    }
    // Post_Cursor is pointing at  8 in Post Order
    post_cursor -= 1;
    // If RST first Element is the first element of LST
    if (*post_cursor == *LST_cursor)
    {
        *post_cursor = '\0';
    }

    int LST_elements = 0;
    // Find the Start of RST Expression in PreOrder
    pre_cursor = preO;
    // If the Binary Tree does not have a RST
    // if (*(pre_cursor + 1) == *post_cursor)
    // {
    //     while (*pre_cursor != '\0')
    //     {
    //         LST_elements += 1;
    //     }
    // }
    while(true)
    {
        pre_cursor += 1;
        if (*pre_cursor == *post_cursor)
        {
            break;
        }
        LST_elements += 1;
    }

    // Create a New PreO String for LST
    LST_cursor = malloc(LST_elements * sizeof(char) + 1);
    char *tmp = LST_cursor;
    char *preorder = preO + 1;
    // Preorder is also pointing at 8 in Pre ORder
 
    // while(*pre_cursor != *preorder)
    for (int j = 0; j < LST_elements; j += 1)
    {
        // Copy the LST Elements to New String
        *tmp = *preorder;
        tmp += 1;
        preorder += 1;
        if (*preorder == *pre_cursor)
        {
            *tmp = '\0';
        }
    }

    // Create a New PreO String for RST
    RST_cursor = malloc(RST_elements * sizeof(char) + 1);
    tmp = RST_cursor;
    for (int i = 0; i < RST_elements; i += 1)
    {
        if (i == RST_elements - 1)
        {
            *tmp = '\0';
        }
        else
        {
            *tmp = *pre_cursor;
        }
        pre_cursor += 1;
        tmp += 1;
    }

    // Recursively Calling BuildTree on LST & RST
    buildTree(&((*node)->left), LST_cursor, postO);
    buildTree(&((*node)->right), RST_cursor, postO);

}