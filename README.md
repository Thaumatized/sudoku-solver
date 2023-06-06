to use tell the executable the sudoku by using it as a variable as a string of numbers, where 0 represents an empty space and the numbers represent themselves. Input the data from left to right and top to bottom. Like most people read.

eg. for this sudoku:

1--  ---  2-7  
---  9--  563  
---  7-2  -1-  
  
56-  4--  -3-
---  ---  7--  
974  ---  156  
  
249  -57  ---  
71-  -9-  3--  
---  1--  47-  
  
you should call
./sudokusolver 100000207000900563000702010560400030000000700974000156249057000710090300000100470

to compile us gcc:
gcc main.c -o sudokusolver