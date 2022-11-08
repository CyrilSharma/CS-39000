#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> tree;
    SegTree(vector<int> array) {
        int p = 1;
        while (p < array.size()) p *= 2;
        tree = vector<int>(p * 2);
        build(array);
    }
    void build(vector<int> array) {
        int n = tree.size();
        for (int i = 0; i < array.size(); i++)
            tree[n/2 + i] = array[i];
        for (int i = n-1; i > 1; i--)
            tree[i/2] += tree[i];
    }
    int query(int l, int r) { return _query(1,l,r,0,tree.size()/2-1); }
    int _query(int ind, int l, int r, int bl, int br) {
        if (l > r) return 0;
        if (l == bl && r == br) return tree[ind];
        int m = (bl + br) / 2;
        return _query(ind*2, l, min(m,r), bl, m) + 
            _query(ind*2 + 1, max(m+1,l), r, m+1, br);
    }
    void update(int ind, int val) {
        ind = ind + tree.size() / 2;
        int diff = val - tree[ind];
        for (; ind > 0; ind /= 2) tree[ind] += diff;
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> vals(6);
    for (int i = 0; i < 6; i++) cin >> vals[i];
    vector<int> types(n);
    vector<vector<int>> gems(6, vector<int>(n));
    for (int i = 0; i < n; i++) {
        char gem; cin >> gem;
        types[i] = gem-'1';
        for (int j = 0; j < 6; j++) {
            gems[j][i] = (gem-'1' == j) ? 1 : 0;
        }
    }

    vector<SegTree> trees;
    for (int i = 0; i < 6; i++) {
        trees.push_back(SegTree(gems[i]));
    }

    while (q--) {
        int code; cin >> code;
        if (code == 1) {
            int k, p;
            cin >> k >> p;
            trees[types[k-1]].update(k-1,0);
            trees[p-1].update(k-1,1);
            types[k-1] = p-1;
        } else if (code == 2) {
            int p, v;
            cin >> p >> v;
            vals[p-1] = v;
        } else {
            int l, r;
            cin >> l >> r;
            long long tot = 0;
            for (int i = 0; i < 6; i++) {
                tot += trees[i].query(l-1, r-1) * (long long) vals[i];
            }
            cout << tot << "\n";
        }
    }
}