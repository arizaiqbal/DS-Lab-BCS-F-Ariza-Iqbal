#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int N = 5;

void displayMatrix(int mat[][N]) {
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

void displayList(int** list, int* sizes) {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < N; i++) {
        cout << i+1 << " -> ";
        for (int j = 0; j < sizes[i]; j++)
            cout << list[i][j] << " ";
        cout << endl;
    }
}

void BFS(int** adj, int* sizes, int start) {
    bool visited[N] = {false};
    queue<int> q;

    q.push(start);
    visited[start] = true;

    cout << "\nBFS: ";

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u+1 << " ";

        for (int i = 0; i < sizes[u]; i++) {
            int v = adj[u][i] - 1;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void DFSUtil(int u, bool visited[], int** adj, int* sizes) {
    visited[u] = true;
    cout << u+1 << " ";

    for (int i = 0; i < sizes[u]; i++) {
        int v = adj[u][i] - 1;
        if (!visited[v])
            DFSUtil(v, visited, adj, sizes);
    }
}

void DFS(int** adj, int* sizes, int start) {
    bool visited[N] = {false};
    cout << "\nDFS: ";
    DFSUtil(start, visited, adj, sizes);
}

int main() {

    int matrix[N][N] = {0};

    int edges[][2] = {
        {1,4}, {1,2},
        {2,4}, {4,5},
        {5,2}, {3,5}
    };

    int E = 6;

    // Create matrix
    for (int i = 0; i < E; i++) {
        int a = edges[i][0] - 1;
        int b = edges[i][1] - 1;
        matrix[a][b] = matrix[b][a] = 1;
    }

    displayMatrix(matrix);

    int* sizes = new int[N]{0};
    int** adj = new int*[N];

    for (int i = 0; i < N; i++)
        adj[i] = new int[N];

    for (int i = 0; i < E; i++) {
        int a = edges[i][0] - 1;
        int b = edges[i][1] - 1;

        adj[a][sizes[a]++] = b + 1;
        adj[b][sizes[b]++] = a + 1;
    }

    displayList(adj, sizes);

    BFS(adj, sizes, 0); 
    DFS(adj, sizes, 0);

    return 0;
}
