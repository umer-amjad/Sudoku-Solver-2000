//
//  SudokuI.cpp
//

#include "SudokuI.hpp"

bool SudokuI::isComplete() const {
    return (allPossVect.size() == 0);
}

bool SudokuI::isDivergent() const {
    if (allPossVect.back().second.size() == 0){
        return true;
    }
    return allPossVect.back().second.size() > 1;
}

bool SudokuI::invalidPuzzle() const {
    return allPossVect.back().second.size() == 0;
}

std::string SudokuI::emptyPositionsPossibilities() const {
    std::stringstream result;
    //std::cout << "Set size is " << allPossVect.size() << '\n'; debug
    for (auto possVect : allPossVect){
        result << possVect.first << ": {";
        for (int poss : possVect.second){
            result << " " << poss << ",";
        }
        result << "}\n";
    }
    return result.str();
}

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


