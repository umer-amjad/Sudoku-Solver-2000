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
//    std::cout << sud.EmptyPositionsPossibilities();
//    if(sud.invalidPuzzle()){
//        return {sud, false};
//    }
    
    auto nbrs = sud.neighbours();
    return solveSudokuNeighbours(nbrs);
}

std::pair<Sudoku, bool> Solver::solveSudokuNeighbours(std::deque<Sudoku>& nbrs){
    //std::cout << "solveSudokuNeighbours called" << std::endl; //debug
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
        //std::cout << "A. Solution found! \n" << sud << std::endl;
        solutions.emplace_back(sud);
        return;
    }
    while(!sud.isDivergent()){
        //std::cout << "Possibles filled " << std::endl; //debug
        sud = sud.fillPossibles();
        if (sud.isComplete()){
            //std::cout << "B. Solution found! \n" << sud << std::endl;
            solutions.emplace_back(sud);
            return;
        }
    }
    //    std::cout << sud.EmptyPositionsPossibilities();
    //    if(sud.invalidPuzzle()){
    //        return {sud, false};
    //    }
    
    auto nbrs = sud.neighbours();
    exhaustiveSolveSudokuNeighbours(nbrs, solutions);
}

void Solver::exhaustiveSolveSudokuNeighbours(std::deque<Sudoku>& nbrs, std::vector<Sudoku>& solutions){
    //std::cout << "exhaustiveSolveSudokuNeighbours called" << std::endl; //debug
    if (nbrs.size() == 0){
        return;
    }
    exhaustiveSolve(nbrs[0], solutions);
    nbrs.pop_front();
    exhaustiveSolveSudokuNeighbours(nbrs, solutions);
}
