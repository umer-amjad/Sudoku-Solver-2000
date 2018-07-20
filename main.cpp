#include <sys/time.h>
#include "SudokuSolver.hpp"

int main() {
    Sudoku<3> hardTest({
        9, 0, 6, 0, 7, 0, 4, 0, 3,
        0, 0, 0, 4, 0, 0, 2, 0, 0,
        0, 7, 0, 0, 2, 3, 0, 1, 0,
        5, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 4, 0, 2, 0, 8, 0, 6, 0,
        0, 0, 3, 0, 0, 0, 0, 0, 5,
        0, 3, 0, 7, 0, 0, 0, 5, 0,
        0, 0, 7, 0, 0, 5, 0, 0, 0,
        4, 0, 5, 0, 1, 0, 7, 0, 8
    });
    std::cout << hardTest;
    struct timeval tp;
    gettimeofday(&tp, 0);
    std::pair < Sudoku<3>, bool> result = solve(hardTest);
    if (result.second) {
        std::cout << result.first;
    } else {
        std::cout << "Puzzle has no solutions \n";
    }
    long int start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    for (int i = 0; i < 1000; i++) {
        Sudoku<3> testS({
            9, 0, 6, 0, 7, 0, 4, 0, 3,
            0, 0, 0, 4, 0, 0, 2, 0, 0,
            0, 7, 0, 0, 2, 3, 0, 1, 0,
            5, 0, 0, 0, 0, 0, 1, 0, 0,
            0, 4, 0, 2, 0, 8, 0, 6, 0,
            0, 0, 3, 0, 0, 0, 0, 0, 5,
            0, 3, 0, 7, 0, 0, 0, 5, 0,
            0, 0, 7, 0, 0, 5, 0, 0, 0,
            4, 0, 5, 0, 1, 0, 7, 0, 8
        });
        result = solve(testS);
    }
    gettimeofday(&tp, 0);
    long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    std::cout << "Time taken for 1000 puzzles: " << end - start << " milliseconds\n";

    start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    for (int i = 1; i < 1000; i++) {
        Sudoku<3> testS({
            9, 0, 6, 0, 7, 0, 4, 0, 3,
            0, 0, 0, 4, 0, 0, 2, 0, 0,
            0, 7, 0, 0, 2, 3, 0, 1, 0,
            5, 0, 0, 0, 0, 0, 1, 0, 0,
            0, 4, 0, 2, 0, 8, 0, 6, 0,
            0, 0, 3, 0, 0, 0, 0, 0, 5,
            0, 3, 0, 7, 0, 0, 0, 5, 0,
            0, 0, 7, 0, 0, 5, 0, 0, 0,
            4, 0, 5, 0, 1, 0, 7, 0, 8
        });
    }
    gettimeofday(&tp, NULL);
    end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    std::cout << "Subtract time taken for 1000 declarations: " << end - start << " milliseconds\n";
    //    std::cout << "Original was: \n" << testS << '\n';
    if (result.second) {
        std::cout << result.first;
    } else {
        std::cout << "Puzzle has no solutions \n";
    }

    Sudoku<3> exhaustiveTest({
        9, 0, 6, 0, 7, 0, 4, 0, 3,
        0, 0, 0, 4, 0, 0, 2, 0, 0,
        0, 7, 0, 0, 2, 3, 0, 1, 0,
        5, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 4, 0, 2, 0, 8, 0, 6, 0,
        0, 0, 3, 0, 0, 0, 0, 0, 5,
        0, 3, 0, 7, 0, 0, 0, 5, 0,
        0, 0, 7, 0, 0, 5, 0, 0, 0,
        4, 0, 5, 0, 1, 0, 7, 0, 8
    });
    std::vector<Sudoku < 3 >> solutions;
    std::cout << "Exhaustive solving: \n";
    std::cout << exhaustiveTest;
    gettimeofday(&tp, 0);
    start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    exhaustiveSolve(exhaustiveTest, solutions);
    gettimeofday(&tp, 0);
    end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    std::cout << "Solutions: " << solutions.size() << ":" << std::endl;
    for (auto& sol : solutions) {
        std::cout << sol;
    }
    std::cout << "Time taken for exhaustive solutions: " << end - start << " milliseconds\n";
    exhaustiveTest = Sudoku<3>({
        0, 8, 0, 0, 0, 9, 7, 4, 3,
        0, 5, 0, 0, 0, 8, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0,
        8, 0, 0, 0, 0, 5, 0, 0, 0,
        0, 0, 0, 8, 0, 4, 0, 0, 0,
        0, 0, 0, 3, 0, 0, 0, 0, 6,
        0, 0, 0, 0, 0, 0, 0, 7, 0,
        0, 3, 0, 5, 0, 0, 0, 8, 0,
        9, 7, 2, 4, 0, 0, 0, 5, 0
    });
    solutions.clear();
    std::cout << "Exhaustive solving: \n";
    std::cout << exhaustiveTest;
    gettimeofday(&tp, 0);
    start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    exhaustiveSolve(exhaustiveTest, solutions);
    gettimeofday(&tp, 0);
    end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    std::cout << "Solutions: " << solutions.size() << ":" << std::endl;
    for (auto& sol : solutions) {
        std::cout << sol;
    }
    std::cout << "Time taken for exhaustive solutions: " << end - start << " milliseconds\n";
}

