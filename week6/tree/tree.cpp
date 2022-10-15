/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Kruskals.
 * I'm not sure if there is a way to do this with Prims, as you are essentially forced to use
 * certain edges. With Kruskal's this is a very simple contraint though, just connect everything
 * it says is already connected (first e nodes, p cables), then add edges until you have a DSU of size n.
 * @date 2022-10-13
 */
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
struct DSU {
    vi parent, size;
    DSU(int n) {parent = vi(n,-1); size = vi(n,1);}
    int find(int v) {
        if (parent[v] == -1) return v;
        return parent[v] = find(parent[v]);
    }
    void merge(int a, int b) {
        int r1 = find(a); int r2 = find(b);
        if (r1 == r2) return;
        if (size[r2] > size[r1]) swap(r1,r2);
        parent[r2] = r1; size[r1] += size[r2];
    }
};

int main() {
    int n, e, p;
    cin >> n >> e >> p;
    DSU ds = DSU(n);
    using ld = long double;
    vector<pair<ld,ld>> nodes(n);
    for (int i = 0; i < n; i++) {
        ld x, y;
        cin >> x >> y;
        nodes[i] = {x,y};
        if (i < e && i > 0) ds.merge(0, i);
    }

    for (int i = 0; i < p; i++) {
        int a, b;
        cin >> a >> b;
        ds.merge(a-1,b-1);
    }

    vector<tuple<ld,int,int>> edges;
    for (int a = e; a < n; a++) {
        for (int b = 0; b < a; b++) {
            auto [x1,y1] = nodes[a];
            auto [x2,y2] = nodes[b];
            ld d = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
            edges.push_back({d,a,b});
        }
    }
    sort(edges.begin(), edges.end());

    ld total = 0;
    for (auto [d,a,b] : edges) {
        if (ds.find(a) != ds.find(b)) {
            ds.merge(a,b);
            total += d;
        }
        if (ds.size[ds.find(0)] == n) break;
    }
    cout << fixed << total << "\n";
}