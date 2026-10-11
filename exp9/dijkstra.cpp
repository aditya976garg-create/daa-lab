#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef pair<long long, int> P;
const long long INF = numeric_limits<long long>::max();

vector<long long> dijkstra(int src, const vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();
    vector<long long> dist(n, INF);
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src;
    cin >> src;

    vector<long long> dist = dijkstra(src, adj);

    for (int i = 0; i < n; i++) {
        cout << "Distance from " << src << " to " << i << " = ";
        if (dist[i] == INF) cout << "INF";
        else cout << dist[i];
        cout << "\n";
    }
    return 0;
}
