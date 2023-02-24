#include <Python.h>
#include <iostream>
#include <chrono>
#include <vector>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std::chrono;

// Define the Number of Vertices
// #define V 500
#define INFINITYXY 9999999
#define MAXWEIGHT 10
#define ITERATIONS 20

// Custom Data Types
struct PriorityQueueItem
{
    int nodeValue{};
    int shortestPathCost{};
};

int** createGraph(int V, int Edges);
void dijkstra(int** graph, int srcNode, int V);
void enqueue(int nodeValue, int shortestPathCost, PriorityQueueItem priorityQueue[]);
int peek(int shortestCostArray[], PriorityQueueItem priorityQueue[]);
void dequeue(int shortestCostArray[], int targetNode, PriorityQueueItem priorityQueue[]);
void printSolution(int* dist, int V);

// Creating a Priority Queue and its Pointer
// PriorityQueueItem priorityQueue[V]{};
int sizeQueue{-1};
// Graph
// int adj[V][V];

int main()
{
    int numVertices = 10;
    // // Testing Correctness
    // int graph[9][9] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
    //                     { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
    //                     { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
    //                     { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
    //                     { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
    //                     { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
    //                     { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
    //                     { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
    //                     { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    // int **adjMatrix = createGraph(numVertices);

    // for(int j{0}; j < 9; j += 1){
    //     for(int k{0}; k < 9; k += 1){
    //         adjMatrix[j][k] = graph[j][k];
    //     }
    // }
    
    // auto startTime = high_resolution_clock::now();
    // dijkstra(adjMatrix, 0, numVertices);
    // auto endTime = high_resolution_clock::now();
    
    // auto timeTaken = duration_cast<microseconds>(endTime - startTime);
    // std::cout << "Time taken for Dijkstra using Arrays as Priority Queue: " << timeTaken.count() << " microseconds" << std::endl;

    // Testing Dijkstra on several randomly generated graphs
    // int timesArray[ITERATIONS]{0};
    // int numVerticesArray[ITERATIONS]{0};
    std::vector<int> timesArray1(ITERATIONS);
    std::vector<int> timesArray2(ITERATIONS);
    std::vector<int> numVerticesArray(ITERATIONS);
    std::vector<int> numEdgesArray(ITERATIONS);


    for (int i{0}; i < ITERATIONS; i += 1){
        // Generate Graph
        int **adjMatrix = createGraph(numVertices, -1);
        
        auto startTime = high_resolution_clock::now();
        dijkstra(adjMatrix, 0, numVertices);
        auto endTime = high_resolution_clock::now();
        
        auto timeTaken = duration_cast<microseconds>(endTime - startTime);
        // std::cout << "Time taken for Dijkstra using Arrays as Priority Queue: " << timeTaken.count() << " microseconds" << std::endl;
        
        // Export to CSV
        timesArray1.at(i) = timeTaken.count();
        numVerticesArray.at(i) = numVertices;
    
        numVertices += 10;
    }

    numVertices = 10;
    int numEdges = numVertices;
    for (int i{0}; i < ITERATIONS; i += 1){
        // Generate Graph
        int **adjMatrix = createGraph(numVertices, numEdges);
        
        auto startTime = high_resolution_clock::now();
        dijkstra(adjMatrix, 0, numVertices);
        auto endTime = high_resolution_clock::now();
        
        auto timeTaken = duration_cast<microseconds>(endTime - startTime);
        // std::cout << "Time taken for Dijkstra using Arrays as Priority Queue: " << timeTaken.count() << " microseconds" << std::endl;
        
        // Export to CSV
        timesArray2.at(i) = timeTaken.count();
        numEdgesArray.at(i) = numEdges;
    
        numEdges += 1;
    }

    for (int i{0}; i < ITERATIONS; i += 1){
        std::cout << "Time for Array: " << timesArray1[i] << " microseconds" << std::endl;
        std::cout << "Time for Heap: " << timesArray2[i] << " microseconds" << std::endl;
    }

    // Plotting the First Graph
    plt::plot(timesArray1, numVerticesArray);
    plt::xlabel("Number of Vertices");
    plt::ylabel("Time Taken by Dijkstra Algorithm");
    plt::title("Graph of Time against Number of Vertices");
    // Save the image (file format is determined by the extension)
    plt::save("./dijkstraArrayVaryVertices.png");

    // Plotting the Second Graph
    plt::plot(timesArray2, numEdgesArray);
    plt::xlabel("Number of Edges");
    plt::ylabel("Time Taken by Dijkstra Algorithm");
    plt::title("Graph of Time against Number of Edges");
    plt::save("./dijkstraArrayVaryEdges.png");

    return 0;
}