//Sudoku tests:
//std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> testSud{
//    5,3,0,0,7,0,0,0,0,
//    6,0,0,1,9,5,0,0,0,
//    0,9,8,0,0,0,0,6,0,
//    8,0,0,0,6,0,0,0,3,
//    4,0,0,8,0,3,0,0,1,
//    7,0,0,0,2,0,0,0,6,
//    0,6,0,0,0,0,2,8,0,
//    0,0,0,4,1,9,0,0,5,
//    0,0,0,0,8,0,0,7,9
//};
//------- ------- -------
//| 5 3 4 | 6 7 8 | 9 1 2 |
//| 6 7 2 | 1 9 5 | 3 4 8 |
//| 1 9 8 | 3 4 2 | 5 6 7 |
//------- ------- -------
//| 8 5 9 | 7 6 1 | 4 2 3 |
//| 4 2 6 | 8 5 3 | 7 9 1 |
//| 7 1 3 | 9 2 4 | 8 5 6 |
//------- ------- -------
//| 9 6 1 | 5 3 7 | 2 8 4 |
//| 2 8 7 | 4 1 9 | 6 3 5 |
//| 3 4 5 | 2 8 6 | 1 7 9 |
//------- ------- -------

//std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> testSud{
//    0,0,0,0,0,0,0,1,0,
//    0,0,0,0,0,2,0,0,3,
//    0,0,0,4,0,0,0,0,0,
//    0,0,0,0,0,0,5,0,0,
//    4,0,1,6,0,0,0,0,0,
//    0,0,7,1,0,0,0,0,0,
//    0,5,0,0,0,0,2,0,0,
//    0,0,0,0,8,0,0,4,0,
//    0,3,0,9,1,0,0,0,0
//};
//------- ------- -------
//| 7 4 5 | 3 6 8 | 9 1 2 |
//| 8 1 9 | 5 7 2 | 4 6 3 |
//| 3 6 2 | 4 9 1 | 8 5 7 |
//------- ------- -------
//| 6 9 3 | 8 2 4 | 5 7 1 |
//| 4 2 1 | 6 5 7 | 3 9 8 |
//| 5 8 7 | 1 3 9 | 6 2 4 |
//------- ------- -------
//| 1 5 8 | 7 4 6 | 2 3 9 |
//| 9 7 6 | 2 8 3 | 1 4 5 |
//| 2 3 4 | 9 1 5 | 7 8 6 |
//------- ------- -------

//std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> testSud{
//    0, 1, 2, 3,
//    2, 0, 0, 1,
//    3, 0, 1, 0,
//    0, 0, 0, 0
//};

