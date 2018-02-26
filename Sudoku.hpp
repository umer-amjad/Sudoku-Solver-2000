//
//  Sudoku.hpp
// 

#ifndef Sudoku_hpp
#define Sudoku_hpp

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

constexpr int MAGNITUDE = 3;
constexpr int MAGNITUDE_SQR = MAGNITUDE * MAGNITUDE;
extern const std::vector<int> allPoss;

typedef std::pair<int, std::vector<int>> PossVect;

struct PossVectCompare {
    inline bool operator()(const PossVect &a, const PossVect &b);
};

//Example:
// Think of
// a b   c d
// e f   g h
//
// i j   k l
// m n   o p
// as:      {a, b, c, d, e, f, g, h, i, j,  k,  l,  m,  n,  o,  p}
// with
//  pos:    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
//  row(0): {a, b, c, d} and so on for row(1), row(2), row(3)
//  col(0): {a, e, i, m} and so on for col(1), col(2), col(3)
//  box(0): {a, b, e, f}
//  box(1): {c, d, g, h}
//  box(2): {i, j, m, n} and so on (i.e. boxes are read left to right, top to bottom)

class Sudoku {
private:
    std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entry;
    std::vector<PossVect> allPossVect; //set of possibility vectors
    
    //given a "pos", returns which row/col/box the pos lies on
    static inline int rowNum(int pos);
    static inline int colNum(int pos);
    static inline int boxNum(int pos);
    
    //returns nth the row/col/box
    std::array<int, MAGNITUDE_SQR> row(int n) const;
    std::array<int, MAGNITUDE_SQR> col(int n) const;
    std::array<int, MAGNITUDE_SQR> box(int n) const;
    
    // returns an array of bools, with the index of an element in the array specifies whether
    // the number representing that index is in the nth row/col/box
    // e.g. if rowFilled(6)[3] is true, then the number 3 is filled in in the 6th row
    std::array<bool, MAGNITUDE_SQR+1> rowFilled(int n) const;
    std::array<bool, MAGNITUDE_SQR+1> colFilled(int n) const;
    std::array<bool, MAGNITUDE_SQR+1> boxFilled(int n) const;

    // for the nth row/col/box, push_backs the pos's that are empty into the vector empty_pos
    void rowPopulateEmpties(int n, std::vector<int>& emptyPos) const;
    void colPopulateEmpties(int n, std::vector<int>& emptyPos) const;
    void boxPopulateEmpties(int n, std::vector<int>& emptyPos) const;

    Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntryList, std::vector<PossVect> newPossVect); //creating Sudokus when possVect has already been created (neighbours calculation)
    Sudoku createNeighbour(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entries, int index, int value, int possValue);
    
    std::vector<int> findPossibles(int i) const;
    
public:
    Sudoku(){}; //empty sudoku
    Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entryList); //constructor takes in array representing puzzle
    
    inline int& operator[](size_t index) {
        return entry[index];
    };
    inline int operator[](size_t index) const {
        return entry[index];
    };
    
    bool isComplete() const;
    bool isDivergent() const;
    bool invalidPuzzle() const; // invalid if no numbers possible at some position
    std::deque<Sudoku> neighbours();
    Sudoku fillPossibles();
    std::string EmptyPositionsPossibilities() const;
    
    friend bool operator< (Sudoku const& sud1, Sudoku const& sud2);
    friend std::ostream& operator<< (std::ostream& o, const Sudoku& fn);
};

#endif /* Sudoku_hpp */
