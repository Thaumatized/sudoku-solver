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

Some notes on online sudoku:
https://sudoku9x9.com/ is great. While they have a clunky interface they will actually tutor you trough on how to solve the sudokus.

https://sudoku.com/ sucks ass. They want you to watch ads, clearly, as hints are dependent on them. Sometimes, specificly on hard logic, a hint will just fill in some numbers. This feels like cheating for a sudoku site.


TODO:

Get this one working:
./sudokusolver -v 050000306600020004007900008000048000000200037004001000000000500070000020080053070
https://sudoku9x9.com/ (L5: #601553023)