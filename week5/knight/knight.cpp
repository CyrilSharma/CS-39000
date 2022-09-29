#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, u, v, w;
    cin >> n >> m;
    using vi = vector<int>;

    vi mat(n);
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }

    vector<vector<pair<int,int>>> graph(n);
    vector<vi> parent(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        graph[v].push_back({u,w});
        parent[u].push_back(v);
    }

    vi roots;
    for (int i = 0; i < n; i++) {
        if (parent[i].size() == 0)
            roots.push_back(i);
    }
    
    vi req(mat); vi vis(n);
    function<void(int,int)> search;
    search = [&](int node, int amount) {
        if (graph[node].size() == 0) {
            return;
        }
        for (auto [child, num]: graph[node]) {
            if (vis[child] == 0) {
                search(child, num * amount + mat[child]);
                vis[child] = 1;
            }
            else 
                search(child, num * amount);
            req[child] += num * amount;
        }
    };

    for (auto r: roots)
        search(r, mat[r]);

    for (auto r: req) 
        cout << r << " ";
    cout << "\n";
}