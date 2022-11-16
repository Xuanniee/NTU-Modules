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
    printf("\n");

    return 0;
}

void DFS_R(Graph g, int v)
{
    // More Recursive Version

    // Initialisation of Pointers
    int numVertices = g.V;
    int *visited = g.visited;
    int **adj_matrix = g.matrix;

    // Recursive Case
    int currentVertex = v;
    int counter = 0, counterInverse = 0, printed = 0;
    for (int i = 0; i < numVertices; i += 1)
    {
        if (visited[i] == 0)
        {
            counter += 1;
        }
    }

    for (int i = 0; i < numVertices; i += 1)
    {
        if ((adj_matrix[currentVertex-1][i] == 1) && (visited[i] != 1))
        {
            if ((counter == numVertices) && (printed == 0))
            {
                printf("%d ", currentVertex);
                visited[v-1] = 1;
                printed = 1;
            }
            visited[i] = 1;
            printf("%d ", i+1);
            DFS_R(g, i+1);
        }
        else
        {
            counterInverse += 1;
        }
    }

    // Base Case
    if (counterInverse == numVertices)
    {
        // No More Neighbour to Go
        return;
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