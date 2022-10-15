/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Track merges.
 * Instinctively, BFS seems to be the natural approach to this problem, but it's unfortunately really slow,
 * As each integer which describes a person can potentially allow them to be connected to everyone else!
 * A faster way to find paths is instead to have one representative for each number (the first node described
 * by that number) and then whenever a node with that number is found you merge it into the UF.
 * Since each merge connects nodes that weren't previously connected, it's sufficient to keep track of all 
 * the merges, and the print them out at the end.
 * @date 2022-10-13
 */
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
struct UF {
    vi parent, size;
    UF(int s) {
        parent = vi(s,-1);
        size = vi(s,1);
    }
    int find(int i) {
        int ret = (parent[i] != -1) ? find(parent[i]) : i;
        if (parent[i] != -1) parent[i] = ret;
        return ret;
    }
    void merge(int a, int b) {
        if (size[a] > size[b]) {
            parent[a] = b;
            size[b] += size[a];
        }
        else {
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

int main() {
    int n, m, d;
    cin >> n;
    map<int,int> mp;
    UF u = UF(n+1);
    vector<tuple<int,int,int>> edges;
    for (int i = 1; i <= n; i++) {
        cin >> m;
        for (int j = 0; j < m; j++) {
            cin >> d;
            if (mp.count(d) == 0) mp[d] = i;
            else {
                int a = u.find(mp[d]);
                int b = u.find(i);
                if (a != b) {
                    u.merge(a, b);
                    edges.push_back({i,mp[d],d});
                }
            }
        }
    }
    if (u.size[u.find(1)] != n) {
        cout << "impossible\n";
        return 0;
    }

    for (auto [a,b,w]: edges) {
        cout << a << " " << b << " " << w << "\n";
    }
}