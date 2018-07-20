// 
// SudokuI.hpp - Sudoku Interface class 
//

#ifndef SUDOKUI_HPP
#define SUDOKUI_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <vector>
#include <ostream>
#include <string>
#include <sstream>
#include <set>
#include <utility>

struct PossibleAtIndex {
    int index;
    std::vector<int> possibles;
};

bool operator<(const PossibleAtIndex &a, const PossibleAtIndex &b) {
    if (a.possibles.size() == b.possibles.size())
        return a.index > b.index;
    return a.possibles.size() > b.possibles.size();
}

class SudokuI {
protected:
    std::vector<PossibleAtIndex> allPossibles; //set of possibility vectors
public:
    SudokuI() {};
    SudokuI(std::vector<PossibleAtIndex> newPossVect): allPossibles(newPossVect) {}; //Populating possibilities vector
    
    bool isComplete() const;
    bool isDivergent() const;
    bool invalidPuzzle() const; // invalid if no numbers possible at some position
    
    std::string emptyPositionsPossibilities() const;
    
    virtual std::string toString() const = 0; //operator << calls print, which is overloaded appropriately
    
    friend bool operator< (SudokuI const& sud1, SudokuI const& sud2);
    friend std::ostream& operator<< (std::ostream& o, const SudokuI& fn);
};



#endif /* SUDOKUI_HPP */

