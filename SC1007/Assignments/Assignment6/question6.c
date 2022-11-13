#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of vertices in the graph

int count = 0; // count the number of solutions
int V; //number of regions

/* A utility function to print solution */
void printSolution(int* color)
{
    printf(
        "Solution Exists:"
        " Following are the assigned colors \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", color[i]);
    printf("\n");
}
 
/* A utility function to check if
   the current color assignment
   is safe for vertex v i.e. checks
   whether the edge exists or not
   (i.e, graph[v][i]==1). If exist
   then checks whether the color to
   be filled in the new vertex(c is
   sent in the parameter) is already
   used by its adjacent
   vertices(i-->adj vertices) or
   not (i.e, color[i]==c) */
int isSafe(
    int v, int** graph,
    int* color, int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return 0;
    return 1;
}
 
/* A backtracking function
to solve m coloring problem */
int graphColoring(
    int** graph, int m,
    int* color, int v)
{
    int numColors = m, currentIndex = v, numRegions = V;
    // Base Case
    if (currentIndex == (numRegions - 1))
    {
        int result = 1;
        // Check if any of the Colours are valid
        for (int i = 0; i < numColors; i += 1)
        {
            int colour = i + 1;
            // Solution Found
            if (isSafe(currentIndex, graph, color, i+1) == 1)
            {
                count += 1;
                result = 0;
            }
        }

        return result; // 0 means Solution found
    }

    // Recursive Case
    int solution = 0;
    for (int i = 0; i < numColors; i += 1)
    {
        if (currentIndex == 0)
        {
            // Reset for First Index
            for (int j = 0; j < numRegions; j += 1)
            {
                color[j] = 0;
            }
        }

        // Check if Colour is safe
        if (isSafe(currentIndex, graph, color, i+1) == 1)
        {
            int currentColor = i + 1;
            // Assign the Current Colour
            color[currentIndex] = currentColor;

            // Recursively Check the Subsequent Columns
            if (graphColoring(graph, numColors, color, (currentIndex + 1)) == 0)
            {
                // Check the other Colours for other possible solutions
                solution = 1;
                continue;
            }

            // If Colour is not solution
            color[currentIndex] = 0;
        }

    }

    if (solution == 1)
    {
        // Success
        // Have to set the Current Index to 0 before going to an earlier Index
        // This is because in an earlier index, the later indexes should not be coloured yet
        color[currentIndex] = 0;
        return 0;
    }
    return 1;
    
}


int main()
{
    int m;
    int **graph;
    int *color;
    
    printf("Enter number of colors:\n");
    scanf("%d",&m);
    
    printf("Enter number of regions:\n");
    scanf("%d",&V);
    
    int i,j;
    color = (int *) malloc(V*sizeof(int));
    graph = (int **) malloc(V*sizeof(int *));
    
    for (i=0;i<V;i++)
        graph[i] = (int *) malloc(V*sizeof(int));
    
    printf("Input the adjacency matrix:\n");
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
             scanf("%d",&graph[i][j]);
    
 
    // Initialize all color values as 0.
    for (i = 0; i < V; i++)
        color[i] = 0;
 
    graphColoring(graph, m, color, 0);
        
    printf("There is/are total %d solution(s)\n", count);
    return 0;
}

