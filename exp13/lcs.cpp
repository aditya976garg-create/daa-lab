#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class LCS {
    string a, b;
    int n, m;
    vector<vector<int>> dp;

public:
    LCS(const string &x, const string &y) : a(x), b(y), n(x.size()), m(y.size()) {
        dp.assign(n + 1, vector<int>(m + 1, 0));
    }

    int compute() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i - 1] == b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }

    string getSequence() {
        string res;
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (a[i - 1] == b[j - 1]) {
                res.push_back(a[i - 1]);
                i--;
                j--;
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }

    void printTable() {
        cout << "DP table:\n";
        cout << setw(6) << " " << setw(4) << " ";
        for (int j = 0; j < m; j++) cout << setw(4) << b[j];
        cout << "\n";
        for (int i = 0; i <= n; i++) {
            if (i == 0) cout << setw(6) << " ";
            else cout << setw(6) << a[i - 1];
            for (int j = 0; j <= m; j++) cout << setw(4) << dp[i][j];
            cout << "\n";
        }
    }

    void solve() {
        cout << "String 1: " << a << "\n";
        cout << "String 2: " << b << "\n\n";
        int len = compute();
        printTable();
        cout << "\nLength of LCS: " << len << "\n";
        cout << "LCS: " << (len == 0 ? "(empty)" : getSequence()) << "\n";
    }
};

int main() {
    cout << "===== Test 1 =====\n";
    LCS t1("AGGTAB", "GXTXAYB");
    t1.solve();

    cout << "\n===== Test 2 =====\n";
    LCS t2("ABCBDAB", "BDCABA");
    t2.solve();

    cout << "\n===== Test 3 =====\n";
    LCS t3("ABC", "XYZ");
    t3.solve();

    return 0;
}
