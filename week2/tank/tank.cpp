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

    // sparse graph so use djikstras to assess reachability.
    vector<vector<int>> dist(n, vector<int>(n, maxVal));
    for (int node = 0; node < n; node++) {
        priority_queue<pair<int,int>> q;
        q.push(make_pair(0, node));
        dist[node][node] = 0;
        pair<int, int> entry;
        while (q.size() != 0) {
            entry = q.top(); q.pop();
            int cur = entry.second;
            if (entry.first != dist[node][cur]) continue;
            for (int i = 0; i < graph[cur].size(); i++) {
                int nbrDist = graph[cur][i].first;
                int nbr = graph[cur][i].second;
                if (dist[node][cur] + nbrDist < dist[node][nbr]) {
                    dist[node][nbr] = dist[node][cur] + nbrDist;
                    q.push(make_pair(dist[node][nbr], nbr));
                }
            }
        }
    }

    // upto 100 queries.
    int q; cin >> q;
    for (int qNum = 0; qNum < q; qNum++) {
        int c, s, e;
        cin >> c >> s >> e;

        vector<vector<pair<int,int>>> closure(n, vector<pair<int,int>>());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] <= c) {
                    closure[i].push_back(make_pair(dist[i][j] * price[i], j));
                }
            }
        }

        priority_queue<pair<int,int>> q;
        vector<int> cost(n, maxVal);
        q.push(make_pair(0, s));
        cost[s] = 0;
        pair<int, int> entry;
        while (q.size() != 0) {
            entry = q.top(); q.pop();
            int cur = entry.second;
            if (entry.first != cost[cur]) continue;
            for (int i = 0; i < closure[cur].size(); i++) {
                int nbrDist = closure[cur][i].first;
                int nbr = closure[cur][i].second;
                if (cost[cur] + nbrDist < cost[nbr]) {
                    cost[nbr] = cost[cur] + nbrDist;
                    q.push(make_pair(cost[nbr], nbr));
                }
            }
        }

        if (cost[e] == maxVal) cout << "impossible\n";
        else cout << cost[e] << "\n";
    }
}