#include <iostream>
#include <cmath>

#define V 9
#define MYINFINITY 9999999

// Structures for Minimising Heap
typedef struct minHeapNode{
    int nodeValue;
    int dist;
} MinHeapNode;

typedef struct minHeap{
    // Number of Heap Nodes present currently
    int size;
    int capacity;
    MinHeapNode **array;
} MinHeap;

// A structure to represent a
// node in adjacency list
typedef struct adjListNode{
    int dest;
    int weight;
    struct adjListNode* next;
} AdjListNode;
 
typedef struct adjList{
   // Pointer to head node of list
   AdjListNode *head;
}AdjList;
 
typedef struct graph
{
    int numVertices;
    AdjList* array;
}Graph;

void printArr(int dist[], int n);
void addEdge(Graph* graph, int src, int dest, int weight);
Graph* createGraph(int numVertices);
AdjListNode* newAdjListNode(int dest, int weight);
void HeapDecreaseKey(MinHeap* minimumHeap, int index, int newKeyDistance);
MinHeapNode* HeapExtractMinNode(MinHeap* minimumHeap);
void minHeapify(MinHeap* minimumHeap, int parentIndex);
void swapMinHeapNode(MinHeapNode** node1, MinHeapNode** node2);
MinHeap* BuildMinHeap(int capacity);
MinHeapNode* newMinHeapNode(int nodeValue, int dist);
void dijkstra(Graph* graph, int srcNode);

int main() {
    /**
     * @brief Issue seems to be with my minHeapify Function not working as intended since the Visited Nodes order is wrong
     * 
     */
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
 
    dijkstra(graph, 0);
    return 0;
}

void dijkstra(Graph* graph, int srcNode)
{
    // Definition of Solution, Predecessor, and Shortest Paths Arrays
    int solutionArray[V] {};
    int predecessorArray[V] {};
    int shortestCostArray[V] {};
    // Initialisation of Arrays
    for (int i{0}; i < V; i += 1)
    {
        // Current Vertex is not included in the Solution yet
        solutionArray[i] = 0;
        // No predecessor yet, assign to a NULL 
        predecessorArray[i] = -1;
        // Assign cost to any node to be infinite as we do not know shortest path yet
        shortestCostArray[i] = MYINFINITY;
    }

    // Cost of Source is 0 since we start there
    shortestCostArray[srcNode] = 0;
    predecessorArray[srcNode] = srcNode;

    // Create a Min Heap
    MinHeap* minimumHeap = BuildMinHeap(V);
    // Place all the Vertices in a Priority Queue [Min Heap in Part B]
    for (int i{0}; i < V; i += 1) {
        // Adding Nodes into the Queue by their Index Position
        minimumHeap->array[i] = newMinHeapNode(i, shortestCostArray[i]);
        minimumHeap->size++;
    }
  
    // Ensure it is a minHeap
    minHeapify(minimumHeap, 0);

    // Extracting the Node with the lowest costs
    while (minimumHeap->size != 0) {
        // Remove the Node with the Lowest Distance
        MinHeapNode* currentNode = HeapExtractMinNode(minimumHeap);
        // std::cout << "Visited Node: " << currentNode->nodeValue << std::endl;

        // Include it in our Solution
        solutionArray[currentNode->nodeValue] = 1;
        minimumHeap->size -= 1;

        // Updating Adjacent Nodes to Current Node to reflect new costs
        AdjListNode* cursor = graph->array[currentNode->nodeValue].head;
        while (cursor != NULL) {
            int adjacentNode = cursor->dest;
            // If Adjacent Nodes are not in the solution path and the cost of the old path is higher, replace with new path
            if (solutionArray[adjacentNode] != 1 && shortestCostArray[adjacentNode] > shortestCostArray[currentNode->nodeValue] + cursor->weight){
                // Update with new & shorter cost path
                shortestCostArray[adjacentNode] = shortestCostArray[currentNode->nodeValue] + cursor->weight;
                predecessorArray[adjacentNode] = currentNode->nodeValue;

                // Update the Adjacent Node Cost within the Heap
                HeapDecreaseKey(minimumHeap, cursor->dest, shortestCostArray[cursor->dest]);
                minHeapify(minimumHeap, 0);
            }
            cursor = cursor->next;
        }
    }

    // print the calculated shortest distances
    printArr(shortestCostArray, V);
}

/**
 * @brief Utility function to create a MinHeapNode*
 * 
 * @param nodeValue 
 * @param dist 
 * @return MinHeapNode* 
 */
