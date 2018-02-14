//
//  Sudoku.cpp
//

#include "Sudoku.hpp"

const std::vector<int> allPoss = []{
    std::vector<int> v(MAGNITUDE_SQR);
    for (int i = 0; i < MAGNITUDE_SQR; i++)
        v[i] = i+1;
    return v;
}();

int Sudoku::rowNum(int pos){
    return pos / MAGNITUDE_SQR;
}

int Sudoku::colNum(int pos){
    return pos % MAGNITUDE_SQR;
}

int Sudoku::boxNum(int pos){
    return MAGNITUDE*(pos / (MAGNITUDE_SQR*MAGNITUDE)) + (pos % MAGNITUDE_SQR)/MAGNITUDE;
    // 2 /, 1 %, 2*, 1 +
}

bool operator<(Sudoku const& sud1, Sudoku const& sud2){
    if (sud1.allPossVect.size() == 0 || sud2.allPossVect.size() == 0) // no possibilities in lowest
        return sud1.allPossVect.size() < sud2.allPossVect.size();
    int size1 = (int) sud1.allPossVect.begin()->second.size();
    int size2 = (int) sud2.allPossVect.begin()->second.size();
    //        if (size1 == size2)
    //            return sud1.totalNumPoss < sud2.totalNumPoss;
    return size1 < size2;
}
//try also (pos / MAGNITUDE) % MAGNITUDE + pos / MAGNITUDE_SQR - ( (pos / MAGNITUDE_SQR) % MAGNITUDE)
// 3 /, 2 %, 1+, 1 -

std::vector<int> Sudoku::findPossibles(int pos){
    auto rw = this->row(rowNum(pos));
    auto cl = this->col(colNum(pos));
    auto bx = this->box(boxNum(pos));
    std::vector<int> possibles = allPoss;
    possibles.erase(std::remove_if(possibles.begin(), possibles.end(),
                   [rw, cl, bx](int possible){
                       if (std::find(rw.begin(), rw.end(), possible) != rw.end())
                           return true;
                       if (std::find(cl.begin(), cl.end(), possible) != cl.end())
                           return true;
                       if (std::find(bx.begin(), bx.end(), possible) != bx.end())
                           return true;
                       
                       return false; //Not found in any of them, not removed
                   }), possibles.end());
    return possibles;
}

Sudoku::Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entryList): entry(entryList){
    int i = 0;
    for (auto e : entry){
        if (e == 0){
            std::vector<int> poss = findPossibles(i);
            //std::cout << "Here at pos " << i << '\n';
            allPossVect.emplace_back(std::make_pair(i, poss));
//            allPossVect2.insert(std::make_pair(i, poss));
            //totalNumPoss += poss.size();
        }
        i++;
    }
    std::sort(allPossVect.begin(), allPossVect.end(), PossVectCompare());
//    std::cout << *this;
//    std::cout << showEmptyPos();
};

Sudoku::Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntryList, std::vector<PossVect> newPossVect): entry(newEntryList), allPossVect(newPossVect) {    
    for (auto& indPoss : allPossVect){
        int index = indPoss.first;
        std::vector<int>& possibles = indPoss.second;
        auto rw = this->row(rowNum(index));
        auto cl = this->col(colNum(index));
        auto bx = this->box(boxNum(index));
        possibles.erase(std::remove_if(possibles.begin(), possibles.end(),
                                       [rw, cl, bx](int possible){
                                           if (std::find(rw.begin(), rw.end(), possible) != rw.end())
                                               return true;
                                           if (std::find(cl.begin(), cl.end(), possible) != cl.end())
                                               return true;
                                           if (std::find(bx.begin(), bx.end(), possible) != bx.end())
                                               return true;
                                           
                                           return false; //Not found in any of them, not removed
                                       }), possibles.end());
    }
    std::sort(allPossVect.begin(), allPossVect.end(), PossVectCompare());
//    std::cout << *this;
//    std::cout <<"Parse correctly? \n" << showEmptyPos();
};

std::array<int, MAGNITUDE_SQR> Sudoku::row(int n){
    std::array<int, MAGNITUDE_SQR> result{0};
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        result[i] = entry[i+n*MAGNITUDE_SQR];
    }
    return result;
}

std::array<int, MAGNITUDE_SQR> Sudoku::col(int n){
    std::array<int, MAGNITUDE_SQR> result{0};
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        result[i] = entry[n+i*MAGNITUDE_SQR];
    }
    return result;
}

std::array<int, MAGNITUDE_SQR> Sudoku::box(int n){
    std::array<int, MAGNITUDE_SQR> result{0};
    int colStart = MAGNITUDE*(n % MAGNITUDE);
    int rowStart = MAGNITUDE*(n / MAGNITUDE);
    int boxStart = MAGNITUDE_SQR*rowStart + colStart;
    for (int i = 0; i < MAGNITUDE_SQR; i++){
        result[i] = entry[boxStart + (i % MAGNITUDE) + (i / MAGNITUDE) * MAGNITUDE_SQR];
    }
    return result;
}

PossVect Sudoku::popFirstPosVect(){
//    auto smallestListIter = allPossVect2.begin();
//    auto smallestPossList = std::move(*smallestListIter);
//    allPossVect2.erase(allPossVect2.begin());
    auto smallestPossList = std::move(allPossVect[0]);
    allPossVect.erase(allPossVect.begin());//erase first (begin) element
    return smallestPossList;
}

std::vector<Sudoku> Sudoku::neighbours(){
    auto smallestPossList = popFirstPosVect(); // take out first element
    //std::cout<<showEmptyPos(); debug
    int numNbrs = (int) smallestPossList.second.size();
    std::vector<Sudoku> nbrs;
    for (int i = 0; i < numNbrs; i++){
        std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntry = entry;
        newEntry[smallestPossList.first] = smallestPossList.second[i];
        nbrs.push_back(Sudoku(newEntry, allPossVect));
    }
    std::sort(nbrs.begin(), nbrs.end());
    return nbrs;
}


std::string Sudoku::showEmptyPos(){
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

Sudoku Sudoku::fillPossibles(){
    //keep track of which numbers have been used ("visited"), in case the puzzle has reached a point
    //where the only possibles in the same row/box/col are overlapping (contradictorily). 
    bool visited[MAGNITUDE_SQR + 1] = {false}; //starts at 0, but uses values from 1
    auto possVec = allPossVect.begin();
    for (; possVec != allPossVect.end(); possVec++){
        if (possVec->second.size() == 0 || possVec->second.size() > 1)
            break;
        int val = possVec->second[0];
        if (visited[val])
            break;
        entry[possVec->first] = val; //size = 1
        visited[val] = true;
    }
    allPossVect.erase(allPossVect.begin(), possVec);
    //std::cout << "After filling pos:\n" << showEmptyPos();
    return Sudoku(this->entry);
}

bool Sudoku::isComplete(){
    return (allPossVect.size() == 0);
}

bool Sudoku::isDivergent(){
    if (allPossVect.size() > 0){
        if (allPossVect[0].second.size() == 0){
            return true;
        }
        return allPossVect[0].second.size() > 1;
    }
    return false;
}


