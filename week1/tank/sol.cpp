/**
 * @author Trung Dang (dang28@purdue.edu)
 * @date 2022-09-05
 * @brief Solve independently for each query as follow:
 * 
 * Construct a new graph where each node is represented by (u, cap), where u is the actual node on the graph
 * and cap is the current capacity of fuel in the tank. Add edges as follow:
 * - For each (u, cap), connect it to (u, cap + 1) with weight p[u], representing the action of
 *   buying one unit of fuel as u.
 * - For each (u, cap), connect it to (v, cap - w) with weight 0 for a road (u, v) with length d on the
 *   actual graph, representing the action of traverse the road (u, v).
 * We simply find the shortest path from (s, 0) to (e, c) to some c.
 * 
 * Note that we can prove that the number of nodes in this new graph is O(nc), and the number of edges is O(mc).
 * Therefore, the complexity for each test case is O(c (m + n) log m)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> p(n);
    vector adj(n, vector<pair<int, int>>());
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    function<int(int, int, int)> dijkstra;
    dijkstra = [&](int s, int e, int cap) {
        vector dst(n, vector<int>(cap + 1, numeric_limits<int>::max()));
        using state = tuple<int, int, int>; // distance, node, current_cap
        priority_queue<state, vector<state>, greater<state>> pq;
        dst[s][0] = 0; pq.push({0, s, 0});
        while (!pq.empty()) {
            auto [d, u, c] = pq.top(); pq.pop(); // distance, node u, current cap c
            // add one unit of gas to this tate
            if (c < cap && dst[u][c + 1] > d + p[u]) {
                dst[u][c + 1] = d + p[u];
                pq.push({d + p[u], u, c + 1});
            }
            // traverse to other nodes
            for (auto [v, w] : adj[u]) {
                if (c >= w && dst[v][c - w] > d) {
                    dst[v][c - w] = d;
                    pq.push({d, v, c - w});
                }
            }
        }
        return *min_element(dst[e].begin(), dst[e].end());
    };
    int q; cin >> q;
    while (q--) {
        int cap, s, e; cin >> cap >> s >> e;
        int ans = dijkstra(s, e, cap);
        if (ans == numeric_limits<int>::max()) {
            cout << "impossible\n";
        } else {
            cout << ans << '\n';
        }
    }
}
