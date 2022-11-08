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
    void update(int ind) {
        ind = ind + tree.size() / 2;
        int diff = !tree[ind] - tree[ind];
        for (; ind > 0; ind /= 2) tree[ind] += diff;
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    SegTree tree = SegTree(vector<int>(n));
    while (k--) {
        char c; cin >> c;
        if (c == 'C') {
            int l, r;
            cin >> l >> r;
            cout << tree.query(l, r) << "\n";
        } else if (c == 'F') {
            int b; cin >> b;
            tree.update(b);
        }
    }
}