#include <stdio.h>
#include <stdlib.h>

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

////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

void DFS_R(Graph , int );

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
    DFS_R(g,i);

    return 0;
}

void DFS_R(Graph g, int v)
{
    // Visit the Neighbouring Vertices in Ascending Order using Depth First Search
    int numVertices = g.V;
    int numEdges = g.E, inputVertex = v;
    int ** adj_matrix = g.matrix;
    // g.visited is the Visited Matrix

    // Base Case
    int counter = 0;
    for (int i = 0; i < numVertices; i += 1)
    {
        if (g.visited[i] == 1)
        {
            counter += 1;
        }
    }
    if (counter == numVertices)
    {
        // All Vertices have been visited
        printf("\n");
        return;
    }


    // Recursive Case
    // Visit the Current Node
    g.visited[v-1] = 1;
    printf("%d ", v);
    // Iterate through all Adjacent Nodes to Current Node
    for (int i = 0; i < numVertices; i += 1)
    {
        // If Adjacent and Not Visited
        if ((adj_matrix[inputVertex-1][i] == 1) && (g.visited[i] == 0))
        {
            // Call Recursive Function to Visit the Node
            DFS_R(g, i+1);
        }

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