int** createGraph(int V, int Edges){
    int i, j, E, vertex1, vertex2;
    int** adj = new int*[V];
    for (int i = 0; i < V; ++i) {
        adj[i] = new int[V];
    }

    srand(time(NULL));

    for(i=0; i<V; i++){ //initialising matrix with 0s
        for(j=0; j<V; j++){
            adj[i][j] = 0;
        }
    }
    /*
    //test graph
    adj[0][1] = 2; //adding weighted edges for test graph
    adj[0][2] = 4;
    adj[1][2] = 1;
    adj[1][3] = 7;
    adj[2][4] = 3;
    adj[3][5] = 1;
    adj[4][3] = 2;
    adj[4][5] = 5;*/

    // for(i=0; i<V; i++){ //initialising distances to all vertices to infinity since not reached yet
    //     dist[i] = infinity;
    //     status[i] = 0;
    // }

    //randomly generated graph code
    E = rand()%(V*(V-1) + 1); //generating random number of edges in the directed graph... with max num of edges = V(V-1)....... can edit this value with artificial limit if want to limit the number of edges further to simulate a road network
    
    // If -1 is Provided it means we are varying the number of vertices
    if (Edges != - 1) {
        E = Edges;
    }

    for(i=0; i<E; i++){
        vertex1 = rand()%V;
        vertex2 = rand()%V;

        while(vertex1 == vertex2 || adj[vertex1][vertex2] != 0){ //making sure the 2 selected vertices are not the same => no self edge AND the edge has not already been added
            vertex1 = rand()%V;
            vertex2 = rand()%V;
        }

        adj[vertex1][vertex2] = (rand()%MAXWEIGHT) + 1; //adding a new edge into the graph with weight being a random value from 1 to MAXWEIGHT
        //printf("Adding an edge from %d to %d with weight %d\n", vertex1, vertex2, adj[vertex1][vertex2]); //for testing
    }
    return adj;
}

void dijkstra(int** graph, int srcNode, int V)
{
    if (V == 0){
        return;
    }
    PriorityQueueItem* priorityQueue = (PriorityQueueItem*) malloc(sizeof(PriorityQueueItem)*V);
    // std::vector<PriorityQueueItem> priorityQueue(V);

    // Definition of Solution, Predecessor, and Shortest Paths Arrays
    int* solutionArray = (int*) malloc(sizeof(int)*V);
    // std::vector<int> solutionArray(V);
    // int predecessorArray[]{};
    int* predecessorArray = (int*) malloc(sizeof(int)*V);
    // std::vector<int> predecessorArray(V);
    int* shortestCostArray = (int*) malloc(sizeof(int)*V);
    // int shortestCostArray[]{};
    // std::vector<int> shortestCostArray(V);
    // Initialisation of Arrays
    for (int i{0}; i < V; i += 1)
    {
        // Current Vertex is not included in the Solution yet
        solutionArray[i] = 0;
        // No predecessor yet, assign to a NULL 
        predecessorArray[i] = -1;
        // Assign cost to any node to be infinite as we do not know shortest path yet
        shortestCostArray[i] = INFINITYXY;
    }

    // Cost of Source is 0 since we start there
    shortestCostArray[srcNode] = 0;
    predecessorArray[srcNode] = srcNode;
    
    // Place all the Vertices in a Priority Queue [An Array for Part A]
    for (int i{0}; i < V; i += 1) {
        // Adding Nodes into the Queue by their Index Position
        enqueue(i, shortestCostArray[i], priorityQueue);
    }

    // Extracting the Node with the lowest costs
    while (sizeQueue != -1) {
        // Remove Current Node from Queue
        int currentNodeIndex = peek(shortestCostArray, priorityQueue);
        // Include it in our Solution
        solutionArray[currentNodeIndex] = 1;
        dequeue(shortestCostArray, currentNodeIndex, priorityQueue);

        // Updating Adjacent Nodes to Current Node to reflect new costs
        for (int i{0}; i < V; i += 1) {
            // If Adjacent is not in Solution Array and the Old Cost of the Node is Higher, replace with current path.
            if ((solutionArray[priorityQueue[i].nodeValue] != 1) && (shortestCostArray[i] > shortestCostArray[currentNodeIndex] + graph[currentNodeIndex][i]) && graph[currentNodeIndex][i] != 0) {     //  && graph[currentNodeIndex][i] != 0
                // Remove the Adjacent Node from the Queue Temporarily
                dequeue(shortestCostArray, i, priorityQueue);
                // Update shortestCostArray with New Shortest Costs
                shortestCostArray[i] = shortestCostArray[currentNodeIndex] + graph[currentNodeIndex][i];
                // Update Predecessor Array
                predecessorArray[i] = currentNodeIndex;
                // Reinsert the Updated QueueItem back into PQ
                enqueue(i, shortestCostArray[i], priorityQueue);
            }
        }
    }
    printSolution(shortestCostArray, V);
}

