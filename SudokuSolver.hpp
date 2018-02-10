//
//  SudokuSolver.hpp
//  PD Tests
//
//  Created by H263353 on 12/5/17.
//  Copyright © 2017 Me. All rights reserved.
//

#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include <iostream>

#include "Sudoku.hpp"


namespace Solver{
    std::pair<Sudoku, bool> solve(Sudoku& sud);
    std::pair<Sudoku, bool> solveVector(std::vector<Sudoku>& nbrs);
};

#endif /* SudokuSolver_hpp */
