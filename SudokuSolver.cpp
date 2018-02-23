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
//    std::cout << sud.showEmptyPos();
//    if(sud.invalidPuzzle()){
//        return {sud, false};
//    }
    
    auto nbrs = sud.neighbours();
    return solveVector(nbrs);
}

std::pair<Sudoku, bool> Solver::solveVector(std::deque<Sudoku>& nbrs){
    //std::cout << "SolveVector called" << std::endl; //debug
    if (nbrs.size() == 0){
        return {Sudoku(), false};
    }
    //auto firstResult = solve(nbrs.back());
    auto firstResult = solve(nbrs[0]);
    if (!firstResult.second) {
        //std::swap(nbrs[0], nbrs.back());
        //nbrs.pop_back();
        //nbrs.erase(nbrs.begin()); //remove first element
        nbrs.pop_front();
        return solveVector(nbrs);
    }
    return firstResult;
}