/**
 *  Helper Functions for Implementing an Array as a Priority Queue
 */

/**
 * @brief Enqueues a Node to the End of the Array
 * 
 * @param nodeValue 
 * @param shortestPathCost 
 */
void enqueue(int nodeValue, int shortestPathCost, PriorityQueueItem* priorityQueue)
{
    // Increase the Size of the Queue by Moving the PQ Pointer
    sizeQueue += 1;    // If Empty, will cause it to be index 0 for first iteration

    // Insert the Element into the Queue
    priorityQueue[sizeQueue].nodeValue = nodeValue;
    priorityQueue[sizeQueue].shortestPathCost = shortestPathCost;
}

/**
 * @brief Helper Function to retrieve NodeValue with the Highest Priority
 * 
 * @param shortestCostArray 
 * @return int 
 */
int peek(int shortestCostArray[], PriorityQueueItem* priorityQueue)
{
    // Set HP to the lowest possible value so that it can be replaced by any value that is higher
    int lowestCost = INT_MAX;
    int index = -1;

    // Determine the element with the highest priority
    for (int i{0}; i <= sizeQueue; i += 1)  // <= sizeQueue since it represents the Index
    {
        // If Priority(cost equally low) is the same, pick the node with the higher value
        if (lowestCost > priorityQueue[i].shortestPathCost) {
            // Set the Node with a lower cost as new lowest
            lowestCost = priorityQueue[i].shortestPathCost;
            index = i;
        }
    }

    // Returns the Position of the Node with Lowest Cost
    // printf("Node with Current Lowest Cost: %d\n", priorityQueue[index].nodeValue);
    // Return the Index of the Desired Node in Priority Queue
    return priorityQueue[index].nodeValue;
}

/**
 * @brief Helper Function to remove a specified Node Value
 * 
 * @param shortestCostArray 
 * @param targetNode 
 */
void dequeue(int shortestCostArray[], int targetNode, PriorityQueueItem* priorityQueue)
{
    // Find the Element with the Highest Priority
    // int indexHighestPriority = peek(shortestCostArray);
    // printf("Dequeued Node: %d\n", targetNode);

    // Remove the Element by Shifting all the Elements after it by 1 to the Left
    bool targetfound = false;
    for (int i{0}; i < sizeQueue; i += 1)
    {
        if (priorityQueue[i].nodeValue == targetNode) {
            targetfound = true;   
        }
        if (targetfound) {
            priorityQueue[i] = priorityQueue[i+1]; 
        }
    }
    // Assigning the Last Element of the Priority Queue
    priorityQueue[sizeQueue].nodeValue = -1;
    priorityQueue[sizeQueue].shortestPathCost = INFINITYXY;

    // Decrease the size of the Priority Queue
    sizeQueue -= 1;
}

/**
 * @brief Utility Function to print out the Shortest Distances from the Source Vertex to each Node
 * 
 * @param dist 
 */
    void printSolution(int* dist, int V)
{
    std::cout << "Vertex \t Distance from Source" << std::endl;
    for (int i = 0; i < V; i++)
        std::cout << i << " \t\t\t\t" << dist[i] << std::endl;
}