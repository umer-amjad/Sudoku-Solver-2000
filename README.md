# Sudoku-Solver-2000 #

A sudoku solver written in C++, based on the algorithm used in my Sudoku Solver made in Racket, but with improvements making it up to 1000 times faster. Additionally, it can solve any n^2 by n^2 Sudoku puzzle.

### How To Use ###
The class template `Sudoku<int MAGNITUDE>` is provided to represent an MAGNITUDE<sup>2</sup> by MAGNITUDE<sup>2</sup> puzzle. It has a constructor which takes as an input an array of size MAGNITUDE<sup>2</sup> * MAGNITUDE<sup>2</sup>.

Then, the function `solve` can be called. If `sudoku` is the name of a variable of type `Sudoku<n>` for `n` some positive integer, then it can be solved by calling `solve(sudoku)`. This outputs a variable of type `pair<Sudoku<n>, bool>`. The second output in the pair of outputs is true if a solution was found, and false if the puzzle does not have any solutions. The first output in the pair of outputs is the solution if one was found.

If the input given is an ill-formed puzzle which allows for multiple solutions, only one solution is found. However, in this case, if one wants to find all possible solutions, one can use the `exhaustiveSolve` function, which takes as its first argument the Sudoku puzzle, and as a second argument (by reference) an empty vector of Sudoku puzzles. This second argument will be populated with all possible solutions.

The insertion operator `<<` has been overloaded to display a Sudoku puzzle. The output adjusts itself appropriately as needed depending on the size of the puzzle.

The project was written using C++14 and can be compiled accordingly. 

### Future Plans ###

Short term plans include:
- Increase algorithmic efficiency (this will be implemented in the "createNeighbour" function) (IN PROGRESS)
- More user-friendly command-line interface, to input puzzles in the command line instead of in the code itself

Long term plans include:
- Using an image detection library to solve Sudoku puzzles input as images
- Run algorithm multithreaded where possible, for faster solving
