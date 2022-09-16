#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

#define maxVal 1000000000

typedef vector<vector<pair<int,int>>> adjl;

int main() {
    int n, m;
    cin >> n >> m;
    adjl graph(n, vector<pair<int,int>>());
    vector<int> price(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
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

        // change to reccomended graph.
        adjl cgraph((c+1)*n, vector<pair<int,int>>());
        int prev = 0;
        for (int i = 0; i < n; i++) {
            // should be fine.
            for (int j = 0; j < c; j++) {
                cgraph[prev].push_back(make_pair(price[i], prev+1));
                prev++;
            }
            prev++;

            for (int j = 0; j < graph[i].size(); j++) {
                int nbr = graph[i][j].second;
                int nbrDist = graph[i][j].first;
                if (nbrDist > c) continue;
                if (dist[nbr][e] == maxVal) continue;
                for (int k = nbrDist; k <= c; k++) {
                    cgraph[(c+1)*i + k].push_back(make_pair(0, (c+1)*nbr + k - nbrDist));
                }
            }
        }

        // can be quite expensive ~30 mil.
        priority_queue<pair<int,int>> q;
        vector<int> cost(n*(c+1), maxVal);
        q.push(make_pair(0, s*(c+1)));
        cost[s*(c+1)] = 0;
        pair<int, int> entry;
        while (q.size() != 0) {
            entry = q.top(); q.pop();
            int cur = entry.second;
            if (entry.first != cost[cur]) continue;
            for (int i = 0; i < cgraph[cur].size(); i++) {
                int nbrDist = cgraph[cur][i].first;
                int nbr = cgraph[cur][i].second;
                if (cost[cur] + nbrDist < cost[nbr]) {
                    cost[nbr] = cost[cur] + nbrDist;
                    q.push(make_pair(cost[nbr], nbr));
                }
            }
        }

        if (cost[e*(c+1)] == maxVal) cout << "impossible\n";
        else cout << cost[e*(c+1)] << "\n";
    }
}