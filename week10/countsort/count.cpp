#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> nums(n);
    for (int i = 1; i <= n; i++) nums[i-1] = i;
    auto rng = default_random_engine {};
    shuffle(nums.begin(), nums.end(), rng);

    int nbits = 8;
    int comp = (1 << nbits) - 1;
    int width = (1 << nbits);
    vector<vector<int>> buckets(width);
    for (int j = 0; j < n; j++) {
        buckets[nums[j] & comp].push_back(nums[j]);
    }

    vector<vector<int>> nbuckets(width);
    for (int i = 1; i < 32 / nbits; i++) {
        for (int j = 0; j < width; j++) {
            for (auto num: buckets[j]) {
                nbuckets[(num >> (nbits * i)) & comp].push_back(num);
            }
        }
        buckets = nbuckets;
        nbuckets = vector<vector<int>>(width);
    }
}