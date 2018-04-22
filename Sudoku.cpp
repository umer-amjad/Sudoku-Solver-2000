//
//  Sudoku.cpp
//

#include "Sudoku.hpp"

//helpers:

const std::vector<int> allPoss = []{
    std::vector<int> v(MAGNITUDE_SQR);
    for (int i = 0; i < MAGNITUDE_SQR; i++)
        v[i] = i+1;
    return v;
}();

bool PossVectCompare::operator()(const PossVect &a, const PossVect &b){
    if (a.second.size() == b.second.size())
        return a.first > b.first;
    return a.second.size() > b.second.size();
}

//constructors:

Sudoku::Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entryList): entry(entryList){
    int i = 0;
    int min_index = 0;
    int min_possibles_size = MAGNITUDE_SQR;
    allPossVect.reserve(81); //debug, so that iterators are not invalidated by vector reallocation
    auto min_iterator = allPossVect.begin();
    for (auto e : entry){
        if (e == 0){
            //std::cout << "Here at pos " << i << '\n';
            allPossVect.emplace_back(std::make_pair(i, findPossibles(i)));
            if (allPossVect.back().second.size() < min_possibles_size){
                //std::cout << "At " << i << " iteration,  allPossVect size is " << allPossVect.size() << std::endl;
                min_iterator = std::prev(allPossVect.end());
                min_index = min_iterator - allPossVect.begin();
                min_possibles_size = (int)allPossVect.back().second.size();
            }
        }
        i++;
    }
    //TODO: Debug allPossVect.begin() replaced with min_iterator() produces memory errors
    // iterators invalidated because of many insertions into vector above
    //std::cout << "At: "  << min_iterator - allPossVect.begin() << std::endl;
    std::sort(min_iterator, allPossVect.end(), PossVectCompare());
    //    std::cout << *this;
    //    std::cout << EmptyPositionsPossibilities();
}

Sudoku::Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntryList, std::vector<PossVect> newPossVect): entry(newEntryList), allPossVect(newPossVect) {
    int min_possibles_size = MAGNITUDE_SQR;
    auto min_iterator = allPossVect.begin();
    for (auto indPoss = allPossVect.begin(); indPoss != allPossVect.end(); indPoss++){
        int index = indPoss->first;
        std::vector<int>& possibles = indPoss->second;
        auto rwFilled = rowFilled(rowNum(index));
        auto clFilled = colFilled(colNum(index));
        auto bxFilled = boxFilled(boxNum(index));
        possibles.erase(std::remove_if(possibles.begin(), possibles.end(),
                                       [&rwFilled, &clFilled, &bxFilled](int possible){
                                           if (rwFilled[possible] || clFilled[possible] || bxFilled[possible])
                                               return true;
                                           
                                           return false; //Not found in any of them, not removed
                                       }), possibles.end());
        if (possibles.size() < min_possibles_size){
            min_iterator = indPoss;
            min_possibles_size = (int)possibles.size();
        }
    }
    std::sort(min_iterator, allPossVect.end(), PossVectCompare());
}

//private member functions:

int Sudoku::rowNum(int pos){
    return pos / MAGNITUDE_SQR;
}

int Sudoku::colNum(int pos){
    return pos % MAGNITUDE_SQR;
}

int Sudoku::boxNum(int pos){
    return MAGNITUDE*(pos / (MAGNITUDE_SQR*MAGNITUDE)) + (pos % MAGNITUDE_SQR)/MAGNITUDE;
}

std::array<int, MAGNITUDE_SQR> Sudoku::row(int n) const {
    std::array<int, MAGNITUDE_SQR> result;
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        result[i] = entry[i+n*MAGNITUDE_SQR];
    }
    return result;
}

std::array<int, MAGNITUDE_SQR> Sudoku::col(int n) const {
    std::array<int, MAGNITUDE_SQR> result;
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        result[i] = entry[n+i*MAGNITUDE_SQR];
    }
    return result;
}

std::array<int, MAGNITUDE_SQR> Sudoku::box(int n) const {
    std::array<int, MAGNITUDE_SQR> result;
    int colStart = MAGNITUDE*(n % MAGNITUDE);
    int rowStart = MAGNITUDE*(n / MAGNITUDE);
    int boxStart = MAGNITUDE_SQR*rowStart + colStart;
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        result[i] = entry[boxStart + (i % MAGNITUDE) + (i / MAGNITUDE) * MAGNITUDE_SQR];
    }
    return result;
}

std::array<bool, MAGNITUDE_SQR+1> Sudoku::rowFilled(int n) const {
    std::array<bool, MAGNITUDE_SQR+1> result{false};
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        int val = entry[i+n*MAGNITUDE_SQR];
        if (val != 0){
            result[val] = true;
        }
    }
    return result;
}

std::array<bool, MAGNITUDE_SQR+1> Sudoku::colFilled(int n) const {
    std::array<bool, MAGNITUDE_SQR+1> result{false};
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        int val = entry[n+i*MAGNITUDE_SQR];
        if (val != 0){
            result[val] = true;
        }
    }
    return result;
}

