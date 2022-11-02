#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

int Connected (Graph);

int main()
{
    Graph g;
    int i,j;
    

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
	
    g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) 
        g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res ==1)
        printf("The graph is connected.\n");
    else
        printf("The graph is not connected.\n");

    return 0;
}

int Connected (Graph g)
{
    printGraphMatrix(g);
    // Input Validation: Ensure there is at least 1 Vertex
    if (g.V < 1)
    {
       return 0;
    } 

    // Create a Stack to keep track of the Vertices to visit, i.e. Traversal Order
    Stack *verticesOrder = (Stack*) malloc(sizeof(Stack));
    verticesOrder->size = 0;
    verticesOrder->head = NULL;

    // Pointers to keep track of Graph
    int numVertices = g.V;
    int numEdges = g.E;
    int visitedVertices[numVertices];
    memset(visitedVertices, 0, sizeof(visitedVertices));
    g.visited = visitedVertices;
    int **adj_matrix = g.matrix;

    // For Loop to check if any vertex can reach all the other vertices
    for (int i = 0; i < numVertices; i += 1)
    {
        // Keep Track of Current Vertex
        int currentVertex = i + 1;
        // Push the Current Vertex into Stack, Treating it as the First Node 
        push(verticesOrder, currentVertex);
        visitedVertices[i] = 1;

        // While Stack is not Empty
        while(isEmptyStack(*verticesOrder) != 1)
        {
            // Determine Current Node
            int stackPeek = peek(*verticesOrder);
            // int *currentVertexPtr = *(adj_matrix + stackPeek - 1);      // Pointer to One of the Outer Array Indexes
            // If Stack not Empty
            int counter = 0;
            for (int j = 0; j < numVertices; j += 1)
            {
                // If there is an Edge adjacent to another Vertex && Another Vertex has not been visited
                if ((adj_matrix[stackPeek - 1][j] == 1) && (visitedVertices[j] == 0))
                {
                    // Push the Adjacent Vertex into Stack
                    push(verticesOrder, (j + 1));
                    // Mark the Current Vertex as Visited
                    visitedVertices[j] = 1;
                }
                else
                {
                    counter += 1;
                }
            }

            if (counter == numVertices)
            {
                pop(verticesOrder);
            }
        }

        // Check the Visited Array to ensure all Vertices have been visited for the Current Vertex
        for (int j = 0; j < numVertices; j += 1)
        {
            if (*(visitedVertices + j) == 0)
            {
                // Not a Connected Graph
                return 0;
            }
            else
            {
                *(visitedVertices + j) = 0;
            }
        }
    }
    // Connected Graph since can reach all the Vertices from any Vertex
    return 1;
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
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

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
