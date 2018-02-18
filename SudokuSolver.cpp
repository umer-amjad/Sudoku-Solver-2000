//
//  SudokuSolver.cpp
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
    
    if(sud.invalidPuzzle()){
        return {sud, false};
    }
    
    auto nbrs = sud.neighbours();
    return solveVector(nbrs);
}

std::pair<Sudoku, bool> Solver::solveVector(std::vector<Sudoku>& nbrs){
    //std::cout << "SolveVector called" << std::endl; //debug
    auto firstResult = solve(nbrs[0]);
    if (!firstResult.second) {
        nbrs.erase(nbrs.begin()); //remove first element
        return solveVector(nbrs);
    }
    return firstResult;
}