std::array<bool, MAGNITUDE_SQR+1> Sudoku::boxFilled(int n) const {
    std::array<bool, MAGNITUDE_SQR+1> result{false};
    int colStart = MAGNITUDE*(n % MAGNITUDE);
    int rowStart = MAGNITUDE*(n / MAGNITUDE);
    int boxStart = MAGNITUDE_SQR*rowStart + colStart;
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        int val = entry[boxStart + (i % MAGNITUDE) + (i / MAGNITUDE) * MAGNITUDE_SQR];
        if (val != 0){
            result[val] = true;
        }
    }
    return result;
}

std::vector<int> Sudoku::findPossibles(int pos) const {
    std::vector<int> possibles = allPoss;
    auto rwFilled = rowFilled(rowNum(pos));
    auto clFilled = colFilled(colNum(pos));
    auto bxFilled = boxFilled(boxNum(pos));
    possibles.erase(std::remove_if(possibles.begin(), possibles.end(),
                                   [&rwFilled, &clFilled, &bxFilled](int possible){
                                       if (rwFilled[possible] || clFilled[possible] || bxFilled[possible])
                                           return true;
                                       
                                       return false; //Not found in any of them, not removed
                                   }), possibles.end());
    return possibles;
}

// public member functions:

bool Sudoku::isComplete() const {
    return (allPossVect.size() == 0);
}

bool Sudoku::isDivergent() const {
    if (allPossVect.back().second.size() == 0){
        return true;
    }
    return allPossVect.back().second.size() > 1;
}

bool Sudoku::invalidPuzzle() const {
    return allPossVect.back().second.size() == 0;
}

std::deque<Sudoku> Sudoku::neighbours() {
    auto smallestPossList = allPossVect.back(); // take out first element
    allPossVect.pop_back();
    int numNbrs = (int) smallestPossList.second.size();
    std::deque<Sudoku> nbrs;
    for (int i = 0; i < numNbrs; i++){
        std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntry = entry;
        newEntry[smallestPossList.first] = smallestPossList.second[i];
        nbrs.push_back(Sudoku(newEntry, allPossVect));
    }
    std::sort(nbrs.begin(), nbrs.end());
    return nbrs;
}

Sudoku Sudoku::fillPossibles(){
    //keep track of which numbers have been used ("visited"), in case the puzzle has reached a point
    //where the only possibles in the same row/box/col are overlapping (contradictorily).
    bool visited[MAGNITUDE_SQR + 1] = {false}; //starts at 0, but uses values from 1
    auto possVec = allPossVect.rbegin();
    for (; possVec != allPossVect.rend(); ++possVec){
        if (possVec->second.size() != 1)
            break;
        int val = possVec->second[0];
        if (visited[val])
            break;
        entry[possVec->first] = val; //size = 1
        visited[val] = true;
    }
    allPossVect.erase(possVec.base(), allPossVect.end());
    //std::cout << "After filling pos:\n" << EmptyPositionsPossibilities();
    return Sudoku(entry, allPossVect);
}

std::string Sudoku::EmptyPositionsPossibilities() const {
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

// friend operators:

bool operator<(Sudoku const& sud1, Sudoku const& sud2){
    if (sud1.allPossVect.size() == 0 || sud2.allPossVect.size() == 0) // no possibilities in lowest
        return sud1.allPossVect.size() < sud2.allPossVect.size();
    int size1 = (int) sud1.allPossVect.back().second.size();
    int size2 = (int) sud2.allPossVect.back().second.size();
    //        if (size1 == size2)
    //            return sud1.allPossVect.size() > sud2.allPossVect.size();
    return size1 < size2;
}

std::ostream& operator<< (std::ostream& o, const Sudoku& sud){
    int numDigits = log10(MAGNITUDE_SQR) + 1;
    std::string emptyPos;
    for(int i = 0; i < numDigits; i++)
        emptyPos += ".";
    int lenLine = numDigits*MAGNITUDE_SQR + MAGNITUDE + 1 + MAGNITUDE*(MAGNITUDE + 1);
    for (int r = 0; r < MAGNITUDE_SQR; r++){
        if (r % MAGNITUDE == 0){
            for (int i = 0; i < lenLine; i++){
                if (i % (numDigits * MAGNITUDE + MAGNITUDE + 2) == 0)
                    o << " ";
                else
                    o << "-";
            }
            o << "\n";
        }
        for (int c = 0; c < MAGNITUDE_SQR; c++){
            if (c % MAGNITUDE == 0){
                o << "| ";
            }
            if (sud[r*MAGNITUDE_SQR + c] == 0)
                o << emptyPos << " ";
            else
                o <<std::setw(numDigits) << std::setfill('0') << sud[r*MAGNITUDE_SQR + c] << " ";
        }
        o <<"|\n";
    }
    for (int i = 0; i < lenLine; i++){
        if (i % (numDigits * MAGNITUDE + MAGNITUDE + 2) == 0)
            o << " ";
        else
            o << "-";
    }
    o << "\n";
    return o;
}
