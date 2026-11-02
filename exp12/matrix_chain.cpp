#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <iomanip>

using namespace std;

class MatrixChain {
    vector<int> p;
    int n;
    vector<vector<long long>> m;
    vector<vector<int>> s;

public:
    MatrixChain(const vector<int> &dims) : p(dims), n(dims.size() - 1) {
        m.assign(n + 1, vector<long long>(n + 1, 0));
        s.assign(n + 1, vector<int>(n + 1, 0));
    }

    long long compute() {
        for (int len = 2; len <= n; len++) {
            for (int i = 1; i <= n - len + 1; i++) {
                int j = i + len - 1;
                m[i][j] = LLONG_MAX;
                for (int k = i; k < j; k++) {
                    long long cost = m[i][k] + m[k + 1][j] + 1LL * p[i - 1] * p[k] * p[j];
                    if (cost < m[i][j]) {
                        m[i][j] = cost;
                        s[i][j] = k;
                    }
                }
            }
        }
        return m[1][n];
    }

    string parenthesization(int i, int j) {
        if (i == j) return "A" + to_string(i);
        return "(" + parenthesization(i, s[i][j]) + " x " + parenthesization(s[i][j] + 1, j) + ")";
    }

    void printCostTable() {
        cout << "Cost table m[i][j]:\n";
        cout << setw(8) << " ";
        for (int j = 1; j <= n; j++) cout << setw(8) << ("A" + to_string(j));
        cout << "\n";
        for (int i = 1; i <= n; i++) {
            cout << setw(8) << ("A" + to_string(i));
            for (int j = 1; j <= n; j++) {
                if (j < i) cout << setw(8) << "-";
                else cout << setw(8) << m[i][j];
            }
            cout << "\n";
        }
    }

    void printSplitTable() {
        cout << "\nSplit table s[i][j]:\n";
        cout << setw(8) << " ";
        for (int j = 1; j <= n; j++) cout << setw(8) << ("A" + to_string(j));
        cout << "\n";
        for (int i = 1; i <= n; i++) {
            cout << setw(8) << ("A" + to_string(i));
            for (int j = 1; j <= n; j++) {
                if (j <= i) cout << setw(8) << "-";
                else cout << setw(8) << s[i][j];
            }
            cout << "\n";
        }
    }

    void solve() {
        cout << "Matrix dimensions:\n";
        for (int i = 1; i <= n; i++)
            cout << "A" << i << " : " << p[i - 1] << " x " << p[i] << "\n";
        cout << "\n";

        long long result = compute();

        printCostTable();
        printSplitTable();

        cout << "\nOptimal parenthesization: " << parenthesization(1, n) << "\n";
        cout << "Minimum number of scalar multiplications: " << result << "\n";
    }
};

int main() {
    cout << "===== Test 1 =====\n";
    MatrixChain t1({10, 30, 5, 60});
    t1.solve();

    cout << "\n===== Test 2 =====\n";
    MatrixChain t2({40, 20, 30, 10, 30});
    t2.solve();

    cout << "\n===== Test 3 =====\n";
    MatrixChain t3({30, 35, 15, 5, 10, 20, 25});
    t3.solve();

    return 0;
}
