#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Edge {
    int u, v, w;
};

class Graph {
    int V;
    vector<Edge> edges;

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    bool bellmanFord(int src, vector<long long> &dist, vector<int> &parent, vector<int> &cycle) {
        const long long INF = LLONG_MAX / 2;
        dist.assign(V, INF);
        parent.assign(V, -1);
        cycle.clear();
        dist[src] = 0;

        for (int i = 1; i <= V - 1; i++) {
            bool updated = false;
            for (const Edge &e : edges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    parent[e.v] = e.u;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        int x = -1;
        for (const Edge &e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                parent[e.v] = e.u;
                x = e.v;
                break;
            }
        }

        if (x == -1) return false;

        for (int i = 0; i < V; i++) x = parent[x];

        int cur = x;
        do {
            cycle.push_back(cur);
            cur = parent[cur];
        } while (cur != x);
        cycle.push_back(x);
        reverse(cycle.begin(), cycle.end());
        return true;
    }

    void printPath(int v, const vector<int> &parent) {
        vector<int> path;
        for (int cur = v; cur != -1; cur = parent[cur]) path.push_back(cur);
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << " -> ";
        }
    }

    void solve(int src) {
        vector<long long> dist;
        vector<int> parent, cycle;
        bool hasCycle = bellmanFord(src, dist, parent, cycle);

        cout << "Source vertex: " << src << "\n";
        if (hasCycle) {
            cout << "Negative-weight cycle detected!\n";
            cout << "Cycle: ";
            for (size_t i = 0; i < cycle.size(); i++) {
                cout << cycle[i];
                if (i + 1 < cycle.size()) cout << " -> ";
            }
            cout << "\n";
            return;
        }

        cout << "No negative-weight cycle found.\n\n";
        cout << left << setw(10) << "Vertex" << setw(12) << "Distance" << "Path\n";
        cout << string(40, '-') << "\n";
        const long long INF = LLONG_MAX / 2;
        for (int i = 0; i < V; i++) {
            cout << left << setw(10) << i;
            if (dist[i] == INF) {
                cout << setw(12) << "INF" << "unreachable\n";
            } else {
                cout << setw(12) << dist[i];
                printPath(i, parent);
                cout << "\n";
            }
        }
    }
};

int main() {
    cout << "===== Test 1: Graph without negative cycle =====\n";
    Graph g1(5);
    g1.addEdge(0, 1, 6);
    g1.addEdge(0, 2, 7);
    g1.addEdge(1, 2, 8);
    g1.addEdge(1, 3, 5);
    g1.addEdge(1, 4, -4);
    g1.addEdge(2, 3, -3);
    g1.addEdge(2, 4, 9);
    g1.addEdge(3, 1, -2);
    g1.addEdge(4, 0, 2);
    g1.addEdge(4, 3, 7);
    g1.solve(0);

    cout << "\n===== Test 2: Graph with negative cycle =====\n";
    Graph g2(4);
    g2.addEdge(0, 1, 1);
    g2.addEdge(1, 2, -1);
    g2.addEdge(2, 3, -1);
    g2.addEdge(3, 1, -1);
    g2.solve(0);

    return 0;
}
