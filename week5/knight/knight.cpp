#include <bits/stdc++.h>
using namespace std;
int main() {
    // Note to self, never assume the answer fits within integer bounds...
    int n, m, u, v, w;
    cin >> n >> m;
    using vi = vector<int>;
    using ll = long long;
    using vll = vector<ll>;

    vll mat(n);
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }

    vector<vector<pair<int,ll>>> graph(n);
    vector<vi> parent(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        graph[v].push_back({u,w});
        parent[u].push_back(v);
    }

    queue<pair<int,ll>> q;
    for (int i = 0; i < n; i++) {
        if (parent[i].size() == 0) {
            q.push({i, mat[i]});
        }
    }
    
    vll req(mat);
    vi count(n);
    while (q.size() != 0) {
        auto [node, amount] = q.front(); q.pop();
        for (auto [child, num]: graph[node]) {
            req[child] += num * amount;
            count[child]++;
            if (count[child] == parent[child].size()) {
                q.push({child, req[child]});
            }
        }
    }

    for (auto r: req) 
        cout << r << " ";
    cout << "\n";
}