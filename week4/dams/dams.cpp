/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Parent-first Tree Traversal 
 * The core idea is that if you know how much water the parent node needs
 * then you know you must dump at least that much water into the parent.
 * Thus, the amount you have to add is however much is needed to exceed the capacity OR
 * however much water is needed to dump sufficient water into the parent, whichever is larger.
 * Compute this for all nodes, then find the maximum.
 * @date 2022-09-24
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w, d, c, u;
    cin >> n >> w;
    vector<vector<int>> child(n+1);
    vector<int> cap(n+1, 0), amt(n+1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> d >> c >> u;
        child[d].push_back(i);
        cap[i] = c;
        amt[i] = u;
    }

    long long best = 1e18;
    function<void(int, long long)> search;
    search = [&](int node, ll prev) {
        ll add = max((ll)(prev - amt[node]), (ll)(cap[node] - amt[node]));
        best = min(best, add);
        for (auto c: child[node]) {
            search(c, add);
        }
    };
    search(0,w);
    cout << best << "\n";
}