//
// Created by Yonil on 12/16/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <string>


class Board {
private:
    std::string**  gameBoard ;
    int N;
    int M;
    int countMoves;
    Board();
public:
    Board(int size, int mToWin);
    bool takeSpot(int row, int col, std::string symbol);
    bool checkWinCondition(int row, int col, std::string symbol) const;
    bool isEmpty(int row, int col) const;
    bool checkValidArguments(int row, int col) const;
    void printBoard() const;
    ~Board();
    int getCountMoves() const;
    int getN() const;
};

#endif //BOARD_H
