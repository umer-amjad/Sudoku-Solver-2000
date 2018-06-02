//  SudokuN.hpp

#ifndef SUDOKUN_HPP
#define SUDOKUN_HPP

#include <sstream>
#include <memory>

#include "SudokuI.hpp"

struct PossVectCompare {
    inline bool operator()(const PossVect &a, const PossVect &b);
};

bool PossVectCompare::operator()(const PossVect &a, const PossVect &b){
    if (a.second.size() == b.second.size())
        return a.first > b.first;
    return a.second.size() > b.second.size();
}

template<int MAGNITUDE>
class Sudoku : public SudokuI {
    static constexpr int MAGNITUDE_SQR = MAGNITUDE * MAGNITUDE;

    const std::vector<int> allPoss = []{
        std::vector<int> v(MAGNITUDE_SQR);
        for (int i = 0; i < MAGNITUDE_SQR; i++)
            v[i] = i+1;
        return v;
    }();
    
    inline int& operator[](size_t index) {
        return entry[index];
    };
    inline int operator[](size_t index) const {
        return entry[index];
    };
    
    std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entry;
    
    //given a "pos", returns which row/col/box the pos lies on
    inline int rowNum(int pos) const {
        return pos / MAGNITUDE_SQR;
    }
    inline int colNum(int pos) const {
        return pos % MAGNITUDE_SQR;
    }
    inline int boxNum(int pos) const {
        return MAGNITUDE*(pos / (MAGNITUDE_SQR*MAGNITUDE)) + (pos % MAGNITUDE_SQR)/MAGNITUDE;
    }
    
    //returns nth the row/col/box
    std::array<int, MAGNITUDE_SQR> row(int n) const {
        std::array<int, MAGNITUDE_SQR> result;
        for (int i = 0; i < MAGNITUDE_SQR; i++){
            result[i] = entry[i+n*MAGNITUDE_SQR];
        }
        return result;
    }
    std::array<int, MAGNITUDE_SQR> col(int n) const {
        std::array<int, MAGNITUDE_SQR> result;
        for (int i = 0; i < MAGNITUDE_SQR; i++){
            result[i] = entry[n+i*MAGNITUDE_SQR];
        }
        return result;
    }
    std::array<int, MAGNITUDE_SQR> box(int n) const {
        std::array<int, MAGNITUDE_SQR> result;
        int colStart = MAGNITUDE*(n % MAGNITUDE);
        int rowStart = MAGNITUDE*(n / MAGNITUDE);
        int boxStart = MAGNITUDE_SQR*rowStart + colStart;
        for (int i = 0; i < MAGNITUDE_SQR; i++){
            result[i] = entry[boxStart + (i % MAGNITUDE) + (i / MAGNITUDE) * MAGNITUDE_SQR];
        }
        return result;
    }
    
    // returns an array of bools, with the index of an element in the array specifies whether
    // the number representing that index is in the nth row/col/box
    // e.g. if rowFilled(6)[3] is true, then the number 3 is filled in in the 6th row
    std::array<bool, MAGNITUDE_SQR+1> rowFilled(int n) const {
        std::array<bool, MAGNITUDE_SQR+1> result{false};
        for (int i = 0; i < MAGNITUDE_SQR; i++){
            int val = entry[i+n*MAGNITUDE_SQR];
            if (val != 0){
                result[val] = true;
            }
        }
        return result;
    }
    std::array<bool, MAGNITUDE_SQR+1> colFilled(int n) const {
        std::array<bool, MAGNITUDE_SQR+1> result{false};
        for (int i = 0; i < MAGNITUDE_SQR; i++){
            int val = entry[n+i*MAGNITUDE_SQR];
            if (val != 0){
                result[val] = true;
            }
        }
        return result;
    }
    std::array<bool, MAGNITUDE_SQR+1> boxFilled(int n) const {
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
    
    Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntryList, std::vector<PossVect> newPossVect): SudokuI(newPossVect), entry(newEntryList) {
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
    
    std::vector<int> findPossibles(int pos) const {
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
    
public:
    
    Sudoku(std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> entryList): entry(entryList){
        int i = 0;
        int min_index = 0;
        int min_possibles_size = MAGNITUDE_SQR;
        for (auto e : entry){
            if (e == 0){
                allPossVect.emplace_back(std::make_pair(i, findPossibles(i)));
                if (allPossVect.back().second.size() < min_possibles_size){
                    min_index = allPossVect.size() - 1;
                    min_possibles_size = (int)allPossVect.back().second.size();
                }
            }
            i++;
        }
        std::sort(allPossVect.begin() + min_index, allPossVect.end(), PossVectCompare());
    }
    
    virtual std::deque<std::shared_ptr<SudokuI>> neighbours() override {
        std::shared_ptr<SudokuI> sudPtr {nullptr};
        auto smallestPossList = allPossVect.back(); // take out first element
        allPossVect.pop_back();
        int numNbrs = (int) smallestPossList.second.size();
        std::deque<std::shared_ptr<SudokuI>> nbrs;
        for (int i = 0; i < numNbrs; i++){
            std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> newEntry = entry;
            newEntry[smallestPossList.first] = smallestPossList.second[i];
            sudPtr.reset(new Sudoku(newEntry, allPossVect));
            nbrs.push_back(sudPtr);
        }
        std::sort(nbrs.begin(), nbrs.end(), [](const std::shared_ptr<SudokuI> sudA, const std::shared_ptr<SudokuI> sudB) {
            return (*sudA) < (*sudB);
        });
        return nbrs;
    }
    
    std::shared_ptr<SudokuI> fillPossibles() override {
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
        std::shared_ptr<SudokuI> toReturn;
        toReturn.reset(new Sudoku(entry, allPossVect));
        return toReturn;
    }
    
    virtual std::string toString() const override {
        std::ostringstream o;
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
                if ((*this)[r*MAGNITUDE_SQR + c] == 0)
                    o << emptyPos << " ";
                else
                    o <<std::setw(numDigits) << std::setfill('0') << (*this)[r*MAGNITUDE_SQR + c] << " ";
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
        return o.str();
    }   
};

#endif /* SUDOKUN_HPP */

