#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NQueens {
    int n;
    vector<int> board;
    vector<bool> cols, diag1, diag2;
    int count;
    int printLimit;

public:
    NQueens(int n, int printLimit) : n(n), board(n, -1), cols(n, false),
                                     diag1(2 * n - 1, false), diag2(2 * n - 1, false),
                                     count(0), printLimit(printLimit) {}

    void printBoard() {
        cout << "Solution " << count << ":\n";
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++)
                cout << (board[r] == c ? "Q " : ". ");
            cout << "\n";
        }
        cout << "Positions (row, col): ";
        for (int r = 0; r < n; r++) {
            cout << "(" << r + 1 << "," << board[r] + 1 << ")";
            if (r + 1 < n) cout << " ";
        }
        cout << "\n\n";
    }

    void solve(int row) {
        if (row == n) {
            count++;
            if (count <= printLimit) printBoard();
            return;
        }
        for (int c = 0; c < n; c++) {
            if (cols[c] || diag1[row + c] || diag2[row - c + n - 1]) continue;
            board[row] = c;
            cols[c] = diag1[row + c] = diag2[row - c + n - 1] = true;
            solve(row + 1);
            cols[c] = diag1[row + c] = diag2[row - c + n - 1] = false;
            board[row] = -1;
        }
    }

    int run() {
        solve(0);
        return count;
    }
};

int main() {
    int sizes[] = {4, 6, 3, 8};
    int limits[] = {2, 1, 1, 1};

    for (int i = 0; i < 4; i++) {
        int n = sizes[i];
        cout << "===== N = " << n << " =====\n";
        NQueens q(n, limits[i]);
        int total = q.run();
        if (total == 0) cout << "No solution exists.\n";
        cout << "Total solutions for N = " << n << ": " << total << "\n\n";
    }

    return 0;
}
