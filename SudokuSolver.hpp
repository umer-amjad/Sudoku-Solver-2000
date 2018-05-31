//
//  SudokuSolver.hpp
//

#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include <iostream>

#include "Sudoku.hpp"

namespace Solver {
    // given a sudoku puzzle, if a solution is found, returns {Solution, true}
    // if no solution is found, second component is false
    std::pair<Sudoku, bool> solve(Sudoku& sud);
    std::pair<Sudoku, bool> solveSudokuNeighbours(std::deque<Sudoku>& nbrs);
    
    // given a sudoku puzzle, populates "solutions" with ALL POSSIBLE solutions
    // to the puzzle
    void exhaustiveSolve(Sudoku& sud, std::vector<Sudoku>& solutions);
    void exhaustiveSolveSudokuNeighbours(std::deque<Sudoku>& nbrs, std::vector<Sudoku>& solutions);
};

#endif /* SudokuSolver_hpp */
