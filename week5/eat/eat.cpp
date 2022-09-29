#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, s, t;
    cin >> n >> m;
    using vi = vector<int>;
    vi sat(n);
    for (int i = 0; i < n; i++) {
        cin >> sat[i];
    }
    vector<vi> graph(n);
    for (int i = 0; i < m; i++) {
        cin >> s >> t;
        graph[s].push_back(t);
    }

    vector<double> bestVal(n, -1);
    function<double(int)> search;
    search = [&](int node) {
        if (graph[node].size() == 0) {
            bestVal[node] = (double)sat[node];
            return (double)sat[node];
        }
        double best = -1;
        for (auto child: graph[node]) {
            double cval;
            if (bestVal[child] != -1) cval = bestVal[child];
            else cval = search(child);
            if (cval > sat[node] + cval/2.0) {
                best = max(best, cval);
            }
            else {
                best = max(best, sat[node] + cval/2.0);
            }
        }
        bestVal[node] = best;
        return best;
    };
    search(0);
    // ALWAYS REMEMBER TO PUT fixed WITH DOUBLES.
    cout << fixed << bestVal[0] << "\n";
}