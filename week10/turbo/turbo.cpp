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
    int n; cin >> n;
    vector<pair<int,int>> nums(n);
    for (int i = 0; i < n; i++) {
        int num; cin >> num;
        nums[i] = {num,i};
    }
    vector<SegTree> trees(2, SegTree(vector<int>(n)));
    sort(nums.begin(), nums.end());
    int l = 0;
    int r = n - 1;
    int cur = 0;
    for (int count = 0; count < n; count++) {
        auto [val, old] = nums[cur];
        if (old > cur) {
            int diff1 = trees[1].query(0, old);
            int diff2 = trees[0].query(old, n-1);
            cout << abs((old - cur) - diff1 + diff2) << "\n";
        } else {
            int diff1 = trees[0].query(old, n-1);
            int diff2 = trees[1].query(0, old);
            cout << abs((cur - old) - diff1 + diff2) << "\n";
        }

        if (count % 2 == 0) {
            cur = r; l++; 
            trees[0].update(old, 1);
        } else { 
            cur = l; r--;
            trees[1].update(old, 1);
        }
    }
}