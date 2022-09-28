#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, a, b, x, t, k;
    cin >> n;
    vector<vector<tuple<int,int,int>>> children(n+1);
    for (int i = 0; i < n-1; i++) {
        cin >> a >> b >> x >> t;
        children[a].push_back({b, x, t});
    }
    vector<int> req(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> k;
        req[i] = k;
    }
    function<double(int)> search;
    search = [&](int node) {
        if (req[node] != -1) {
            return (double)req[node];
        }
        double best = -1;
        for (auto child: children[node]) {
            double cur;
            auto [b,x,t] = child;
            double req = search(b);
            double p = (double)x / 100.0;
            if (t) cur = min(req/p, sqrt(req)/p);
            else cur = req/p;
            best = max(best, cur);
        }
        return best;
    };
    cout << fixed << search(1) << "\n";
}