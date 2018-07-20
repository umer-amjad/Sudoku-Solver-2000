//
//  AbstractSudoku.cpp
//

#include "AbstractSudoku.hpp"

#include <ostream>
#include <sstream>

bool AbstractSudoku::isComplete() const {
    return (allPossibles.size() == 0);
}

bool AbstractSudoku::isDivergent() const {
    if (allPossibles.back().possibles.size() == 0){
        return true;
    }
    return allPossibles.back().possibles.size() > 1;
}

bool AbstractSudoku::invalidPuzzle() const {
    return allPossibles.back().possibles.size() == 0;
}

std::string AbstractSudoku::emptyPositionsPossibilities() const {
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

bool operator<(AbstractSudoku const& sud1, AbstractSudoku const& sud2){
    if (sud1.allPossibles.size() == 0 || sud2.allPossibles.size() == 0) // no possibilities in lowest
        return sud1.allPossibles.size() < sud2.allPossibles.size(); 
    return sud1.allPossibles.back().possibles.size() < 
           sud2.allPossibles.back().possibles.size();
}

std::ostream& operator<< (std::ostream& o, const AbstractSudoku& sud){
    o << sud.toString();
    return o;
}


