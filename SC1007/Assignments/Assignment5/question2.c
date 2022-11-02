#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ListNode Definition
typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int SD (Graph G, int v, int w);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

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
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    // printGraphMatrix(g);
    
    printf("Enter two vertices for finding their shortest distance: (press a to stop)\n");
    scanf("%d %d", &i, &j);

    int d = SD(g,i,j);
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    return 0;
}

int SD(Graph g, int v, int z)
{
    printGraphMatrix(g);
    // Initialize a Queue
    Queue *vertexQueue = (Queue*) malloc(sizeof(Queue));
    vertexQueue->size = 0;
    vertexQueue->head = NULL;
    vertexQueue->tail = NULL;

    // Initialize Pointers
    int startVertex = v;
    int endVertex = z;
    int numVertices = g.V;
    int numEdges = g.E;
    int pathCost[numVertices];
    memset(pathCost, 0, sizeof(pathCost));
    int visited[numVertices];
    memset(visited, 0, sizeof(visited));
    g.visited = visited;
    int **adj_matrix = g.matrix;

    // Enqueue the Start Node
    enqueue(vertexQueue, startVertex);
    visited[startVertex - 1] = 1;

    // Iterate through Graph to find a path
    int smallestCost = 0;
    while (isEmptyQueue(*vertexQueue) != 1)
    {
        // Dequeue Current Vertex
        int currentVertex = dequeue(vertexQueue);
        int counter  = 0;
        // Set the Starting Vertex Cost to be Zero
        pathCost[startVertex - 1] = 0;

        // Iterate through the Adjacent Vertices
        for (int i = 0; i < numVertices; i += 1)
        {
            // If Vertex is Adjacent and Not Visited
            if ((adj_matrix[currentVertex - 1][i] == 1) && (visited[i] != 1))
            {
                // Calculate Path Cost of Adjacent Node
                pathCost[i] = pathCost[currentVertex - 1] + 1;
                // Check if it is target
                if ((i + 1) == endVertex)
                {
                    for (int k = 0; k < numVertices; k += 1)
                    {
                        printf("%d ", pathCost[k]);
                    }
                    return pathCost[i];
                    // int pathIndex = 0;
                    // for (int i = 0; i < numVertices; i += 1)
                    // {
                    //     if (pathCost[i] == endVertex)
                    //     {
                    //         pathIndex = i;
                    //     }
                    // }
                    // if (pathIndex % 2 == 0)
                    // {
                    //     // Even; Index starts from 1 to Skip First Vertex since Path Cost counts Edges
                    //     for (int i = 1; i < numVertices; i += 1)
                    //     {
                    //         if (i % 2 == 0)
                    //         {
                    //             smallestCost += 1;
                    //         }
                    //     }
                    // }
                    // else
                    // {
                    //     // Odd
                    //     for (int i = 1; i < numVertices; i += 1)
                    //     {
                    //         if (i % 2 != 0)
                    //         {
                    //             smallestCost += 1;
                    //         }
                    //     }
                    // }
                    // return pathCost;
                }
                // Enqueue Adjacent Nodes
                enqueue(vertexQueue, (i + 1));
                // Mark as Visited
                visited[i] = 1;
            }
            else
            {
                counter += 1;
            }
        }

        // If there are no Adjacent Vertices
        if (counter == numVertices)
        {
            // Remove the Current Node to check the Next
            dequeue(vertexQueue);
        }
    }
    // If no Path
    return -1;
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


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}