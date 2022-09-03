#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define maxVal 1000000000

int main() {
    int n, m, a, k;
    cin >> n >> m >> a >> k;
    while (n || m || a || k) {
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
        vector<int> unsafe(n+1, 0);
        for (int ind = 0; ind < a; ind++) {
            int base = bases[ind];
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
            vector<int> dist(n, maxVal);
            q.push(make_pair(0, base));
            dist[base] = 0;
            pair<int,int> entry;
            while (q.size() != 0) {
                entry = q.top(); q.pop();
                if (entry.first != dist[entry.second]) continue;
                if (entry.first >= k) break;
                if (!unsafe[entry.second]) {
                    unsafe[entry.second] = 1; 
                    numUnsafe++;
                }
                for (int i = 0; i < graph[entry.second].size(); i++) {
                    int nbr = graph[entry.second][i].second;
                    int nbrDist = graph[entry.second][i].first;
                    if (dist[entry.second] + nbrDist < dist[nbr]) {
                        dist[nbr] = dist[entry.second] + nbrDist;
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