#include <stdio.h>
#include <stdlib.h>

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

void buildTree(BTNode** node, char* preO, char* postO)
{
    // Create Pointers and Variables
    char *pre_cursor = preO;
    char *post_cursor = postO;
    char *final_preO, *final_postO;
    char current_root;
    BTNode *current_root_node = *node;

    // Determine the Value of the Root of the Current Subtree
    if (*node == NULL)
    {
        current_root = *preO;
    }
    else
    {
        current_root = current_root_node->id;
    }

    // Recursion Break Condition
    if(strlen(preO) == 1)
    {
        return;
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

    // Add 


}