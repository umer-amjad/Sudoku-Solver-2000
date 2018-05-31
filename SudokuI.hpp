// 
// SudokuI.hpp - Sudoku Interface class 
//

#ifndef SUDOKUI_HPP
#define SUDOKUI_HPP

typedef std::pair<int, std::vector<int>> PossVect;

struct PossVectCompare {
    inline bool operator()(const PossVect &a, const PossVect &b);
};

class SudokuI {
    std::vector<PossVect> allPossVect; //set of possibility vectors
public:
    Sudoku(){}; //empty sudoku
    Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entryList); //constructor takes in array representing puzzle
    
    inline int& operator[](size_t index);
    inline int operator[](size_t index) const;
    
    bool isComplete() const;
    bool isDivergent() const;
    bool invalidPuzzle() const; // invalid if no numbers possible at some position
    std::deque<Sudoku> neighbours();
    Sudoku fillPossibles();
    std::string emptyPositionsPossibilities() const;
    
    void toString() const; //operator << calls print, which is overloaded appropriately
    
    friend bool operator< (Sudoku const& sud1, Sudoku const& sud2);
    friend std::ostream& operator<< (std::ostream& o, const Sudoku& fn);
};



#endif /* SUDOKUI_HPP */

