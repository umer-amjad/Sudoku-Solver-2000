//
//  SudokuSolver.cpp
//  PD Tests
//
//  Created by H263353 on 12/5/17.
//  Copyright © 2017 Me. All rights reserved.
//

#include "SudokuSolver.hpp"

std::pair<Sudoku, bool> Solver::solve(Sudoku& sud){
    if (sud.isComplete()){
        return {sud, true};
    }
    while(!sud.isDivergent()){
        //std::cout << "Possibles filled " << std::endl; //debug
        sud = sud.fillPossibles();
        if (sud.isComplete()){
            return {sud, true};
        }
    }
    auto nbrs = sud.neighbours();
    return solveVector(nbrs);
}

std::pair<Sudoku, bool> Solver::solveVector(std::vector<Sudoku>& nbrs){
    //std::cout << "SolveVector called" << std::endl; //debug
    if (nbrs.size() == 0){
        return {Sudoku(), false};
    }
    auto firstResult = solve(nbrs[0]);
    if (!firstResult.second) {
        nbrs.erase(nbrs.begin()); //remove first element
        return solveVector(nbrs);
    }
    return firstResult;
}
