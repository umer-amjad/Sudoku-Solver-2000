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
#include <ostream>
#include <string>
#include <sstream>
#include <set>

constexpr int MAGNITUDE = 3;
constexpr int MAGNITUDE_SQR = MAGNITUDE * MAGNITUDE;
extern const std::vector<int> allPoss;

// Think of
// a b
// c d
// as: {a, b, c, d}

typedef std::pair<int, std::vector<int>> PossVect;

struct PossVectCompare {
    inline bool operator()(const PossVect &a, const PossVect &b) {
        if (a.second.size() == b.second.size())
            return a.first < b.first;
        return a.second.size() < b.second.size();
    }
};
class Sudoku {
private:
    static constexpr int MAGNITUDE_SQR = MAGNITUDE * MAGNITUDE;
    std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entry;
    std::vector<PossVect> allPossVect; //set of possibility vectors
    inline int rowNum(int pos);
    inline int colNum(int pos);
    inline int boxNum(int pos);
    std::vector<int> findPossibles(int i);
    
    Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntryList, std::vector<PossVect> newPossVect); //creating Sudokus when possVect has already been created (neighbours calculation)
    std::array<int, MAGNITUDE_SQR> row(int n);
    std::array<int, MAGNITUDE_SQR> col(int n);
    virtual std::array<int, MAGNITUDE_SQR> box(int n);
    PossVect popFirstPosVect();
    
    Sudoku createNeighbour(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entries, int index, int value, int possValue);
public:
    Sudoku(){}; //empty sudoku
    Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entryList);
    std::string showEmptyPos();
    bool isComplete();
    bool isDivergent();
    Sudoku fillPossibles();
    std::vector<Sudoku> neighbours();
    
    inline int& operator[](std::size_t index) {
        return entry[index];
    };
    inline int operator[](std::size_t index) const {
        return entry[index];
    };
    friend std::ostream& operator<< (std::ostream& o, const Sudoku& fn);
    friend bool operator<(Sudoku const& sud1, Sudoku const& sud2);
};

#endif /* Sudoku_hpp */
