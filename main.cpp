#include <iostream>
#include <stdexcept>
#include "board.h"

int main() {
    bool winner = false;  // Variable to track if there is a winner
    Board* ticTacToe = nullptr;  // Pointer to the Tic Tac Toe board

    // Loop until a valid Board object is created
    while (ticTacToe == nullptr) {
        try {
            int N, M;  // N is the size of the board, M is the number of moves required to win

            // Prompt the user to enter the dimensions of the board and the winning streak length
            while (true) {
                std::cout << "Enter size and winning streak for the tic_tac_toe board (N M): ";
                std::cin >> N >> M;

                // Attempt to create a new board with the specified dimensions
                ticTacToe = new Board(N, M);
                break;  // Exit the loop once the board is successfully created
            }
        } catch (const std::exception& e) {
            // print the error message and allow the user to try again
            std::cout << e.what() << std::endl;
        }
    }

    // Print the initial state of the board
    ticTacToe->printBoard();

    // Main game loop
    while (!winner) {
        try {
            int row, col;  // Variables to store the row and column for the move
            std::string symbol ;  // Variable to store whether the player chooses 'X' or 'O'

            // Loop to get a valid move (empty spot)
            while (true) {
                std::cout << "Enter row and col of tic_tac_toe (0-based index): " << std::endl;
                std::cin >> row >> col;

                // Check if the chosen spot is empty
                bool empty = ticTacToe->isEmpty(row, col);
                break;  // If the spot is empty, exit the loo
            }

            // Prompt the user to enter 'X' or 'O'
            std::cout << "Enter X or O: " << std::endl;
            std::cin >> symbol ;

            // Check if the input is either 'X' or 'O'
            if (symbol  != "X" && symbol  != "O") {
                std::cout << "Invalid input. Please enter X or O." << std::endl;
                continue;  // If the input is invalid, prompt the user again
            }

            // Attempt to make the move and check if there is a winner
            winner = ticTacToe->takeSpot(row, col, symbol );

            // Check if the game has ended in a draw (all spots are filled)
            if (ticTacToe->getCountMoves() == ticTacToe->getN() * ticTacToe->getN()) {
                std::cout << "Game over - it's a draw!" << std::endl;
                break;  // Exit the game loop in case of a draw
            }
        } catch (const std::exception& e) {
            // Catch any exceptions (e.g., invalid move or invalid row/col) and print the error message
            std::cout << e.what() << std::endl;
        }
    }

    // Clean up and delete the dynamically allocated Board object
    delete ticTacToe;
    return 0;
}