#include <algorithm>       // For shuffle
#include <random>          // For std::mt19937
#include <iostream>
#include <vector>
#include <string>
#include <queue>

enum class Piece { EMPTY, BLUE, RED };

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
    bool check_win (Piece p, const std::vector<std::vector<Piece>>& testBoard) {
        int n = size;
        std::vector<std::vector<bool>> visited (n, std::vector<bool>(n, false));
        std::queue<std::pair<int, int>> q;

        // Start the Search from starting Slide
        for (int i = 0; i < n; i++) {
            if (p == Piece::BLUE && testBoard[i][0] == Piece::BLUE) {
                q.push({i, 0});
                visited[i][0] = true;
            } else if (p == Piece::RED && testBoard[0][i] == Piece::RED) {
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

                if (testBoard[nr][nc] == p && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        return false;  
    }

    bool check_win(Piece p) {
        return check_win(p, this->board);
    }

    // "Fill in the Blank" Machine / Function 
    bool run_simulation (int StartR, int StartC, Piece aiPlayer) {
        // Create a "Ghost Board" (a copy of current state of board)
        std::vector<std::vector<Piece>> ghostBoard = board;

        // Place AI's first "experimental" move
        ghostBoard[StartR][StartC] = aiPlayer;

        // Find all the remaining empty spots
        std::vector<std::pair<int, int>> emptySpots;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (ghostBoard[i][j] == Piece::EMPTY) {
                    emptySpots.push_back({i, j});
                }
            }
        }

        // Shuffle the empty spots vector to make playout random
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(emptySpots.begin(), emptySpots.end(), g);

        // Fill the board alternatingly
        Piece currentPlayer = (aiPlayer == Piece::BLUE) ? Piece::RED : Piece::BLUE;
        for (auto& spot : emptySpots) {
            ghostBoard[spot.first][spot.second] = currentPlayer;
            currentPlayer = (currentPlayer == Piece::BLUE) ? Piece::RED : Piece::BLUE;
        }

        // Check who won this random mess
        return check_win (aiPlayer, ghostBoard);

    }

    std::pair<int, int> get_best_move(Piece aiPlayer, int trials = 1000) {
        std::pair<int, int> bestMove = {-1, -1};
        double maxWinRate = -1.0;

        // Find all the empty spaces to evalute
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == Piece::EMPTY) {

                    // For this specific spot run many Ghost Games
                    int wins = 0;
                    for (int t = 0; t < trials; t++) {
                        if (run_simulation(i, j, aiPlayer)) {
                            wins++;
                        }
                    }
                    // Calculate win rate and track the best one
                    double WinRate = static_cast<double>(wins) / trials;

                    // See AI's thinking in the terminal
                    std::cout << "Testing " << (char)('A'+i) << j+1 << " " << WinRate * 100 << "%" << std::endl;

                    if (WinRate > maxWinRate) {
                        maxWinRate = WinRate;
                        bestMove = {i, j};
                    }
                }
            }
        }
        return bestMove;
    }

};

// Main Function 
int main() {
    int boardSize;
    std::cout << "Enter board size (e.g., 7): " << std::endl;
    std::cin >> boardSize;

    HexBoard myGame(boardSize);

    char choice;
    std::cout << "Choose you color: Blue (B) goes first, Red (R) goes second: ";
    std::cin >> choice;

    Piece human = (toupper(choice) == 'B') ? Piece::BLUE : Piece::RED;
    Piece ai = (human == Piece::BLUE) ? Piece::RED : Piece::BLUE;

    // Blue always starts
    Piece currentPlayer = Piece::BLUE;
    bool gameWon = false;

    while (!gameWon) {
        myGame.display();

        // --- Human Turn --- 
        if (currentPlayer == human) {
            char rowChar;
            int colNum;

            std::cout << " Your turn (e.g., A 1): ";
            // check for inputs
            if (!(std::cin >> rowChar >> colNum)) break;

            // Convert A->0 & B->1 ...
            int r = toupper(rowChar) - 'A';
            // Convert 1->0 & 2->1...
            int c = colNum - 1;

            if (myGame.is_legal(r, c)) {
                myGame.make_move (r, c, currentPlayer);

                if (myGame.check_win(human)) gameWon = true;
                currentPlayer = ai;
            } else {
                std::cout << "Invalid move!. Try again." << std::endl;
            }

        } else {
            // --- AI Turn ---
            std::cout << "AI is thinking..." << std::endl;
            std::pair<int, int> best = myGame.get_best_move(ai, 1000);
            myGame.make_move(best.first, best.second, ai);
            std::cout << "AI plays: " << (char)('A' + best.first) << 1 + best.second << std::endl;

            if (myGame.check_win(ai)) gameWon = true;
            currentPlayer = human;
        }
    }

    myGame.display();
    std::cout << "Game Over! " << (myGame.check_win(human) ? "You Win!" : "AI Wins!") << std::endl;
    return 0;
}
