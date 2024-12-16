//
// Created by Yonil on 12/16/2024.
//
#include "board.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Constructor for the Board class
Board::Board(const int size, const int mToWin) {
    // Validate the size and mToWin arguments
    if(size < 1 || mToWin < 1 || mToWin > size) {
        throw std::invalid_argument("Invalid row/col or winning streak");
    }

    N = size;  // Set the size of the board
    M = mToWin;  // Set the number of consecutive marks required to win
    gameBoard  = new std::string*[N];  // Create the board as a dynamic 2D array of strings
    countMoves = 0;  // Initialize the count of moves made

    // Initialize the board with string values representing the indices
    for (int i = 0; i < N; ++i) {
        gameBoard [i] = new std::string[N];
    }
    int index = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            gameBoard [i][j] = std::to_string(index++);
        }
    }
}

// Method to take a spot on the board (place either X or O)
bool Board::takeSpot(const int row, const int col, const std::string symbol) {
    // Validate the row and column
    if(!checkValidArguments(row, col)) {
        throw std::invalid_argument("Invalid row or col");
    }

    // Check if the spot is empty
    if(!isEmpty(row, col)) {
        throw std::invalid_argument("Spot taken");
    }

    // Place the player's symbol on the board and increment the count of moves
    gameBoard [row][col] = symbol;
    countMoves++;

    // Check if this move results in a win
    if(checkWinCondition(row, col, symbol)) {
        std::cout << "Congrats!!! Player " << symbol << " won!!" << std::endl;
        printBoard();
        return true;  // Return true to indicate a win
    }

    // Print the board after the move
    printBoard();
    return false;  // Return false as no winner yet
}

// Method to check if the provided row and column are valid (within bounds)
bool Board::checkValidArguments(const int row, const int col) const {
    if(row < 0 || row >= N || col < 0 || col >= N) {
        return false;  // Return false if the row or column is out of bounds
    }
    return true;
}

// Method to check if a spot is empty on the board
bool Board::isEmpty(const int row, const int col) const {
    // Ensure the spot is within bounds
    if (row < 0 || row >= N || col < 0 || col >= N) {
        throw std::invalid_argument("Invalid spot, please try again.");
    }

    // Check if the spot is already taken by either "X" or "O"
    if (gameBoard [row][col] == "O" || gameBoard [row][col] == "X") {
        return false;  // Spot is not empty
    }
    return true;
}

// Method to check if the current move results in a win
bool Board::checkWinCondition(const int row, const int col, const std::string symbol) const {
    // Initialize counters for checking lines in all directions
    int countNInColumnDown = 0;
    int countNInColumnUp = 0;
    int countNInRowFront = 0;
    int countNInRowBack = 0;
    int countNInDiagonalUpRight = 0;
    int countNInDiagonalUpLeft = 0;
    int countNInDiagonalDownRight = 0;
    int countNInDiagonalDownLeft = 0;

    // Check all directions for a winning line
    for(int i = 0; i < M; ++i) {
        // Check horizontally (right and left)
        if(col + i < N && gameBoard [row][col + i] == symbol) {
            if(++countNInColumnDown == M) {
                return true;  // Win in this direction
            }
        }
        if(col - i >= 0 && gameBoard [row][col - i] == symbol) {
            if(++countNInColumnUp == M) {
                return true;  // Win in this direction
            }
        }

        // Check vertically (up and down)
        if(row + i < N && gameBoard [row + i][col] == symbol) {
            if(++countNInRowFront == M) {
                return true;  // Win in this direction
            }
        }
        if(row - i >= 0 && gameBoard [row - i][col] == symbol) {
            if(++countNInRowBack == M) {
                return true;  // Win in this direction
            }
        }

        // Check diagonally (four diagonal directions)
        if(col - i >= 0  && row + i < N && gameBoard [row + i][col - i] == symbol) {
            if(++countNInDiagonalUpRight == M) {
                return true;  // Win in this direction
            }
        }
        if(col + i < N  && row + i < N && gameBoard [row + i][col + i] == symbol) {
            if(++countNInDiagonalDownRight == M) {
                return true;  // Win in this direction
            }
        }
        if(col - i >= 0  && row - i >= 0 && gameBoard [row - i][col - i] == symbol) {
            if(++countNInDiagonalUpLeft == M) {
                return true;  // Win in this direction
            }
        }
        if(col + i < N  && row - i >= 0 && gameBoard [row - i][col + i] == symbol) {
            if(++countNInDiagonalDownLeft == M) {
                return true;  // Win in this direction
            }
        }
    }
    return false;  // No winning line found
}

// Method to print the board to the console
void Board::printBoard() const {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
           std::cout<< gameBoard [i][j]<< " ";  // Print each element of the board
        }
        std::cout << std::endl;
    }
}

// Destructor to clean up dynamically allocated memory
Board::~Board() {
    delete[] gameBoard ;
}

// Getter for the count of moves made so far
int Board::getCountMoves() const {
    return countMoves;
}

// Getter for the size of the board (N)
int Board::getN() const {
    return N;
}
