#include <stdio.h>
#include <string.h>

void printSudoku(char sudoku[9][9]);

int main(int argc,char **argv)
{
 	char sudoku[9][9];
    sudoku[0][0] = 10; //Easy way to tell that sudoku got set is to see that this is less than 10.
 	char possible[9][9][9];

    for(int argNum = 1; argNum < argc; argNum++)
 	{
 		int varLength = strlen(argv[argNum]);
        if(varLength == 81) //This has to be the suppuku!
        {
            for(int i = 0; i < 81; i++)
            {
                if(i < varLength)
                {
                    sudoku[(i-(i%9))/9][i%9] = argv[1][i] - '0';
                }
            }
        }
 	}

    if(sudoku[0][0] >= 10)
    {
        printf("Sudoku not set.");
        return 1;
    }

    printf("Before:\n");
    printSudoku(sudoku);

    // Step one: Narrow down possibilities
    for(int x = 0; x < 9; x++)
    {
        for(int y = 0; y < 9; y++)
        {
            for(int n = 0; n < 9; n++)
            {
                // Place alerady taken
                if(sudoku[x][y])
                {
                    possible[x][y][n] = 0;
                    continue;
                }
                
                int continueOver = 0;

                // Row
                for(int x2 = 0; x2 < 9; x2++)
                {
                    if(x == x2)
                    {
                        continue;
                    }

                    if(sudoku[x2][y] == n)
                    {
                        possible[x][y][n] = 0;
                        continueOver = 1;
                        break;
                    }
                }

                if(continueOver)
                {
                    continue;
                }

                // Column
                for(int y2 = 0; y2 < 9; y2++)
                {
                    if(y == y2)
                        continue;
                    if(sudoku[x][y2] == n)
                    {
                        possible[x][y][n] = 0;
                        continueOver = 1;
                        break;
                    }
                }

                if(continueOver)
                {
                    continue;
                }

                //Square
                for(int x2 = x-(x%3); x2 < x-(x%3)+3; x2++)
                {
                    for(int y2 = y-(y%3); y2 < y-(y%3)+3; y2++)
                    {
                        if(x == x2 && y == y2)
                        {
                            continue;
                        }

                        if(sudoku[x2][y2] == n)
                        {
                            possible[x][y][n] = 0;
                            continueOver = 1;
                            break;
                        }
                    }

                    if(continueOver)
                    {
                        continue;
                    }
                }
            }
        }
    }

    int changed = 1;
    while(changed)
    {
        changed = 0;
    }

    printf("After:\n");
    printSudoku(sudoku);
}

void printSudoku(char sudoku[9][9])
{
    for(int i = 0; i < 81; i++)
    {
        if(sudoku[(i-(i%9))/9][i%9] != 0)
            printf("%i", sudoku[(i-(i%9))/9][i%9]);
        else
            printf("-");

        if((i+1)%3 == 0)
            printf("  ");
        if((i+1)%9 == 0)
            printf("\n");
        if((i+1)%27 == 0)
            printf("\n");
    }
}