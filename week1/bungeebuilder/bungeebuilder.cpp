#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 1000000
#define maxVal 2000000000

int N;
pair<int, int> vals[maxN];
int tree[maxN * 3];

void build() {
    // calculate nearest power of 2.
    int temp = 1;
    int temp1 = N;
    int num2s = 0;
    while (temp1 != 0) {
        temp1 /= 2;
        temp *= 2;
        num2s++;
    }

    int count = 0;
    for (int i = temp - 1; i < (2 * temp) - 1; i++) {
        if (count < N) tree[i] = vals[count].first;
        else tree[i] = maxVal;
        count++;
    }

    for (int i = temp - 2; i >= 0; i--) {
        tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
    }
}

int _query(int node, int l, int r, int bl, int br) {
    // if there is only one item in the bound, return it.
    if (bl == br) return tree[node];
    int bm = (bl + br) / 2;
    // if the bounds fit perfectly, return the element.
    if (bl == l && br == r) return tree[node];
    // if the query fits in the left child...
    if (r <= bm && l >= bl) return _query(2 * node + 1, l, r, bl, bm);
    // query fits in the right child
    if (l >= bm + 1 && r <= br) return _query(2 * node + 2, l, r, bm+1, br);
    // query requires both children.
    return min(_query(2 * node + 1, l, bm, bl, bm), _query(2 * node + 2, bm+1, r, bm+1, br));
}

int query(int l, int r) {
    return _query(0, l, r, 0, N);
}

int main() {
    scanf("%d\n", &N);
    int cur;
    for (int i = 0; i < N; i++) {
        scanf("%d\n", &cur);
        vals[i] = make_pair(cur, i);
    }   
    build();
    sort(vals, vals + N);
    // need an O(nlog(n)) way to iterate through all possible bridge combinations.
    // instead of sort, iterate through the array, and connect br with bl, where bl is the nearest thing larger 
    // then br. do it for the other connection too.
    // you need a quick way to find the closest, smallest, largest element, just a BST, will be O(log(n)).
    int maxDrop = -1;
    int height, l, r;
    for (int i = 1; i < N; i++) {
        height = min(vals[i].first, vals[i-1].first);
        l = min(vals[i].second, vals[i-1].second);
        r = max(vals[i].second, vals[i-1].second);
        maxDrop = max(maxDrop, height - query(l, r));
    }
    cout << maxDrop << "\n";
}