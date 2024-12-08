#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class TicTacToe {
    vector<vector<char>> board; // 3x3 game board
    char playerSymbol, computerSymbol; // Symbols for player and computer
    int playerScore, computerScore; // Score counters

public:
    TicTacToe() : board(3, vector<char>(3, ' ')), playerScore(0), computerScore(0) {}

    // Main function to control the game flow
    void playGame() {
        while (true) {
            clearConsole();
            displayScores();
            resetBoard();
            bool againstComputer = chooseOpponent();
            char winner = playRound(againstComputer);
            updateScores(winner);
            if (!askToRestart()) break;
        }
    }

private:
    // Resets the game board to an empty state
    void resetBoard() {
        for (auto& row : board) row.assign(3, ' ');
    }

    // Displays the current game board
    void displayBoard() {
        cout << "\n  1 2 3\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "  -----\n";
        }
    }

    // Displays the scores of the player and the computer
    void displayScores() {
        cout << "Scores:\nPlayer: " << playerScore << " | Computer: " << computerScore << "\n\n";
    }

    // Lets the player choose between playing with another player or the computer
    bool chooseOpponent() {
        cout << "Choose opponent:\n1. Another Player\n2. Computer\nEnter choice (1/2): ";
        int choice;
        cin >> choice;
        return choice == 2; // Returns true if computer is selected
    }

    // Handles a single round of the game
    char playRound(bool againstComputer) {
        char currentPlayer = 'X';
        playerSymbol = 'X';
        computerSymbol = againstComputer ? 'O' : 'X';

        while (true) {
            clearConsole();
            displayBoard();
            if (currentPlayer == computerSymbol && againstComputer) {
                computerMove();
            }
            else {
                playerMove(currentPlayer);
            }
            if (checkWin(currentPlayer)) {
                clearConsole();
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                return currentPlayer;
            }
            if (isDraw()) {
                clearConsole();
                displayBoard();
                cout << "It's a draw!\n";
                return 'D';
            }
            currentPlayer = togglePlayer(currentPlayer); // Switch to the other player
        }
    }

    // Processes a player's move
    void playerMove(char currentPlayer) {
        string rowS, colS;
        int row, col;
        while (true) {
            try
            {
                cout << "Player " << currentPlayer << ", enter row and column (1-3): ";
                cin >> rowS >> colS;
                row = stoi(rowS);
                col = stoi(colS);
                row--; col--; // Convert to 0-based indexing
                if (isValidMove(row, col)) {
                    board[row][col] = currentPlayer;
                    break;
                }
                else {
                    cout << "Invalid move, try again.\n";
                }
            }
            catch (const std::exception&)
            {
                cout << "Invalid move, try again.\n";
            }
        }
    }

    // Makes a move for the computer
    void computerMove() {
        srand(time(0));
        int row, col;
        while (true) {
            row = rand() % 3;
            col = rand() % 3;
            if (isValidMove(row, col)) {
                board[row][col] = computerSymbol;
                break;
            }
        }
        cout << "Computer made its move.\n";
    }

    // Toggles the current player
    char togglePlayer(char currentPlayer) {
        return currentPlayer == 'X' ? 'O' : 'X';
    }

    // Checks if a move is valid
    bool isValidMove(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
    }

    // Checks if the current player has won
    bool checkWin(char player) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
        return false;
    }

    // Checks if the game is a draw
    bool isDraw() {
        for (const auto& row : board)
            for (char cell : row)
                if (cell == ' ') return false;
        return true;
    }

    // Updates the scores based on the winner
    void updateScores(char winner) {
        if (winner == playerSymbol) playerScore++;
        if (winner == computerSymbol) computerScore++;
    }

    // Asks the player if they want to restart the game
    bool askToRestart() {
        cout << "Do you want to play again? (y/n): ";
        char choice;
        cin >> choice;
        return choice == 'y';
    }

    // Clears the console for a cleaner display
    void clearConsole() {
#ifdef _WIN32
        system("cls"); // Windows
#else
        system("clear"); // Unix-based systems
#endif
    }
};

int main() {
    TicTacToe game;
    game.playGame(); // Start the game
    return 0;
}
