#include <iostream>
#include <chrono>

using namespace std::chrono;

// Define the Number of Vertices
#define V 9
#define INFINITY 9999999

// Custom Data Types
struct PriorityQueueItem
{
    int nodeValue{};
    int shortestPathCost{};
};

void printSolution(int dist[]);
void dijkstra(int graph[V][V], int srcNode);
void enqueue(int nodeValue, int shortestPathCost);
int peek(int shortestCostArray[]);
void dequeue(int shortestCostArray[], int targetNodeIndex);

// Creating a Priority Queue and its Pointer
PriorityQueueItem priorityQueue[V]{};
int sizeQueue{-1};

int main()
{
    // Creating an Example Graph
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    auto startTime = high_resolution_clock::now();
    dijkstra(graph, 0);
    auto endTime = high_resolution_clock::now();

    auto timeTaken = duration_cast<microseconds>(endTime - startTime);
    std::cout << "Time taken for Dijkstra using Arrays as Priority Queue: " << timeTaken.count() << " microseconds" << std::endl;

    return 0;
}



void dijkstra(int graph[V][V], int srcNode)
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
        shortestCostArray[i] = INFINITY;
    }

    // Cost of Source is 0 since we start there
    shortestCostArray[srcNode] = 0;
    predecessorArray[srcNode] = srcNode;
    
    // Place all the Vertices in a Priority Queue [An Array for Part A]
    for (int i{0}; i < V; i += 1) {
        // Adding Nodes into the Queue by their Index Position
        enqueue(i, shortestCostArray[i]);
    }

    // Extracting the Node with the lowest costs
    while (sizeQueue != -1) {
        // Remove Current Node from Queue
        int currentNodeIndex = peek(shortestCostArray);
        // Include it in our Solution
        solutionArray[currentNodeIndex] = 1;
        dequeue(shortestCostArray, currentNodeIndex);

        // Updating Adjacent Nodes to Current Node to reflect new costs
        for (int i{0}; i < V; i += 1) {
            // If Adjacent is not in Solution Array and the Old Cost of the Node is Higher, replace with current path.
            if ((solutionArray[priorityQueue[i].nodeValue] != 1) && (shortestCostArray[i] > shortestCostArray[currentNodeIndex] + graph[currentNodeIndex][i]) && graph[currentNodeIndex][i] != 0) {     //  && graph[currentNodeIndex][i] != 0
                // Remove the Adjacent Node from the Queue Temporarily
                dequeue(shortestCostArray, i);
                // Update shortestCostArray with New Shortest Costs
                shortestCostArray[i] = shortestCostArray[currentNodeIndex] + graph[currentNodeIndex][i];
                // Update Predecessor Array
                predecessorArray[i] = currentNodeIndex;
                // Reinsert the Updated QueueItem back into PQ
                enqueue(i, shortestCostArray[i]);
            }
        }
    }
    printSolution(shortestCostArray);
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
void enqueue(int nodeValue, int shortestPathCost)
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
int peek(int shortestCostArray[])
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
    printf("Node with Current Lowest Cost: %d\n", priorityQueue[index].nodeValue);
    // Return the Index of the Desired Node in Priority Queue
    return priorityQueue[index].nodeValue;
}

/**
 * @brief Helper Function to remove a specified Node Value
 * 
 * @param shortestCostArray 
 * @param targetNode 
 */
void dequeue(int shortestCostArray[], int targetNode)
{
    // Find the Element with the Highest Priority
    // int indexHighestPriority = peek(shortestCostArray);
    printf("Dequeued Node: %d\n", targetNode);

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
    priorityQueue[sizeQueue].shortestPathCost = INFINITY;

    // Decrease the size of the Priority Queue
    sizeQueue -= 1;
}

/**
 * @brief Utility Function to print out the Shortest Distances from the Source Vertex to each Node
 * 
 * @param dist 
 */
void printSolution(int dist[])
{
    std::cout << "Vertex \t Distance from Source" << std::endl;
    for (int i = 0; i < V; i++)
        std::cout << i << " \t\t\t\t" << dist[i] << std::endl;
}