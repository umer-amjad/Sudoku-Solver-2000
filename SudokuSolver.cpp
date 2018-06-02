//
//  SudokuSolver.cpp
//

#include "SudokuSolver.hpp"

std::pair<std::shared_ptr<SudokuI>, bool> Solver::solve(std::shared_ptr<SudokuI> sudPtr){
    if (sudPtr->isComplete()){
        return {sudPtr, true};
    }
 
    while(!sudPtr->isDivergent()){
        sudPtr = sudPtr->fillPossibles();
        if (sudPtr->isComplete()){
            return {sudPtr, true};
        }
    }
    auto nbrs = sudPtr->neighbours();
    return solveSudokuNeighbours(nbrs);
}

std::pair<std::shared_ptr<SudokuI>, bool> Solver::solveSudokuNeighbours(std::deque<std::shared_ptr<SudokuI>>& nbrs){
    if (nbrs.size() == 0){
        return {nullptr, false};
    }
    auto firstResult = solve(nbrs[0]);
    if (!firstResult.second) {
        nbrs.pop_front();
        return solveSudokuNeighbours(nbrs);
    }
    return firstResult;
}

void Solver::exhaustiveSolve(std::shared_ptr<SudokuI> sudPtr, std::vector<std::shared_ptr<SudokuI>>& solutions){
    if (sudPtr->isComplete()){
        solutions.emplace_back(sudPtr);
        return;
    }
    
    while(!sudPtr->isDivergent()){
        sudPtr = sudPtr->fillPossibles();
        if (sudPtr->isComplete()){
            solutions.emplace_back(sudPtr);
            return;
        }
    }
    
    auto nbrs = sudPtr->neighbours();
    exhaustiveSolveSudokuNeighbours(nbrs, solutions);
}

void Solver::exhaustiveSolveSudokuNeighbours(std::deque<std::shared_ptr<SudokuI>>& nbrs, std::vector<std::shared_ptr<SudokuI>>& solutions){
    if (nbrs.size() == 0){
        return;
    }
    exhaustiveSolve(nbrs[0], solutions);
    nbrs.pop_front();
    exhaustiveSolveSudokuNeighbours(nbrs, solutions);
}
