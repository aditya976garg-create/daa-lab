#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rankVal;

public:
    DSU(int n) {
        parent.resize(n);
        rankVal.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y)
            return false;

        if (rankVal[x] < rankVal[y])
            swap(x, y);

        parent[y] = x;

        if (rankVal[x] == rankVal[y])
            rankVal[x]++;

        return true;
    }
};

void prims(int n, vector<vector<pair<int, int>>>& adj) {
    vector<bool> visited(n, false);
    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>
    > pq;

    pq.push({0, 0, -1});

    int totalWeight = 0;
    int edges = 0;

    cout << "\nPrim's Algorithm:\n";

    while (!pq.empty()) {
        auto [weight, u, parent] = pq.top();
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        totalWeight += weight;

        if (parent != -1) {
            cout << parent + 1 << " - " << u + 1
                 << " : " << weight << '\n';
            edges++;
        }

        for (auto [v, w] : adj[u]) {
            if (!visited[v])
                pq.push({w, v, u});
        }
    }

    if (edges != n - 1) {
        cout << "Minimum Spanning Tree does not exist. Graph is disconnected.\n";
    } else {
        cout << "Total weight: " << totalWeight << '\n';
    }
}

void kruskals(int n, vector<tuple<int, int, int>>& edgeList) {
    sort(edgeList.begin(), edgeList.end());

    DSU dsu(n);
    int totalWeight = 0;
    int edges = 0;

    cout << "\nKruskal's Algorithm:\n";

    for (auto [weight, u, v] : edgeList) {
        if (dsu.unite(u, v)) {
            cout << u + 1 << " - " << v + 1
                 << " : " << weight << '\n';

            totalWeight += weight;
            edges++;

            if (edges == n - 1)
                break;
        }
    }

    if (edges != n - 1) {
        cout << "Minimum Spanning Tree does not exist. Graph is disconnected.\n";
    } else {
        cout << "Total weight: " << totalWeight << '\n';
    }
}

int main() {
    int n, m;

    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    vector<tuple<int, int, int>> edgeList;

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        u--;
        v--;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});

        edgeList.push_back({w, u, v});
    }

    prims(n, adj);
    kruskals(n, edgeList);

    return 0;
}
