#include <iostream>
#include <vector>
using namespace std;

int timer = 0;

void DFS(int u, int parent,
         vector<vector<int>>& adj,
         vector<bool>& visited,
         vector<int>& disc,
         vector<int>& low,
         vector<bool>& articulation)
{
    visited[u] = true;
    disc[u] = low[u] = ++timer;

    int children = 0;

    for (int v : adj[u])
    {
        if (v == parent)
            continue;

        if (!visited[v])
        {
            children++;

            DFS(v, u, adj, visited, disc, low, articulation);

            low[u] = min(low[u], low[v]);

            if (parent == -1 && children > 1)
                articulation[u] = true;

            if (parent != -1 && low[v] >= disc[u])
                articulation[u] = true;
        }
        else
        {

            low[u] = min(low[u], disc[v]);
        }
    }
}

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> adj(V);

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(V, false);
    vector<int> disc(V, 0);
    vector<int> low(V, 0);
    vector<bool> articulation(V, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            DFS(i, -1, adj, visited, disc, low, articulation);
    }

    cout << "\nArticulation Points are: ";

    bool found = false;

    for (int i = 0; i < V; i++)
    {
        if (articulation[i])
        {
            cout << i << " ";
            found = true;
        }
    }

    if (!found)
        cout << "None";

    cout << endl;

    return 0;
}