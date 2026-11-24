/*
 * Homework 4: Hex Board Implementation
 * Author: Muhammad Arham
 * Description: Implements an 11x11 Hex board with move validation 
 * and win detection using Breadth-First Search (BFS).
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>

enum class Piece { EMPTY, BLUE, RED };

/*
 * Represents the Hex Game Board and its logic.
 * Uses a coordinate system where (row, col) represents a hexagonal cell.
 * The board is visually slanted to represent the hexagonal grid.
 */

// Class Hexboard
class HexBoard {
private:
    int size;
    std::vector<std::vector<Piece>> board;
public:
    // Initialize an 11x11 board full of empty pieces
    HexBoard(int n = 11) : size(n), board(n, std::vector<Piece>(n, Piece :: EMPTY)) {}
    void display () {

        // Initital padding for the row letters 
        std::cout << "   ";
        for (int j = 1; j <= size; j++) {
            std::cout << j << (j < 10 ? "  " : "   ");
        }

        std::cout << "\n";

        for (int i = 0; i < size; i++) {
            std::string padding(i, ' ');
            char rowLabel = 'A' + i;
            std::cout << rowLabel << " " << padding;

            for (int j = 0; j < size; j++) {

                // Prints the symbol for the pieces 
                char symbol = '.';
                if (board[i][j] == Piece::BLUE) symbol = 'B';
                if (board[i][j] == Piece::RED) symbol = 'R';

                std::cout << symbol;

                // Adding a little dash between columns for readability 
                if (j < size-1) std::cout << " - ";
            }
            // Next Row / Line
            std::cout << std::endl;
            
            if (i < size-1) {
                // Printing the slashes row
                std::cout << padding << " ";
                for (int j = 0; j < size-1; j++) {
                    std::cout << "\\ / ";
                }
                std::cout << "\\" << std::endl;
            }
        }

    }

    // Function to check if the spot is legal or not
    bool is_legal (int r, int c) {
        // Check if spot is within bound
        bool in_bounds = (r >= 0 && r < size) && (c >= 0 && c < size);

        // Check if the spot is empty
        if (in_bounds && board[r][c] == Piece::EMPTY) {
            return true;
        }
        return false;
    }

    // Function to make a move 
    void make_move (int r, int c, Piece p) {
        if (is_legal(r, c)) {
            board[r][c] = p;
        } else {
            std::cout << "Move not legal! Try again." << std::endl;
        }
    }

    // Helper function to get all neighbours 
    std::vector<std::pair<int, int>> get_neighbours (int r, int c) {
        std::vector<std::pair<int, int>> neighbours;

        // Look all the 6 neighbours 
        int dr[] = {-1, -1, 0, 0, 1, 1};
        int dc[] = {0, 1, -1, 1, -1, 0};

        for (int i = 0; i < 6; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Check if new row & column is Inside Board
            if (nr >= 0 && nr < size && nc >= 0 && nc < size) {
                    neighbours.push_back({nr, nc});
                }
        }
        return neighbours;
    }

    // Function to check if Win 
    bool check_win (Piece p) {
        int n = size;
        std::vector<std::vector<bool>> visited (n, std::vector<bool>(n, false));
        std::queue<std::pair<int, int>> q;

        // Start the Search from starting Slide
        for (int i = 0; i < n; i++) {
            if (p == Piece::BLUE && board[i][0] == Piece::BLUE) {
                q.push({i, 0});
                visited[i][0] = true;
            } else if (p == Piece::RED && board[0][i] == Piece::RED) {
                q.push({0, i});
                visited[0][i] = true;
            }
        }

        // Search Party speards through the Stones
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            // Check for winning 
            if (p == Piece::BLUE && c == n - 1) return true;
            if (p == Piece::RED && r == n - 1) return true;

            for (auto neighbour : get_neighbours(r, c)) {
                int nr = neighbour.first;
                int nc = neighbour.second;

                if (board[nr][nc] == p && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        return false;  
    }

};

// Main Function 
int main() {
    int boardSize;
    std::cout << "Enter board size (e.g., 7): " << std::endl;
    std::cin >> boardSize;

    HexBoard myGame(boardSize);
    Piece currentPlayer = Piece::BLUE;
    bool gameWon = false;

    while (!gameWon) {
        myGame.display();
        std::string pname = (currentPlayer == Piece::BLUE) ? "BLUE" : "RED";
        char rowChar;
        int colNum;

        std::cout << pname << " player's turn. Enter row (A-K) & col (1-11): ";
        // check for inputs
        if (!(std::cin >> rowChar >> colNum)) break;

        // Convert A->0 & B->1 ...
        int r = toupper(rowChar) - 'A';
        // Convert 1->0 & 2->1...
        int c = colNum - 1;

        if (myGame.is_legal(r, c)) {
            myGame.make_move (r, c, currentPlayer);

            if (myGame.check_win(currentPlayer)) {
                myGame.display();
                std::cout << "Congratulations! " << pname << " wins !" << std::endl;
                gameWon = true;
            } else {
                // Switch Players
                currentPlayer = (currentPlayer == Piece::BLUE) ? Piece::RED : Piece::BLUE;
            }
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }
    return 0;
}
