# Sudoku-Solver-2000 #

A sudoku solver written in C++, based on the algorithm used in my Sudoku Solver made in Racket, but with improvements making it up to 1000 times faster. Additionally, it can solve any n^2 by n^2 Sudoku puzzle.

### How To Use: ###
Currently, one must set the "MAGNITUDE" field in Sudoku.h to be the "size" of the puzzle they're solving. A 1 by 1 sudoku has magnitude 1, a 4 by 4 sudoku has magnitude 2, a 9 by 9 sudoku has magnitude 3, and so on. Note that one always has an n^2 by n^2 sudoku puzzle, with magnitude n. 

Once this field is set, you can enter in your sudoku as an array in the first line of main.cpp. Running the program will then solve this puzzle, as well as display the time taken to solve 1000 identical puzzles to the one entered (but re-running the algorithm every time). If one just wants the solution, this timer can be commented out or removed. 

The first output in the pair of outputs <bool, Sudoku> is true if a solution was found, and false if the puzzle does not have any solutions. If the input given is an ill-formed puzzle which allows for multiple solution, only one solution is found. The insertion operator << has been overloaded to display a Sudoku puzzle. The output adjusts itself if the puzzle's magnitude is large enough that more than one digit is required per number. 

Note that the project was written using C++14, but the features used should allow compiling in older versions.

### Future Plans ###

Short term plans include:
- Increase algorithmic efficiency (this will be implemented in the "createNeighbour" function)
- Create a template out of the Sudoku class (with the template parameter being the size (or "MAGNITUDE") of the Sudoku) so that sudokus of different magnitudes can be solved without re-compiling the program
- More user-friendly command-line interface, to input puzzles in the command line instead of in the code itself

Long term plans include:
- Finding the set of all possible solutions for ill-formed puzzles, as well as the number of all possible solutions
- Using an image detection library to solve Sudoku puzzles input as images