//std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> testSud{
//     1, 0, 0, 2, 3, 4, 0, 0,12, 0, 6, 0, 0, 0, 7, 0,
//     0, 0, 8, 0, 0, 0, 7, 0, 0, 3, 0, 0, 9,10, 6,11,
//     0,12, 0, 0,10, 0, 0, 1, 0,13, 0,11, 0, 0,14, 0,
//     3, 0, 0,15, 2, 0, 0,14, 0, 0, 0, 9, 0, 0,12, 0,
//    13, 0, 0, 0, 8, 0, 0,10, 0,12, 2, 0, 1,15, 0, 0,
//     0,11, 7, 6, 0, 0, 0,16, 0, 0, 0,15, 0, 0, 5,13,
//     0, 0, 0,10, 0, 5,15, 0, 0, 4, 0, 8, 0, 0,11, 0,
//    16, 0, 0, 5, 9,12, 0, 0, 1, 0, 0, 0, 0, 0, 8, 0,
//     0, 2, 0, 0, 0, 0, 0,13, 0, 0,12, 5, 8, 0, 0, 3,
//     0,13, 0, 0,15, 0, 3, 0, 0,14, 8, 0,16, 0, 0, 0,
//     5, 8, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0,13, 9,15, 0,
//     0, 0,12, 4, 0, 6,16, 0,13, 0, 0, 7, 0, 0, 0, 5,
//     0, 3, 0, 0,12, 0, 0, 0, 6, 0, 0, 4,11, 0, 0,16,
//     0, 7, 0, 0,16, 0, 5, 0,14, 0, 0, 1, 0, 0, 2, 0,
//    11, 1,15, 9, 0, 0,13, 0, 0, 2, 0, 0, 0,14, 0, 0,
//     0,14, 0, 0, 0,11, 0, 2, 0, 0,13, 3, 5, 0, 0,12
//};


//exhaustive solve tests;

//this puzzle has 2 solutions:
//std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> exhaustiveTest{
//    9,0,6,0,7,0,4,0,3,
//    0,0,0,4,0,0,2,0,0,
//    0,7,0,0,2,3,0,1,0,
//    5,0,0,0,0,0,1,0,0,
//    0,4,0,2,0,8,0,6,0,
//    0,0,3,0,0,0,0,0,5,
//    0,3,0,7,0,0,0,5,0,
//    0,0,7,0,0,5,0,0,0,
//    4,0,5,0,1,0,7,0,8
//};
//solutions:
//------- ------- -------
//| 9 2 6 | 5 7 1 | 4 8 3 |
//| 3 5 1 | 4 8 6 | 2 7 9 |
//| 8 7 4 | 9 2 3 | 5 1 6 |
//------- ------- -------
//| 5 8 2 | 3 6 7 | 1 9 4 |
//| 1 4 9 | 2 5 8 | 3 6 7 |
//| 7 6 3 | 1 4 9 | 8 2 5 |
//------- ------- -------
//| 2 3 8 | 7 9 4 | 6 5 1 |
//| 6 1 7 | 8 3 5 | 9 4 2 |
//| 4 9 5 | 6 1 2 | 7 3 8 |
//------- ------- -------
//------- ------- -------
//| 9 2 6 | 5 7 1 | 4 8 3 |
//| 3 5 1 | 4 8 6 | 2 7 9 |
//| 8 7 4 | 9 2 3 | 5 1 6 |
//------- ------- -------
//| 5 8 2 | 3 6 7 | 1 9 4 |
//| 1 4 9 | 2 5 8 | 3 6 7 |
//| 7 6 3 | 1 9 4 | 8 2 5 |
//------- ------- -------
//| 2 3 8 | 7 4 9 | 6 5 1 |
//| 6 1 7 | 8 3 5 | 9 4 2 |
//| 4 9 5 | 6 1 2 | 7 3 8 |
//------- ------- -------


