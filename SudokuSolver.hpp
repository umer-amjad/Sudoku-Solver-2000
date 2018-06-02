//
//  SudokuSolver.hpp
//

#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include <iostream>

#include "SudokuI.hpp"
#include <memory>

namespace Solver {
    // given a sudoku puzzle, if a solution is found, returns {Solution, true}
    // if no solution is found, second component is false
    std::pair<std::shared_ptr<SudokuI>, bool> solve(std::shared_ptr<SudokuI> sud);
    std::pair<std::shared_ptr<SudokuI>, bool> solveSudokuNeighbours(std::deque<std::shared_ptr<SudokuI>>& nbrs);
    
    // given a sudoku puzzle, populates "solutions" with ALL POSSIBLE solutions
    // to the puzzle
    void exhaustiveSolve(std::shared_ptr<SudokuI> sud, std::vector<std::shared_ptr<SudokuI>>& solutions);
    void exhaustiveSolveSudokuNeighbours(std::deque<std::shared_ptr<SudokuI>>& nbrs, std::vector<std::shared_ptr<SudokuI>>& solutions);
};

#endif /* SudokuSolver_hpp */
