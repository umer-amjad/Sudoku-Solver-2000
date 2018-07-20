// 
// SudokuI.hpp - Sudoku Interface class 
//

#ifndef SUDOKUI_HPP
#define SUDOKUI_HPP

#include <iosfwd>
#include <vector>
#include <string>

struct PossibleAtIndex {
    int index;
    std::vector<int> possibles;
};

inline bool operator<(const PossibleAtIndex &a, const PossibleAtIndex &b) {
    if (a.possibles.size() == b.possibles.size())
        return a.index > b.index;
    return a.possibles.size() > b.possibles.size();
}

class AbstractSudoku {
protected:
    std::vector<PossibleAtIndex> allPossibles; //set of possibility vectors
public:
    AbstractSudoku() {};
    AbstractSudoku(std::vector<PossibleAtIndex> newPossVect): allPossibles(newPossVect) {}; //Populating possibilities vector
    
    bool isComplete() const;
    bool isDivergent() const;
    bool invalidPuzzle() const; // invalid if no numbers possible at some position
    
    std::string emptyPositionsPossibilities() const;
    
    virtual std::string toString() const = 0; //operator << calls print, which is overloaded appropriately
    
    friend bool operator< (AbstractSudoku const& sud1, AbstractSudoku const& sud2);
    friend std::ostream& operator<< (std::ostream& o, const AbstractSudoku& fn);
};



#endif /* SUDOKUI_HPP */

