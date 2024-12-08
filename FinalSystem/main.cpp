#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class TicTacToe {
    vector<vector<char>> board;
    char playerSymbol, computerSymbol;
    int playerScore, computerScore;

public:
    TicTacToe() : board(3, vector<char>(3, ' ')), playerScore(0), computerScore(0) {}

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
    void resetBoard() {
        for (auto& row : board) row.assign(3, ' ');
    }

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

    void displayScores() const {
        cout << "Scores:\nPlayer: " << playerScore << " | Computer: " << computerScore << "\n\n";
    }

    bool chooseOpponent() {
        cout << "Choose opponent:\n1. Another Player\n2. Computer\nEnter choice (1/2): ";
        int choice;
        cin >> choice;
        return choice == 2;
    }

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
            currentPlayer = togglePlayer(currentPlayer);
        }
    }

    void playerMove(char currentPlayer) {
        int row, col;
        while (true) {
            cout << "Player " << currentPlayer << ", enter row and column (1-3): ";
            cin >> row >> col;
            row--; col--;
            if (isValidMove(row, col)) {
                board[row][col] = currentPlayer;
                break;
            }
            else {
                cout << "Invalid move, try again.\n";
            }
        }
    }

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

    char togglePlayer(char currentPlayer) {
        return currentPlayer == 'X' ? 'O' : 'X';
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
    }

    bool checkWin(char player) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
        return false;
    }

    bool isDraw() {
        for (const auto& row : board)
            for (char cell : row)
                if (cell == ' ') return false;
        return true;
    }

    void updateScores(char winner) {
        if (winner == playerSymbol) playerScore++;
        if (winner == computerSymbol) computerScore++;
    }

    bool askToRestart() {
        cout << "Do you want to play again? (y/n): ";
        char choice;
        cin >> choice;
        return choice == 'y';
    }

    void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
