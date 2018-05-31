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
#include <deque>
#include <ostream>
#include <string>
#include <sstream>
#include <set>
#include <utility>

typedef std::pair<int, std::vector<int>> PossVect;

class SudokuI {
    std::vector<PossVect> allPossVect; //set of possibility vectors
public:
    SudokuI(){}; //empty sudoku
    
    virtual bool isComplete() const = 0;
    virtual bool isDivergent() const = 0;
    virtual bool invalidPuzzle() const = 0; // invalid if no numbers possible at some position
    virtual std::deque<SudokuI> neighbours() = 0;
    virtual SudokuI& fillPossibles() = 0;
    virtual std::string emptyPositionsPossibilities() const = 0;
    
    virtual std::string toString() const = 0; //operator << calls print, which is overloaded appropriately
    
    friend bool operator< (SudokuI const& sud1, SudokuI const& sud2);
    friend std::ostream& operator<< (std::ostream& o, const SudokuI& fn);
};



#endif /* SUDOKUI_HPP */

