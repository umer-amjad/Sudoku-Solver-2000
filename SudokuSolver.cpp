//
//  SudokuSolver.cpp
//

#include "SudokuSolver.hpp"

std::pair<Sudoku, bool> Solver::solve(Sudoku& sud){
    if (sud.isComplete()){
        return {sud, true};
    }
    
    while(!sud.isDivergent()){
        sud = sud.fillPossibles();
        if (sud.isComplete()){
            return {sud, true};
        }
    }
    
    auto nbrs = sud.neighbours();
    return solveSudokuNeighbours(nbrs);
}

std::pair<Sudoku, bool> Solver::solveSudokuNeighbours(std::deque<Sudoku>& nbrs){
    if (nbrs.size() == 0){
        return {Sudoku(), false};
    }
    auto firstResult = solve(nbrs[0]);
    if (!firstResult.second) {
        nbrs.pop_front();
        return solveSudokuNeighbours(nbrs);
    }
    return firstResult;
}

void Solver::exhaustiveSolve(Sudoku& sud, std::vector<Sudoku>& solutions){
    if (sud.isComplete()){
        solutions.emplace_back(sud);
        return;
    }
    
    while(!sud.isDivergent()){
        sud = sud.fillPossibles();
        if (sud.isComplete()){
            solutions.emplace_back(sud);
            return;
        }
    }
    
    auto nbrs = sud.neighbours();
    exhaustiveSolveSudokuNeighbours(nbrs, solutions);
}

void Solver::exhaustiveSolveSudokuNeighbours(std::deque<Sudoku>& nbrs, std::vector<Sudoku>& solutions){
    if (nbrs.size() == 0){
        return;
    }
    exhaustiveSolve(nbrs[0], solutions);
    nbrs.pop_front();
    exhaustiveSolveSudokuNeighbours(nbrs, solutions);
}
