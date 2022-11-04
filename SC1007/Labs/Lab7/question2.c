#include <stdio.h>
#include <stdlib.h>

int nQueens(int** board, int N, int col);
int isSafe(int** board,int N, int row, int col);
void printSolution(int** board, int N);

int main()
{
    int **board;
    int BSize;

    int i,j;

    printf("Enter the size of chessBoard:\n");
    scanf("%d",&BSize);

    board = (int **)malloc(BSize*sizeof(int *));
    for(i=0;i<BSize;i++)
        board[i] = (int *)malloc(BSize*sizeof(int));

    for(i=0;i<BSize;i++)
       for(j=0;j<BSize;j++)
           board[i][j] = 0;

    if (!nQueens(board, BSize, 0))
    	printf("Solution does not exist");
    else
        printSolution(board, BSize);
    return 0;
}

int nQueens(int** board, int BSize, int col)
{
    // BSize is the size of the Chessboard, while Column is which column we are in right now
    // Base Case
    if (col >= BSize)
    {
        // Return True since we can reach end of Chess Board
        return 1;
    }

    // Check if there is a position to place the Queen
    for (int i = 0; i < BSize; i += 1)
    {
        // Check if Safe
        if (isSafe(board, BSize, i, col) == 1)
        {
            // Is Safe; Place the Queen in Position
            board[i][col] = 1;
            // Recursively Check if Subsequent Columns can place the Queen
            if (nQueens(board, BSize, (col+1)) == 1)
            {
                // Return True as well if Receive True
                return 1;
            }
            // If reach here, means subsequent columns cannot place a Queen; Remove
            board[i][col] = 0;

        }
    }

    // Return False as No way to put Queen
    return 0;
}

//Safe checking
int isSafe(int** board,int BSize, int row, int col)
{
    int i, j;

    // Horicatal check
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Upper left diagonal check
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Lower left diagonal check
    for (i = row, j = col; j >= 0 && i < BSize; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void printSolution(int** board, int BSize)
{
    int i,j;
    for (i = 0; i < BSize; i++) {
        for (j = 0; j < BSize; j++){
            if(board[i][j]==1)
                printf(" Q ");
            else
                printf(" + ");
        }
        printf("\n");
    }
    printf("\n");
}