// 8 solutions:
//std::array<int, MAGNITUDE_SQR*MAGNITUDE_SQR> exhaustiveTest{
//    0,8,0,0,0,9,7,4,3,
//    0,5,0,0,0,8,0,1,0,
//    0,1,0,0,0,0,0,0,0,
//    8,0,0,0,0,5,0,0,0,
//    0,0,0,8,0,4,0,0,0,
//    0,0,0,3,0,0,0,0,6,
//    0,0,0,0,0,0,0,7,0,
//    0,3,0,5,0,0,0,8,0,
//    9,7,2,4,0,0,0,5,0
//};
//solutions:
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 4 5 7 | 6 3 8 | 9 1 2 |
//| 3 1 9 | 7 4 2 | 5 6 8 |
//------- ------- -------
//| 8 9 1 | 2 6 5 | 4 3 7 |
//| 6 2 3 | 8 7 4 | 1 9 5 |
//| 7 4 5 | 3 9 1 | 8 2 6 |
//------- ------- -------
//| 5 6 8 | 9 1 3 | 2 7 4 |
//| 1 3 4 | 5 2 7 | 6 8 9 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 3 5 7 | 6 4 8 | 9 1 2 |
//| 4 1 9 | 7 3 2 | 5 6 8 |
//------- ------- -------
//| 8 9 1 | 2 6 5 | 4 3 7 |
//| 6 2 3 | 8 7 4 | 1 9 5 |
//| 7 4 5 | 3 9 1 | 8 2 6 |
//------- ------- -------
//| 5 6 8 | 9 1 3 | 2 7 4 |
//| 1 3 4 | 5 2 7 | 6 8 9 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 3 5 4 | 7 6 8 | 9 1 2 |
//| 7 1 9 | 2 4 3 | 5 6 8 |
//------- ------- -------
//| 8 2 3 | 6 1 5 | 4 9 7 |
//| 6 9 7 | 8 2 4 | 1 3 5 |
//| 1 4 5 | 3 9 7 | 8 2 6 |
//------- ------- -------
//| 5 6 8 | 9 3 1 | 2 7 4 |
//| 4 3 1 | 5 7 2 | 6 8 9 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 3 5 4 | 7 6 8 | 9 1 2 |
//| 7 1 9 | 2 4 3 | 5 6 8 |
//------- ------- -------
//| 8 9 3 | 6 1 5 | 4 2 7 |
//| 6 2 7 | 8 9 4 | 1 3 5 |
//| 1 4 5 | 3 2 7 | 8 9 6 |
//------- ------- -------
//| 5 6 8 | 9 3 1 | 2 7 4 |
//| 4 3 1 | 5 7 2 | 6 8 9 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 3 5 4 | 7 6 8 | 9 1 2 |
//| 7 1 9 | 2 4 3 | 5 6 8 |
//------- ------- -------
//| 8 9 3 | 6 1 5 | 4 2 7 |
//| 6 2 7 | 8 9 4 | 1 3 5 |
//| 1 4 5 | 3 7 2 | 8 9 6 |
//------- ------- -------
//| 5 6 8 | 9 3 1 | 2 7 4 |
//| 4 3 1 | 5 2 7 | 6 8 9 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 4 5 7 | 6 3 8 | 2 1 9 |
//| 3 1 9 | 7 4 2 | 5 6 8 |
//------- ------- -------
//| 8 2 1 | 9 6 5 | 4 3 7 |
//| 6 9 3 | 8 7 4 | 1 2 5 |
//| 7 4 5 | 3 2 1 | 8 9 6 |
//------- ------- -------
//| 5 6 8 | 2 1 3 | 9 7 4 |
//| 1 3 4 | 5 9 7 | 6 8 2 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 3 5 7 | 6 4 8 | 2 1 9 |
//| 4 1 9 | 7 2 3 | 5 6 8 |
//------- ------- -------
//| 8 2 1 | 9 6 5 | 4 3 7 |
//| 6 9 3 | 8 7 4 | 1 2 5 |
//| 7 4 5 | 3 1 2 | 8 9 6 |
//------- ------- -------
//| 5 6 8 | 2 3 1 | 9 7 4 |
//| 1 3 4 | 5 9 7 | 6 8 2 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------
//------- ------- -------
//| 2 8 6 | 1 5 9 | 7 4 3 |
//| 3 5 7 | 6 4 8 | 2 1 9 |
//| 4 1 9 | 7 3 2 | 5 6 8 |
//------- ------- -------
//| 8 2 1 | 9 6 5 | 4 3 7 |
//| 6 9 3 | 8 7 4 | 1 2 5 |
//| 7 4 5 | 3 2 1 | 8 9 6 |
//------- ------- -------
//| 5 6 8 | 2 1 3 | 9 7 4 |
//| 1 3 4 | 5 9 7 | 6 8 2 |
//| 9 7 2 | 4 8 6 | 3 5 1 |
//------- ------- -------





