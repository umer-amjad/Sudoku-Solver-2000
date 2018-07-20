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

typedef std::pair<int, std::vector<int>> PossVect;

struct PossVectCompare {
    inline bool operator()(const PossVect &a, const PossVect &b);
};

bool PossVectCompare::operator()(const PossVect &a, const PossVect &b) {
    if (a.second.size() == b.second.size())
        return a.first > b.first;
    return a.second.size() > b.second.size();
}

class SudokuI {
protected:
    std::vector<PossVect> allPossVect; //set of possibility vectors
public:
    SudokuI() {};
    SudokuI(std::vector<PossVect> newPossVect): allPossVect(newPossVect) {}; //Populating possibilities vector
    
    bool isComplete() const;
    bool isDivergent() const;
    bool invalidPuzzle() const; // invalid if no numbers possible at some position
    
    std::string emptyPositionsPossibilities() const;
    
    virtual std::string toString() const = 0; //operator << calls print, which is overloaded appropriately
    
    friend bool operator< (SudokuI const& sud1, SudokuI const& sud2);
    friend std::ostream& operator<< (std::ostream& o, const SudokuI& fn);
};



#endif /* SUDOKUI_HPP */

