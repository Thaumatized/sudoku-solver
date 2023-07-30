#include <stdio.h>
#include <string.h>

void printSudoku(char sudoku[9][9]);
void setSpot(char sudoku[9][9], char possible[9][9][9], char x, char y, char n, char* changed);

char main(char argc,char **argv)
{
 	char sudoku[9][9];
    sudoku[0][0] = 10; //Easy way to tell that sudoku got set is to see that this is less than 10.
 	char possible[9][9][9];

    char verbose = 0;

    for(char argNum = 1; argNum < argc; argNum++)
 	{
 		char varLength = strlen(argv[argNum]);
        if(varLength == 81) //This has to be the suppuku!
        {
            for(char i = 0; i < 81; i++)
            {
                if(i < varLength)
                {
                    sudoku[i%9][(i-(i%9))/9] = argv[argNum][i] - '0';
                }
            }
        }
        else if (varLength == 2 && strcmp(argv[argNum], "-v") == 0)
        {
            verbose = 1;
        }
        
 	}

    if(sudoku[0][0] >= 10)
    {
        printf("Sudoku not set.");
        return 1;
    }

    if(verbose)
    {
        printf("Before:\n");
        printSudoku(sudoku);
    }

    // Step one: Narrow down possibilities
    for(char x = 0; x < 9; x++)
    {
        for(char y = 0; y < 9; y++)
        {
            for(char n = 0; n < 9; n++)
            {
                // Place alerady taken
                if(sudoku[x][y])
                {
                    possible[x][y][n] = 0;
                    continue;
                }
                
                char continueOver = 0;

                // Row
                for(char x2 = 0; x2 < 9; x2++)
                {
                    if(x == x2)
                    {
                        continue;
                    }

                    if(sudoku[x2][y] == n+1)
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
                for(char y2 = 0; y2 < 9; y2++)
                {
                    if(y == y2)
                    {
                        continue;
                    }
                    if(sudoku[x][y2] == n+1)
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
                for(char x2 = x-(x%3); x2 < x-(x%3)+3; x2++)
                {
                    for(char y2 = y-(y%3); y2 < y-(y%3)+3; y2++)
                    {
                        if(x == x2 && y == y2)
                        {
                            continue;
                        }

                        if(sudoku[x2][y2] == n+1)
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

                if(continueOver)
                {
                    continue;
                }

                possible[x][y][n] = 1;
            }
        }
    }

    // Step two: figure out spots that we can fill and reduce possibilities with; repeat until done
    char changed = 1;
    while(changed)
    {
        changed = 0;
        // Spots with only one options
        for(char y = 0; y < 9; y++)
        {
            for(char x = 0; x < 9; x++)
            {
                char sum = 0;
                for(char n = 0; n < 9; n++)
                {
                    sum += possible[x][y][n];
                }

                if(sum == 1)
                {
                    for(char n = 0; n < 9; n++)
                    {
                        if(possible[x][y][n])
                        {
                            if(verbose)
                            {
                                printf("Set spot %i %i to %i by spot.\n", x+1, y+1, n+1);
                            }
                            setSpot(sudoku, possible, x, y, n, &changed);
                            break;
                        }
                    }
                }
            }
        }

        // Rows with only one option for a number
        for(char y = 0; y < 9; y++)
        {
            for(char n = 0; n < 9; n++)
            {
                char count = 0;
                for(char x = 0; x < 9; x++)
                {
                    if(possible[x][y][n] == 1)
                    {
                        count++;
                    }
                }

                if(count == 1)
                {
                    for(char x = 0; x < 9; x++)
                    {
                        if(possible[x][y][n] == 1)
                        {
                            if(verbose)
                            {
                                printf("Set spot %i %i to %i by row.\n", x+1, y+1, n+1);
                            }
                            setSpot(sudoku, possible, x, y, n, &changed);
                            break;
                        }
                    }
                }
            }
        }

        // Columns with only one option for a number
        for(char x = 0; x < 9; x++)
        {
            for(char n = 0; n < 9; n++)
            {
                char count = 0;
                for(char y = 0; y < 9; y++)
                {
                    if(possible[x][y][n] == 1)
                    {
                        count++;
                    }
                }

                if(count == 1)
                {
                    for(char y = 0; y < 9; y++)
                    {
                        if(possible[x][y][n] == 1)
                        {
                            if(verbose)
                            {
                                printf("Set spot %i %i to %i by column.\n", x+1, y+1, n+1);
                            }
                            setSpot(sudoku, possible, x, y, n, &changed);
                            break;
                        }
                    }
                }
            }
        }

        // Squares with only one option for a number
        for(char squareX = 0; squareX < 9; squareX += 3)
        {
            for(char squareY  = 0; squareY  < 9; squareY  += 3)
            {
                for(char n = 0; n < 9; n++)
                {
                    char count = 0;
                    for(char x = squareX; x < squareX+3; x++)
                    {
                        for(char y = squareY ; y < squareY +3; y++)
                        {
                            count += possible[x][y][n];
                        }
                    }   
                    
                    if(count == 1)
                    {
                        for(char x = squareX; x < squareX+3; x++)
                        {
                            for(char y = squareY ; y < squareY +3; y++)
                            {
                                if(possible[x][y][n] == 1)
                                {
                                    if(verbose)
                                    {
                                        printf("Set spot %i %i to %i by square.\n", x+1, y+1, n+1);
                                    }
                                    setSpot(sudoku, possible, x, y, n, &changed);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Advanced possibility narrowing
        /*
         * Apparently, according to https://sudoku.com/evil/ this is called XY-Wing Strategy
         * That is a way too cool name for what it is.
         * All it means is that when you know that a number will be in a certain row/column in a square
         * you can narrow out the possibility of said number being anywhere else on said row/column
         */
        for(char squareX = 0; squareX < 9; squareX += 3)
        {
            for(char squareY  = 0; squareY  < 9; squareY  += 3)
            {
                for(char n = 0; n < 9; n++)
                {
                    char xContains[3];
                    memset(xContains, 0, 3);
                    char yContains[3];
                    memset(yContains, 0, 3);

                    for(char x = 0; x < 3; x++)
                    {
                        for(char y = 0; y < 3; y++)
                        {
                            if(possible[squareX+x][squareY+y][n] == 1)
                            {
                                xContains[x] = 1;
                                yContains[y] = 1;
                            }
                        }
                    }

                    if(xContains[0]+xContains[1]+xContains[2] == 1)
                    {
                        for (char x = 0; x < 3; x++)
                        {
                            if(xContains[x] == 0)
                            {
                                continue;
                            }

                            char advancedNarrowingChanged = 0;

                            for (char y = 0; y < 9; y++)
                            {
                                if (y < squareY  || y > squareY  + 2)
                                {
                                    if (possible[squareX+x][y][n] == 1)
                                    {
                                        changed = 1;
                                        advancedNarrowingChanged = 1;
                                        possible[squareX+x][y][n] = 0;
                                    }
                                }
                            }

                            if(verbose && advancedNarrowingChanged)
                            {
                                printf("Advanced narrowing on square %i on x %i num %i.\n", (squareX/3+1)+(squareY/3*3), x+1, n+1);
                            }
                        }
                        
                    }
                    
                    if(yContains[0]+yContains[1]+yContains[2] == 1)
                    {
                        for (char y = 0; y < 3; y++)
                        {
                            if(yContains[y] == 0)
                            {
                                continue;
                            }

                            char advancedNarrowingChanged = 0;

                            for (char x = 0; x < 9; x++)
                            {
                                if (x < squareX || x > squareX + 2)
                                {
                                    if (possible[x][squareY+y][n])
                                    {
                                        changed = 1;
                                        advancedNarrowingChanged = 1;
                                        possible[x][squareY+y][n] = 0;
                                    }
                                }
                            }

                            if(verbose && advancedNarrowingChanged)
                            {
                                printf("Advanced narrowing on square %i on y %i num %i.\n", (squareX/3+1)+(squareY/3*3), y+1, n+1);
                            }
                        }
                        
                    }
                }
            }
        }
            
        // Reverse Advanced possibility narrowing
        /*
         * If all possible spots for a number on a row/column are in the same square,
         * the rest of that square is free from said number
         */
        // Reverse Advanced possibility narrowing rows
        for(char n = 0; n < 9; n++)
        {
            for (char y = 0; y < 9; y++)
            {
                char squaresContainNumber[3];
                memset(squaresContainNumber, 0, 3);
                
                if(possible[0][y][n] == 1 || possible[1][y][n] == 1 || possible[2][y][n] == 1)
                {
                    squaresContainNumber[0] = 1;
                }
                if(possible[3][y][n] == 1 || possible[4][y][n] == 1 || possible[5][y][n] == 1)
                {
                    squaresContainNumber[1] = 1;
                }
                if(possible[6][y][n] == 1 || possible[7][y][n] == 1 || possible[8][y][n] == 1)
                {
                    squaresContainNumber[2] = 1;
                }

                if (squaresContainNumber[0] + squaresContainNumber[1] + squaresContainNumber[2] == 1)
                {
                    char squareX = 0;
                    if(squaresContainNumber[0] == 1) { squareX = 0; }
                    if(squaresContainNumber[1] == 1) { squareX = 3; }
                    if(squaresContainNumber[2] == 1) { squareX = 6; }

                    char reverseAdvancedNarrowingChanged = 0;

                    for (char y2 = y-(y%3); y2 < y-(y%3)+3; y2++)
                    {
                        if(y2==y)
                        {
                            continue;
                        }

                        for (char x = squareX; x < squareX+3; x++)
                        {
                            if (possible[x][y2][n] == 1)
                            {
                                changed = 1;
                                reverseAdvancedNarrowingChanged = 1;
                                possible[x][y2][n] = 0;
                            }
                        }
                    }

                    if(verbose && reverseAdvancedNarrowingChanged)
                    {
                        printf("Reverse Advanced Narrowing on square %i on y %i num %i.\n", (squareX/3+1)+((y-(y%3))/3*3), y%3+1, n+1);
                    }
                }
            }
        }

        // Reverse Advanced possibility narrowing columns
        for(char n = 0; n < 9; n++)
        {
            for (char x = 0; x < 9; x++)
            {
                char squaresContainNumber[3];
                memset(squaresContainNumber, 0, 3);
                
                if(possible[x][0][n] == 1 || possible[x][1][n] == 1 || possible[x][2][n] == 1)
                {
                    squaresContainNumber[0] = 1;
                }
                if(possible[x][3][n] == 1 || possible[x][4][n] == 1 || possible[x][5][n] == 1)
                {
                    squaresContainNumber[1] = 1;
                }
                if(possible[x][6][n] == 1 || possible[x][7][n] == 1 || possible[x][8][n] == 1)
                {
                    squaresContainNumber[2] = 1;
                }

                if (squaresContainNumber[0] + squaresContainNumber[1] + squaresContainNumber[2] == 1)
                {
                    char squareY = 0;
                    if(squaresContainNumber[0] == 1) { squareY = 0; }
                    if(squaresContainNumber[1] == 1) { squareY = 3; }
                    if(squaresContainNumber[2] == 1) { squareY = 6; }

                    char reverseAdvancedNarrowingChanged = 0;

                    for (char x2 = x-(x%3); x2 < x-(x%3)+3; x2++)
                    {
                        if(x2==x)
                        {
                            continue;
                        }

                        for (char y = squareY; y < squareY + 3; y++)
                        {
                            if (possible[x2][y][n] == 1)
                            {
                                changed = 1;
                                reverseAdvancedNarrowingChanged = 1;
                                possible[x2][y][n] = 0;
                            }
                        }
                    }

                    if(verbose && reverseAdvancedNarrowingChanged)
                    {
                        printf("Reverse Advanced Narrowing on square %i on x %i num %i.\n", ((x-(x%3))/3+1)+(squareY/3*3), x%3+1, n+1);
                    }
                }                
            }
        }

        //Very advanced possibility narrowing
        /*
         * (WHERE X = 2-8)
         * When a row/column contains X cells which all have the same X possibilities and no others
         * We can quarantee that in said column/row those X numbers will be in those X spots
         * and thus we can eliminate them from all others in said row/column
         */
        // Very advanced possibility narrowing rows
        for(char y = 0; y < 9; y++)
        {
            //Since we will be comparing to everything in the row after this we dont need to check the last one
            for(char x = 0; x < 8; x++)
            {
                char spotPossible[9];
                char spotPossibleCount = 0;
                char matches = 0;
                for(char n = 0; n < 9; n++)
                {
                    spotPossible[n] = possible[x][y][n];
                    if(spotPossible[n])
                    {
                        spotPossibleCount++;
                    }
                }

                if (spotPossibleCount < 2 || spotPossibleCount > 8)
                {
                    continue;
                }

                char matchX[spotPossibleCount];
                memset(matchX, 0, spotPossibleCount);
                matchX[0] = x;

                for (char x2 = x+1; x2 < 9; x2++)
                {
                    char match = 1;
                    for(char n = 0; n < 9; n++)
                    {
                        if(spotPossible[n] != possible[x2][y][n])
                        {
                            match = 0;
                            break;
                        }
                    }
                    if(match == 1)
                    {
                        matches++;
                        matchX[matches] = x2;
                    }
                }
                
                //Yup, we should do Very advanced possibility narrowing
                if(matches == spotPossibleCount - 1)
                {
                    char match = 0;
                    char changedOnVeryAdvancedNarrowing = 0;
                    for (char x2 = 0; x2 < 9; x2++)
                    {
                        if(x2 == matchX[match])
                        {
                            match++;
                            continue;
                        }
                        for(char n = 0; n < 9; n++)
                        {
                            if (spotPossible[n])
                            {
                                possible[x2][y][n] = 0;
                                changed = 1;
                                changedOnVeryAdvancedNarrowing = 1;
                            }
                        }
                    }

                    if(verbose && changedOnVeryAdvancedNarrowing)
                    {
                        printf("Very advanced narrowing on spots ");
                        for(char match = 0; match < matches + 1; match++)
                        {
                            if (match != 0)
                            {
                                printf(", ");
                            }
                            
                            printf("%i %i", matchX[match]+1, y+1);
                        }
                        printf(" numbers");
                        for (char n = 0; n < 9; n++)
                        {
                            if(spotPossible[n])
                            {
                                printf(" %i", n+1);
                            }
                        }
                        printf(".\n");
                    }
                }
            }
        }
        
        // Very advanced possibility narrowing columns
        for(char x = 0; x < 9; x++)
        {
            //Since we will be comparing to everything in the row after this we dont need to check the last one
            for(char y = 0; y < 8; y++)
            {
                char spotPossible[9];
                char spotPossibleCount = 0;
                char matches = 0;
                for(char n = 0; n < 9; n++)
                {
                    spotPossible[n] = possible[x][y][n];
                    if(spotPossible[n])
                    {
                        spotPossibleCount++;
                    }
                }

                if (spotPossibleCount < 2 || spotPossibleCount > 8)
                {
                    continue;
                }

                char matchY[spotPossibleCount];
                memset(matchY, 0, spotPossibleCount);
                matchY[0] = y;

                for (char y2 = y+1; y2 < 9; y2++)
                {
                    char match = 1;
                    for(char n = 0; n < 9; n++)
                    {
                        if(spotPossible[n] != possible[x][y2][n])
                        {
                            match = 0;
                            break;
                        }
                    }
                    if(match == 1)
                    {
                        matches++;
                        matchY[matches] = y2;
                    }
                }
                
                //Yup, we should do Very advanced possibility narrowing
                if(matches == spotPossibleCount - 1)
                {
                    char match = 0;
                    char changedOnVeryAdvancedNarrowing = 0;
                    for (char y2 = 0; y2 < 9; y2++)
                    {
                        if(y2 == matchY[match])
                        {
                            match++;
                            continue;
                        }
                        for(char n = 0; n < 9; n++)
                        {
                            if (spotPossible[n])
                            {
                                possible[x][y2][n] = 0;
                                changed = 1;
                                changedOnVeryAdvancedNarrowing = 1;
                            }
                        }
                    }

                    if(verbose && changedOnVeryAdvancedNarrowing)
                    {
                        printf("Very advanced narrowing on spots ");
                        for(char match = 0; match < matches + 1; match++)
                        {
                            if (match != 0)
                            {
                                printf(", ");
                            }
                            
                            printf("%i %i", x+1, matchY[match]+1);
                        }
                        printf(" numbers");
                        for (char n = 0; n < 9; n++)
                        {
                            if(spotPossible[n])
                            {
                                printf(" %i", n+1);
                            }
                        }
                        printf(".\n");
                    }
                }
            }
        }
    }

    printf("After:\n");
    printSudoku(sudoku);
}

void printSudoku(char sudoku[9][9])
{
    for(char i = 0; i < 81; i++)
    {
        if(sudoku[i%9][(i-(i%9))/9] != 0)
            printf("%i", sudoku[i%9][(i-(i%9))/9]);
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


// n = number - 1
void setSpot(char sudoku[9][9], char possible[9][9][9], char x, char y, char n, char* changed)
{
    sudoku[x][y] = n+1;
    // Spot
    for (char n2 = 0; n2 < 9; n2++)
    {
        possible[x][y][n2] = 0;
    }
    

    // Row
    for(char x2 = 0; x2 < 9; x2++)
    {
        possible[x2][y][n] = 0;
    }

    // Column
    for(char y2 = 0; y2 < 9; y2++)
    {
        possible[x][y2][n] = 0;
    }

    //Squares
    char squareX = x-(x%3);
    char squareY = y-(y%3);
    for(char x2 = squareX; x2 < squareX+3; x2++)
    {
        for(char y2 = squareY; y2 < squareY+3; y2++)
        {
            possible[x2][y2][n] = 0;
        }
    }

    *changed = 1;
}