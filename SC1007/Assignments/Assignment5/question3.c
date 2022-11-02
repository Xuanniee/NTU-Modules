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
    for(i=0;i<g.V;i++) g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter a directed edge: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter a directed edge: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res == 1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    return 0;
}

int Connected (Graph g)
{
    printGraphMatrix(g);
    // Remember a Directed Graph goes both ways. So if it is 1 -> 2 and not 2 -> 1, the adj matrix will not be symmetrical
    // Initialise a Stack
    Stack *vertexStack = (Stack*) malloc(sizeof(Stack));
    vertexStack->size = 0;
    vertexStack->head = NULL;

    // Pointers for Graph
    int numVertices = g.V;
    int numEdges = g.E;
    int visited[numVertices];
    memset(visited, 0, sizeof(visited));
    g.visited = visited;
    int **adj_matrix = g.matrix;

    // Int Array to Store Success
    int success[numVertices];
    memset(success, 0, sizeof(success));
    
    // Ensure all Vertices are checked
    for (int index = 0; index < numVertices; index += 1)
    {
        // Push the First Vertex into Stack
        push(vertexStack, (index+1));
        visited[index] = 1;
        int counter = 0;

        // Traverse Graph from Current Vertex
        while (isEmptyStack(*vertexStack) != 1)
        {
            // Determine Current Vertex
            int currentVertex = peek(*vertexStack);
            counter = 0;

            // Check for Adjacent Vertices
            for (int i = 0; i < numVertices; i += 1)
            {
                // If the Vertex is Adjacent, Never Visited Before, and Strongly Connected
                if ((adj_matrix[currentVertex - 1][i] == 1) && (visited[i] == 0))
                {
                    // Add to Stack and Visited
                    push(vertexStack, (i+1));
                    visited[i] = 1;
                }
                else
                {
                    counter += 1;
                }

            }

            // Pop if there are no more adjacent unvisited vertices
            if (counter == numVertices)
            {
                pop(vertexStack);
            }
        }
        int fail = 0;
        // Check if All Vertices were visited from Current Vertex
        for (int i = 0; i < numVertices; i += 1)
        {
            if (visited[i] == 0)
            {
                // Not Strongly Connected
                success[index] = 0;
                fail = 1;
                break;
            }
            
        }

        // Reset Array
        memset(visited, 0, sizeof(visited));
        if (fail == 0)
        {
            // Strongly Connected for the Current Vertex
            success[index] = 1;
        }
        else if (fail == 1)
        {
            // Strongly Connected for the Current Vertex
            success[index] = 0;
        }
        
    }

    // Check if Connected for all Vertices
    for (int i = 0; i < numVertices; i += 1)
    {
        if (success[i] == 0)
        {
            // Not Strongly Connected
            return 0;
        }
        
    }
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