MinHeapNode* newMinHeapNode(int nodeValue, int dist){
    MinHeapNode* minHeapNode = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    minHeapNode->nodeValue = nodeValue;
    minHeapNode->dist = dist;

    return minHeapNode;
}

/**
 * @brief Create a Min Heap object
 * 
 * @param capacity 
 * @return MinHeap* 
 */
MinHeap* BuildMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    // Storing the Actual MinHeap
    minHeap->array = (MinHeapNode**) malloc(sizeof(MinHeapNode*) * capacity); 

    return minHeap;
}

/**
 * @brief Swap 2 Min Heap Nodes
 * 
 * @param node1 
 * @param node2 
 */
void swapMinHeapNode(MinHeapNode** node1, MinHeapNode** node2){
    MinHeapNode* temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}
 
void minHeapify(MinHeap* minimumHeap, int parentIndex) {
    // Assumes that Binary Trees at Left and Right are Minimum Heaps but Parent might be larger than children
    int smallestIndex = parentIndex;
    int leftChildIndex = parentIndex * 2;
    int rightChildIndex = (parentIndex * 2) + 1;

    // Ensure that Left Child is not a Leaf and Determine if Left is smaller than Parent
    if ((leftChildIndex <= minimumHeap->size) && (minimumHeap->array[leftChildIndex]->dist < minimumHeap->array[parentIndex]->dist)){
        smallestIndex = leftChildIndex;
    }
    // Repeat for Right Child
    if ((rightChildIndex <= minimumHeap->size) && (minimumHeap->array[rightChildIndex]->dist < minimumHeap->array[parentIndex]->dist)){
        smallestIndex = rightChildIndex;
    }

    // If Parent is not the Smallest
    if (smallestIndex != parentIndex){
        // Swap the Nodes
        // MinHeapNode* node1 = minimumHeap->array[parentIndex];
        // MinHeapNode* node2 = minimumHeap->array[smallestIndex];
        swapMinHeapNode(&(minimumHeap->array[parentIndex]), &(minimumHeap->array[smallestIndex]));
        // Fix the SubHeap at where the Parent Node is at after the Swap
        minHeapify(minimumHeap, smallestIndex);
    }
}

/**
 * @brief To remove the smallest node from the min heap
 * 
 * @param minimumHeap 
 * @return MinHeapNode* 
 */
MinHeapNode* HeapExtractMinNode(MinHeap* minimumHeap){
    if (minimumHeap->size < 1) {
        throw std::invalid_argument("Heap Underflow");
    }

    // Minimum Node in a Min Heap is the Root, i.e. the first element
    MinHeapNode* minimumNode = minimumHeap->array[0];
    // Shift Last Node to the Start of the Array to remove the Min
    minimumHeap->array[0] = minimumHeap->array[minimumHeap->size - 1];
    // Heapify the Heap so that Minimum Heap Property is preserved
    minHeapify(minimumHeap, 0);
    
    return minimumNode;
}
\

/**
 * @brief // Input: A: an array representing a heap, i: an array index, key: a new key greater than A[i]
             Output: A still representing a heap where the key of A[i] was increased to key
             Running Time: O(log n) where n =heap-size[A]
 * 
 * @param minimumHeap 
 * @param index 
 * @param keyNodeValue 
 */
void HeapDecreaseKey(MinHeap* minimumHeap, int index, int newKeyDistance){
    // Input Validation
    if (newKeyDistance > minimumHeap->array[index]->dist){
        throw std::invalid_argument("New Key Value is larger than Current Key Value");
    }

    // Update the Node with the new key value
    minimumHeap->array[index]->dist = newKeyDistance;

    // Ensure Heap Property is not violated
    int parentIndex = floor(index / 2);
    while (index > 1 && minimumHeap->array[parentIndex]->dist < minimumHeap->array[index]->dist) {
        // MinHeapNode* node1 = minimumHeap->array[parentIndex];
        // MinHeapNode* node2 = minimumHeap->array[index];
        swapMinHeapNode(&(minimumHeap->array[parentIndex]), &(minimumHeap->array[index]));
        index = parentIndex;
        parentIndex = floor(index / 2);
    }
}

// A utility function to create
// a new adjacency list node
AdjListNode* newAdjListNode(int dest, int weight){
    AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices)
{
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = numVertices;
 
    // Create an array of adjacency lists. 
    // Size of array will be V
    graph->array = (AdjList*) malloc(numVertices * sizeof(AdjList));
 
    // Initialize each adjacency list
    // as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest, int weight){
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printArr(int dist[], int n){
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}