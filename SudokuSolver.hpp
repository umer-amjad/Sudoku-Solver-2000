//
//  SudokuSolver.hpp
//

#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include <iostream>

#include "Sudoku.hpp"

namespace Solver{
    std::pair<Sudoku, bool> solve(Sudoku& sud);
    std::pair<Sudoku, bool> solveVector(std::deque<Sudoku>& nbrs);
};

#endif /* SudokuSolver_hpp */
