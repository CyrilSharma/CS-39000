#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define maxN 1000000
#define maxVal 2000000000

int N, T;
int vals[maxN];
int tree[maxN * 3];

void build() {
    // calculate nearest power of 2.
    int temp;
    T = 1; temp = N;
    while (temp != 0) {
        temp /= 2;
        T *= 2;
    }

    int count = 0;
    for (int i = T - 1; i < (2 * T) - 1; i++) {
        if (count < N) tree[i] = vals[count];
        else tree[i] = maxVal;
        count++;
    }

    for (int i = T - 2; i >= 0; i--) {
        tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
    }
}

int _query(int node, int l, int r, int bl, int br) {
    if (bl == br) return tree[node];
    if (bl == l && br == r) return tree[node];
    int bm = (bl + br) / 2;
    if (r <= bm && l >= bl) return _query(2 * node + 1, l, r, bl, bm);
    if (l >= bm + 1 && r <= br) return _query(2 * node + 2, l, r, bm+1, br);
    return min(_query(2 * node + 1, l, bm, bl, bm), _query(2 * node + 2, bm+1, r, bm+1, br));
}

int query(int l, int r) {
    if (l == r) return vals[l];
    if (l > r) return maxVal;
    return _query(0, l, r, 0, T-1);
}

int main() {
    scanf("%d\n", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d\n", &vals[i]);
    }   
    build();

    map<int, int> maxes;
    int maxDrop = 0;
    int height, bl, br;

    maxes[vals[0]] = 0;
    for (int i = 1; i < N; i++) {
        auto it = maxes.upper_bound(vals[i]);
        if (it != maxes.end()) {
            bl = it->second;
            if ((i - bl) > 1) {
                height = vals[i];
                maxDrop = max(maxDrop, height - query(bl, i));
            }
        }
        if (it != maxes.begin()) {
            it--;
            bl = it->second;
            if ((i - bl) > 1) {
                height = vals[bl];
                maxDrop = max(maxDrop, height - query(bl, i));
            }
        }
        maxes.erase(maxes.begin(), it);
        maxes[vals[i]] = i;
    }
    cout << maxDrop << "\n";
}