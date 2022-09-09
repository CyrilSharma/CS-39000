// Author: Cyril Sharma
// You may use my anonymized code
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define maxVal 1e200

int main() {
    while (true) {
        int c; cin >> c;
        if (c == 0) break;
        string temp;
        // make a map so we can index with numbers instead of strings.
        map<string, int> m;
        for (int i = 0; i < c; i++) {
            cin >> temp;
            m[temp] = i;
        }

        int r; cin >> r;
        string c1, c2; int d1, d2; char a;
        // build an adjacency list (note that this is a directed graph)
        vector<vector<double>> graph(c, vector<double>(c, maxVal));
        for (int i = 0; i < r; i++) {
            cin >> c1 >> c2 >> d1 >> a >> d2;
            // use -log because adding logs essentially captures the concept of multiplication
            // by using negative logs, whenever a currency produces more of another currency,
            // that will create a negative edge weight, allowing negative edge cycles to be detected
            // only when it is possible to make more and more currency.
            graph[m[c1]][m[c2]] = -log((double) d2 / (double) d1);
        }

        // floodfill. the graph is not necessarily connected so we must find nodes in each of the seperate groups to intiiliaze.
        queue<int> q;
        vector<int> group(c, -1);
        vector<int> starts;
        for (int i = 0; i < c; i++) {
            if (group[i] == -1) {
                starts.push_back(i);
                q.push(i);
                group[i] = i;
            }
            else continue;
            while (q.size() != 0) {
                int node = q.front(); q.pop();
                group[node] = group[i];
                for (int j = 0; j < graph[node].size(); j++) {
                    if (graph[node][j] != maxVal && group[j] == -1) {
                        q.push(j);
                    }
                }
            }
        }

        // initialize all chunks to zero.
        vector<double> dist(c, maxVal);
        for (int i = 0; i < starts.size(); i++) {
            dist[i] = 0.0;
        }

        // bellman ford.
        for (int i = 0; i < c-1; i++) {
            for (int j = 0; j < c; j++) {
                for (int k = 0; k < c; k++) {
                    if (dist[j] + graph[j][k] < dist[k]) {
                        dist[k] = dist[j] + graph[j][k];
                    }
                }
            }
        }
        
        // standard negartive cycle detection for bellman ford
        bool arbitrage = false;
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < graph[j].size(); k++) {
                if (dist[j] != maxVal && dist[j] + graph[j][k] < dist[k]) {
                    arbitrage = true;
                    break;
                }
            }
            if (arbitrage) break;
        }

        if (!arbitrage) cout << "Ok\n";
        else cout << "Arbitrage\n";
    }
}