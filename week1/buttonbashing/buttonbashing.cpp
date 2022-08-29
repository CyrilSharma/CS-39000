#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define maxVal 10000000

int n, t;
int b[16];

int graph[3601][16];
int dist[3601];
int queued[3601];

void buildGraph() {
    for (int i = 0; i < 3601; i++) {
        dist[i] = maxVal;
        queued[i] = 0;
        for (int j = 0; j < 16; j++) {
            graph[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (b[i] == 0) continue;
        if (b[i] > 0) {
            for (int j = b[i]; j < 3601; j++) {
                graph[j - b[i]][i] = j;
            }
            for (int j = 3600 - b[i]; j < 3601; j++) {
                graph[j][i] = 3600;
            }
        }
        else {
            for (int j = -b[i]; j < 3601; j++) {
                graph[j][i] = j + b[i];
            }
        }
    }
}


void djikstras() {
    priority_queue <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > heap;

    heap.push(make_pair(0, 0));
    dist[0] = 0;
    queued[0] = 1;

    int node, neighbor;
    while (heap.size() != 0) {
        node = heap.top().second;
        // cout << "node: " << node << " " << "dist: " << dist[node] << "\n";
        heap.pop();
        for (int j = 0; j < 16; j++) {
            neighbor = graph[node][j];
            if (neighbor == -1) continue;
            dist[neighbor] = min(dist[neighbor], dist[node] + 1);
            if (!queued[neighbor]) { 
                heap.push(make_pair(dist[neighbor], neighbor)); 
                queued[neighbor] = 1; 
            }
        }
    }
}

void calc() {
    buildGraph();
    djikstras();
    for (int i = t; i < 3601; i++) {
        if (dist[i] != maxVal) {
            cout << dist[i] << " " << i - t << "\n";
            return;
        }
    }
}

int main() {
    int numTests;
    scanf("%d\n", &numTests);
    for (int i = 0; i < numTests; i++) {
        scanf("%d %d", &n, &t);
        for (int k = 0; k < n; k++) {
            scanf("%d", &b[k]);
        }
        calc();
    }
}