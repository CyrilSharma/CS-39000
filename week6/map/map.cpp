#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
struct DSU {
    vi size, parent;
    DSU(int n) {size=vi(n,1); parent=vi(n,-1);}
    int find(int v) {
        if (parent[v] == -1) return v;
        return parent[v] = find(parent[v]);
    }
    void merge(int a, int b) {
        int r1 = find(a); int r2 = find(b);
        if (r1 == r2) return;
        if (size[r2] > size[r1]) swap(r2, r1);
        parent[r2] = r1; size[r1] += size[r2];
    }
};
int main() {
    int n;
    cin >> n;
    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int d; cin >> d;
            edges.push_back({d,i,j});
        }
    }
    sort(edges.begin(), edges.end());
    DSU ds = DSU(n);
    for (auto [d,a,b]: edges) {
        if (ds.find(a) != ds.find(b)) {
            ds.merge(a,b);
            cout << a+1 << " " << b+1 << "\n";
        }
        if (ds.size[ds.find(0)] == n) break;
    }
}