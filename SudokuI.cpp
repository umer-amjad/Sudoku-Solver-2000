//
//  SudokuI.cpp
//

#include "SudokuI.hpp"

bool SudokuI::isComplete() const {
    return (allPossibles.size() == 0);
}

bool SudokuI::isDivergent() const {
    if (allPossibles.back().possibles.size() == 0){
        return true;
    }
    return allPossibles.back().possibles.size() > 1;
}

bool SudokuI::invalidPuzzle() const {
    return allPossibles.back().possibles.size() == 0;
}

std::string SudokuI::emptyPositionsPossibilities() const {
    std::stringstream result;
    //std::cout << "Set size is " << allPossVect.size() << '\n'; debug
    for (auto indPoss : allPossibles){
        result << indPoss.index << ": {";
        for (int poss : indPoss.possibles){
            result << " " << poss << ",";
        }
        result << "}\n";
    }
    return result.str();
}

bool operator<(SudokuI const& sud1, SudokuI const& sud2){
    if (sud1.allPossibles.size() == 0 || sud2.allPossibles.size() == 0) // no possibilities in lowest
        return sud1.allPossibles.size() < sud2.allPossibles.size(); 
    return sud1.allPossibles.back().possibles.size() < 
           sud2.allPossibles.back().possibles.size();
}

std::ostream& operator<< (std::ostream& o, const SudokuI& sud){
    o << sud.toString();
    return o;
}


