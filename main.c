#include <stdio.h>
#include <string.h>

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
                    sudoku[i-(i%9)][i%9] = argv[1][i] - '0';
                }
            }
        }
 	}

    if(sudoku[0][0] >= 10)
    {
        printf("Sudoku not set.");
        return 1;
    }

    for(int x = 0; x < 9; x++)
    {
        for(int y = 0; y < 9; y++)
        {
            for(int n = 0; n < 9; n++)
            {
                possible[x][y][n] = 1;
            }
        }
    }
}