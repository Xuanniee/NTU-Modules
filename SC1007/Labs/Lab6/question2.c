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

void DFS_I (Graph , int );

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
    for(i=0;i<g.V;i++) g.visited[i] = 0;
    
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
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
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for DFS:\n");
    scanf("%d", &i);
    
    printGraphMatrix(g);
    DFS_I(g,i);

    return 0;
}

void DFS_I (Graph g, int v)
{
    // Visit the Neighbouring Vertices in Ascending Order using Depth First Search
    int numVertices = g.V;
    int numEdges = g.E, inputVertex = v;
    int ** adj_matrix = g.matrix;
    int visitedVertices[numVertices];
    memset(visitedVertices, 0, sizeof(visitedVertices));
    g.visited = visitedVertices;

    // Create a Stack to implement DFS
    Stack *vertexStack = (Stack*) malloc(sizeof(Stack));
    vertexStack->head = NULL;
    vertexStack->size = 0;

    // Add Staring Vertex to Stack
    push(vertexStack, inputVertex);
    visitedVertices[inputVertex-1] = 1;
    printf("Visited Vertices: %d ", inputVertex);

    // As long as Stack isn't Empty
    while (isEmptyStack(*vertexStack) != 1)
    {
        // Determine Current Vertex
        int currentVertex = peek(*vertexStack);

        // Add the Adjacent Vertices
        int counter = 0;
        for (int i = 0; i < numVertices; i += 1)
        {
            // Push to Stack if Adjacent and Not Visited Yet
            if ((adj_matrix[currentVertex - 1][i] == 1) && (visitedVertices[i] == 0))
            {
                // Mark Vertex as Visited
                visitedVertices[i] = 1;                
                push(vertexStack, i+1);
                // printf("i + 1: %d, ", i+1);
                printf("%d ", peek(*vertexStack));
                // Do not add more than one neighbouring Node
                break;
            }
            else
            {
                counter += 1;
            }
            
        }

        if (counter == numVertices)
        {
            // Pop from Stack if no more unvisited adjacent vertices
            pop(vertexStack);
        }

    }
    // End with Newline
    printf("\n");
    
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
