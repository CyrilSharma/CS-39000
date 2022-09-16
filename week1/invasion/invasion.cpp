// Author: Cyril Sharma
// You may use my anonymized code.
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define maxVal 1000000000

int main() {
    int n, m, a, k;
    cin >> n >> m >> a >> k;
    // if at least one value is nonzero
    while (n|m|a|k) {
        // construct an adjacency list.
        vector<vector<pair<int,int>>> graph(n+1, vector<pair<int,int>>());
        vector<int> bases(a);
        for (int i = 0; i < m; i++) {
            int t1, t2, d;
            cin >> t1 >> t2 >> d;
            graph[t1].push_back(make_pair(d, t2));
            graph[t2].push_back(make_pair(d, t1));
        }
        for (int i = 0; i < a; i++) {
            int base; cin >> base;
            bases[i] = base;
        }

        int numUnsafe = 0;
        // track whether or not tile is unsafe.
        vector<int> unsafe(n+1, 0);
        // this array will store the shortest path from any unsafe tile to any other tile.
        vector<int> bestDist(n+1, maxVal);
        for (int ind = 0; ind < a; ind++) {
            int base = bases[ind];
            // just fancy notation for min heap
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
            // standard djikstras.
            vector<int> dist(n+1, maxVal);
            q.push(make_pair(0, base));
            dist[base] = 0;
            pair<int,int> entry;
            while (q.size() != 0) {
                entry = q.top(); q.pop();
                int node = entry.second; int nodeDist = entry.first;
                if (nodeDist != dist[node]) continue;
                if (nodeDist >= k) break;
                // These checks are really important, they're the entire reason why this code can even pass.
                // Essentially, these stop the recursion when it is definitely not possible to improve upon the search
                // I.e the current distance is higher then the best distance, so there's no way to improve ndoes in this 
                // direction
                if (bestDist[node] <= nodeDist) continue;
                else bestDist[node] = nodeDist;
                // only count unsafe nodes if they have not already been counted.
                if (!unsafe[node]) {
                    unsafe[node] = 1; 
                    numUnsafe++;
                }
                for (int i = 0; i < graph[node].size(); i++) {
                    int nbr = graph[node][i].second;
                    int nbrD = graph[node][i].first;
                    // edge relaxation.
                    if (dist[node] + nbrD < dist[nbr]) {
                        dist[nbr] = dist[node] + nbrD;
                        q.push(make_pair(dist[nbr], nbr));
                    }
                }
            }
            cout << n - numUnsafe << "\n";
        }
        cout << "\n";
        cin >> n >> m >> a >> k;
    }
}