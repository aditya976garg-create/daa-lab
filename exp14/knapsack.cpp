#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    int weight;
    int value;
};

class Knapsack {
    vector<Item> items;
    int n, W;
    vector<vector<int>> dp;

public:
    Knapsack(const vector<Item> &it, int capacity) : items(it), n(it.size()), W(capacity) {
        dp.assign(n + 1, vector<int>(W + 1, 0));
    }

    int compute() {
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                dp[i][w] = dp[i - 1][w];
                if (items[i - 1].weight <= w)
                    dp[i][w] = max(dp[i][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
        }
        return dp[n][W];
    }

    vector<int> selectedItems() {
        vector<int> chosen;
        int w = W;
        for (int i = n; i > 0; i--) {
            if (dp[i][w] != dp[i - 1][w]) {
                chosen.push_back(i);
                w -= items[i - 1].weight;
            }
        }
        reverse(chosen.begin(), chosen.end());
        return chosen;
    }

    void printTable() {
        cout << right;
        cout << "DP table (rows = items, columns = capacity):\n";
        cout << setw(8) << " ";
        for (int w = 0; w <= W; w++) cout << setw(4) << w;
        cout << "\n";
        for (int i = 0; i <= n; i++) {
            if (i == 0) cout << setw(8) << "none";
            else cout << setw(8) << ("item " + to_string(i));
            for (int w = 0; w <= W; w++) cout << setw(4) << dp[i][w];
            cout << "\n";
        }
    }

    void solve() {
        cout << "Capacity: " << W << "\n";
        cout << left << setw(8) << "Item" << setw(10) << "Weight" << "Value\n";
        for (int i = 0; i < n; i++)
            cout << left << setw(8) << (i + 1) << setw(10) << items[i].weight << items[i].value << "\n";
        cout << "\n";

        int best = compute();
        printTable();

        vector<int> chosen = selectedItems();
        int totalWeight = 0;
        cout << "\nSelected items:\n";
        for (int idx : chosen) {
            cout << "  Item " << idx << " (weight = " << items[idx - 1].weight
                 << ", value = " << items[idx - 1].value << ")\n";
            totalWeight += items[idx - 1].weight;
        }
        if (chosen.empty()) cout << "  (none)\n";
        cout << "\nTotal weight: " << totalWeight << "\n";
        cout << "Maximum value: " << best << "\n";
    }
};

int main() {
    cout << "===== Test 1 =====\n";
    Knapsack t1({{1, 1}, {3, 4}, {4, 5}, {5, 7}}, 7);
    t1.solve();

    cout << "\n===== Test 2 =====\n";
    Knapsack t2({{2, 3}, {3, 4}, {4, 5}, {5, 6}}, 5);
    t2.solve();

    cout << "\n===== Test 3 =====\n";
    Knapsack t3({{5, 10}, {6, 12}}, 4);
    t3.solve();

    return 0;
}
