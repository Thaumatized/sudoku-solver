to use tell the executable the sudoku by using it as a variable as a string of numbers, where 0 represents an empty space and the numbers represent themselves. Input the data from left to right and top to bottom. Like most people read.

eg. for this sudoku:

1-8  3-2  -7-  
---  --6  5--  
-2-  ---  ---  

-7-  2--  ---  
4-2  --3  --6  
-9-  ---  -4-  

---  -1-  --7  
9--  ---  ---  
3-4  8--  -1-  

you should call
./sudokusolver 108302070000006500020000000070200000402003006090000040000010007900000000304800010

to compile use gcc:
gcc main.c -o sudokusolver