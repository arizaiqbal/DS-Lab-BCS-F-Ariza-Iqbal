#include <iostream>
#include <cstring>
using namespace std;

const int INF = 1e9;

int idx(char c) { return c - 'A'; }

void dijkstra(int graph[][6], int start, int end) {
    int dist[6];
    bool visited[6] = {false};
    int parent[6];

    for (int i = 0; i < 6; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int c = 0; c < 6; c++) {
        int u = -1;

        for (int i = 0; i < 6; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        visited[u] = true;

        for (int v = 0; v < 6; v++) {
            if (graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\nShortest Distance = " << dist[end];

    cout << "\nPath: ";
    int temp[6], k = 0;
    for (int v = end; v != -1; v = parent[v])
        temp[k++] = v;

    for (int i = k - 1; i >= 0; i--)
        cout << char(temp[i] + 'A') << " ";
}

int main() {

    int graph[6][6] = {0};

    graph[idx('B')][idx('A')] = 4;
    graph[idx('A')][idx('B')] = 4;

    graph[idx('B')][idx('C')] = 9;
    graph[idx('C')][idx('B')] = 9;

    graph[idx('A')][idx('D')] = 8;
    graph[idx('D')][idx('A')] = 8;

    graph[idx('C')][idx('D')] = 6;
    graph[idx('D')][idx('C')] = 6;

    graph[idx('C')][idx('E')] = 14;
    graph[idx('E')][idx('C')] = 14;

    graph[idx('D')][idx('F')] = 4;
    graph[idx('F')][idx('D')] = 4;

    graph[idx('F')][idx('E')] = 3;
    graph[idx('E')][idx('F')] = 3;

    dijkstra(idx('B'), idx('E'));

    return 0;
}
