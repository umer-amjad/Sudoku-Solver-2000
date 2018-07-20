//
//  SudokuSolver.hpp
//

#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include <iostream>

#include "Sudoku.hpp"
#include <memory>

namespace Solver {
    // given a sudoku puzzle, if a solution is found, returns {Solution, true}
    // if no solution is found, second component is false

    template <int MAGNITUDE>
    std::pair<Sudoku<MAGNITUDE>, bool> solveSudokuNeighbours(std::list<Sudoku<MAGNITUDE>>&nbrs);

    template <int MAGNITUDE>
    std::pair<Sudoku<MAGNITUDE>, bool> solve(Sudoku<MAGNITUDE> sud) {
        if (sud.isComplete()) {
            return {sud, true};
        }

        while (!sud.isDivergent()) {
            sud = sud.fillPossibles();
            if (sud.isComplete()) {
                return {sud, true};
            }
        }

        auto nbrs = sud.neighbours();
        return solveSudokuNeighbours(nbrs);
    }

    template <int MAGNITUDE>
    std::pair<Sudoku<MAGNITUDE>, bool> solveSudokuNeighbours(std::list<Sudoku<MAGNITUDE>>&nbrs) {
        if (nbrs.size() == 0) {
            return {Sudoku<MAGNITUDE>(), false};
        }
        auto firstResult = solve(nbrs.front());
        if (!firstResult.second) {
            nbrs.pop_front();
            return solveSudokuNeighbours(nbrs);
        }
        return firstResult;
    }

    // given a sudoku puzzle, populates "solutions" with ALL POSSIBLE solutions
    // to the puzzle

    template <int MAGNITUDE>
    void exhaustiveSolveSudokuNeighbours(std::list<Sudoku<MAGNITUDE>>&nbrs, std::vector<Sudoku<MAGNITUDE>>&solutions);

    template <int MAGNITUDE>
    void exhaustiveSolve(Sudoku<MAGNITUDE> sud, std::vector<Sudoku<MAGNITUDE>>&solutions) {
        if (sud.isComplete()) {
            solutions.emplace_back(sud);
            return;
        }

        while (!sud.isDivergent()) {
            sud = sud.fillPossibles();
            if (sud.isComplete()) {
                solutions.emplace_back(sud);
                return;
            }
        }

        auto nbrs = sud.neighbours();
        exhaustiveSolveSudokuNeighbours(nbrs, solutions);
    }

    template <int MAGNITUDE>
    void exhaustiveSolveSudokuNeighbours(std::list<Sudoku<MAGNITUDE>>&nbrs, std::vector<Sudoku<MAGNITUDE>>&solutions) {
        if (nbrs.size() == 0) {
            return;
        }
        exhaustiveSolve(nbrs.front(), solutions);
        nbrs.pop_front();
        exhaustiveSolveSudokuNeighbours(nbrs, solutions);
    }
};

#endif /* SudokuSolver_hpp */
