#include <stdio.h>
#include <stdlib.h>

// Linked List Definition
typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

// Graph Definition
typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

// Queue Definition
typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

// BFS Function
void BFS (Graph G, int v);

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
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for BFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    BFS(g,i);

    return 0;
}

// void BFS(Graph g, int v){
//     // BFS Uses a Queue
//     int numVertices = g.V;
//     int **adj_matrix = g.matrix;
//     int *visitedArray = g.visited;

//     // Create a Queue
//     Queue *vertexQueue = (Queue*) malloc(sizeof(Queue));
//     vertexQueue->size = 0;
//     vertexQueue->head = NULL;
//     vertexQueue->tail = NULL;

//     enqueue(vertexQueue, v);
//     visitedArray[v-1] = 1;
//     printf("%d ", v);

//     while(isEmptyQueue(*vertexQueue) != 1)
//     {
//         // While Queue is Not Empty, Add the Neighbours of Vertex into the Queue
//         int currentVertex = getFront(*vertexQueue);
//         for (int i = 0; i < numVertices; i += 1)
//         {
//             // Not Visited and Adjacent
//             if ((adj_matrix[currentVertex-1][i] == 1) && (visitedArray[i] == 0))
//             {
//                 // Visit the Node and Enqueue the Neighbours
//                 visitedArray[i] = 1;
//                 enqueue(vertexQueue, (i+1));
//                 printf("%d ", i+1);
//             }
//         }
//         // If Visited all Neighbours
//         dequeue(vertexQueue);
        
//     }
//     printf("\n");

// }

void BFS(Graph g, int v)
{
    // Create a Queue to keep track of Traversal Order
    Queue *traversalQueue = (Queue*) malloc(sizeof(Queue));
    traversalQueue->size = 0;
    traversalQueue->head = NULL;
    traversalQueue->tail = NULL;

    // Initial Values
    int numVertices = g.V;
    int numEdges = g.E;
    int targetVertex = v;

    // Pointers for Graph
    int **adj_matrix = g.matrix;
    int *array_VisitedNodes = g.visited;
    int **outer_Array = adj_matrix;
    int *inner_Array = NULL;

    // Enqueue the Startind Node
    enqueue(traversalQueue, targetVertex);

    // Continue until Queue is Empty
    int index = 0;  // For Keeping Track of Integers in Array
    while (isEmptyQueue(*traversalQueue) != 1)
    {
        // printf("Traveral Queue: %d\n", getFront(*traversalQueue));
        // Check First Item
        int visited_Vertex = getFront(*traversalQueue);

        // Ensure the Node has not been visited before
        int *verification = array_VisitedNodes;
        int broken = 0;
        for (int i = 0; i < index; i += 1)
        {
            if (*(verification + i) == visited_Vertex)
            {
                // Node has been visited; Dequeue Node without Adding Neighbours
                dequeue(traversalQueue);
                broken = 1;
                break;
            }
        }  
        if (broken == 1)
        {
            continue;
        }
        
        // Mark the New Node as Visited
        *(array_VisitedNodes + index) = visited_Vertex;
        index += 1;

        // Enqueue the Neighbouring Nodes
        int *adjacent_Nodes = *(outer_Array + visited_Vertex - 1);
        // while (adjacent_Nodes != NULL)
        for (int i = 0; i < numVertices; i += 1)
        {
            int neighbour = 0;
            neighbour = *(adjacent_Nodes + i);
            if ((neighbour == 1) && ((i) != numVertices))
            {
                enqueue(traversalQueue, (i+1));
            }
        }

        // Remove the Visited Node from Queue
        dequeue(traversalQueue);
        printf("%d ", visited_Vertex);
    }

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
