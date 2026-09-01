//Name: Aditya Garg
//Roll Number: 25/DA/005
//4. Write a program to find the Connected Components of a graph using Depth First Search (DFS).
#include <iostream>
using namespace std;

const int MAX = 100;

void DFS(int graph[MAX][MAX], int visited[], int n, int vertex){
    // Mark the current vertex as visited
    visited[vertex] = 1;
    // Print the vertex
    cout << vertex << " ";
    
    // Visit all adjacent vertices
    for (int i = 0; i < n; i++){
        if (graph[vertex][i] == 1 && visited[i] == 0)
        {
            DFS(graph, visited, n, i);
        }
    }
}

int main(){
    int graph[MAX][MAX];
    int visited[MAX] = {0};
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter the adjacency matrix:\n";

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }
    int components = 0;
    cout << "\nConnected Components:\n";

    // Check every vertex
    for (int i = 0; i < n; i++){
        // If vertex is not visited, start a new DFS
        if (visited[i] == 0){
            components++;
            cout << "Component " << components << ": ";
            DFS(graph, visited, n, i);
            cout << endl;
        }
    }
    cout << "\nTotal Connected Components = " << components;
    return 0;
}