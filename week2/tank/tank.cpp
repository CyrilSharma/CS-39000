#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

#define maxVal 1000000000

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> graph(n, vector<pair<int,int>>());
    vector<int> price(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &price[i]);
    }

    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back(make_pair(d, v));
        graph[v].push_back(make_pair(d, u));
    }

    // upto 100 queries.
    int q; cin >> q;
    for (int qNum = 0; qNum < q; qNum++) {
        int c, s, e;
        cin >> c >> s >> e;

        vector<vector<pair<int,int>> pgraph;
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (graph[i][j] <= c) pgraph[i].push_back(graph[i][j]);
            }
        }

        priority_queue<pair<int,int>> q;
        vector<int> dist(n, maxVal);
        q.push(make_pair(0, s));
        cost[s] = 0;
        pair<int, int> entry;
        while (q.size() != 0) {
            entry = q.top(); q.pop();
            int cur = entry.second;
            if (entry.first != cost[cur]) continue;
            for (int i = 0; i < pgraph[cur].size(); i++) {
                int nbrDist = pgraph[cur][i].first;
                int nbr = pgraph[cur][i].second;
                if (dist[cur] + nbrDist < dist[nbr]) {
                    dist[nbr] = dist[cur] + nbrDist;
                    q.push(make_pair(dist[nbr], nbr));
                }
            }
        }

        // now only adds nodes that could be on the path.
        vector<vector<pair<int,int>>> closure(n, vector<pair<int,int>>());
        for (int i = 0; i < n; i++) {
            if (dist[i] == maxVal) continue;
            for (int j = 0; j < n; j++) {
                if (dist[j] == maxVal) continue;
                closure[i].push_back(make_pair(dist[i][j] * price[i], j));
            }
        }

        if (cost[e] == maxVal) cout << "impossible\n";
        else cout << cost[e] << "\n";
    }
}