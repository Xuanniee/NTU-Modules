#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

// Means that the Memory allocated can store either an int pointer pointer or a ListNode pointer pointer, but not both at the same time
union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    // Initialising a Graph
    Graph g;
    int i,j;

    // Create a Pointer that Points to the Number of Vertices the Graph has
    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    // Initialise the Values of the Graph
    g.E = 0;
    // Malloc space for the Rows of the Adjacency Matrix
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));

    // Malloc Space for the Columns of the Adjacency Matrix
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    // Initialise all the Values of the Adjacency Matrix to be 0, i.e. a 2D array of Zeroes
    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;

    // Finish initialising the Members of Graph G
    g.type = ADJ_MATRIX;

    // I don't quite understand this but I assume is memory enough to store the all digits
    degreeV = (int *) malloc(g.V*sizeof(int));

    // ERM
    for(i=0;i<g.V;i++)
        degreeV[i]=0;
    
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    }


    printGraphMatrix(g);
    
    adjM2adjL(&g);
    
    printGraphList(g);

    calDegreeV(g,degreeV);
    
    printDegreeV(degreeV,g.V);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    printf("Print graph matrix \n");
    if(g.type == ADJ_LIST) {printf("Error"); return;}
    
    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }
    printf("\n");

}

void adjM2adjL(Graph *g)
{
	g->type = ADJ_LIST; //change representation form

    // Create an ADJ_List
    int vertexNum = g->V;
    ListNode **adj_list = (ListNode**) malloc(sizeof(ListNode*) * vertexNum);
    ListNode **tmp = adj_list;
    for (int i = 0; i < vertexNum; i += 1)
    {
        ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
        newNode->vertex = -1;
        newNode->next = NULL;
        *(tmp + i) = newNode;
    }

    // Iterate throught the ADJ_matrix
    int **matrixPtr = g->adj.matrix;
    int *cursor = NULL;

    // Iterate through the Array
    int outerArray_Index = 0;
    int innerArray_Index = 0;
    for (int i = 0; i < vertexNum; i += 1)
    {
        // Iterate through the Linked List
        cursor = *(matrixPtr + i);
        innerArray_Index = 0;
        for (int j = 0; j < vertexNum; j += 1)
        {
            if (*cursor == 1)
            {
                ListNode *adjListPtr = *(adj_list + outerArray_Index);
                // Put Inner Array Index
                if (adjListPtr->vertex == -1)
                {
                    adjListPtr->vertex = innerArray_Index + 1;
                }
                // Append a New ListNode if Head is already filled
                else
                {
                    ListNode *traversal = adjListPtr;
                    while (traversal->next != NULL)
                    {
                        traversal = traversal->next;
                    }
                    ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
                    newNode->next = NULL;
                    newNode->vertex = innerArray_Index + 1;

                    traversal->next = newNode;
                }
            }
            // Move vertically down the Inner Array
            innerArray_Index += 1;
            cursor += 1;
        }

        // Move to Next Index
        outerArray_Index += 1;
    }

    // Replace the Adjacency Matrix
    g->adj.list = adj_list;
}


void printGraphList(Graph g){
    int i;
    ListNode* temp;
    printf("Print graph list \n");
    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}

void calDegreeV(Graph g, int *degreeV)
{
    // After Conversion to Adjacency List
    if (g.type != ADJ_LIST)
    {
        return;
    }

    // Iterate through the Adjacency List
    int numVertices = g.V;
    int numEdges = g.E;

    ListNode *cursor = *(g.adj.list);
    ListNode *tmp = cursor;

    
    for (int i = 0; i < numVertices; i += 1)
    {
        // Move Cursor to the Next Vertex
        cursor = (tmp + i);
        int currentDegree = 0;
        // Determine the Degree for the Current Vertex
        while (cursor != NULL)
        {
            currentDegree += 1;
            cursor =  cursor->next;
        }
        // Save the Degree Value
        *(degreeV + i) = currentDegree;
        
    }
    return;
    
}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}