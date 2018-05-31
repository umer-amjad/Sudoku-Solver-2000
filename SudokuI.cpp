//
// SudokuI.cpp
//

#include "SudokuI.hpp"

bool operator<(SudokuI const& sud1, SudokuI const& sud2){
    if (sud1.allPossVect.size() == 0 || sud2.allPossVect.size() == 0) // no possibilities in lowest
        return sud1.allPossVect.size() < sud2.allPossVect.size();
    int size1 = (int) sud1.allPossVect.back().second.size();
    int size2 = (int) sud2.allPossVect.back().second.size();
    return size1 < size2;
}

std::ostream& operator<< (std::ostream& o, const SudokuI& sud){
    o << sud.toString();
    return o;
}


