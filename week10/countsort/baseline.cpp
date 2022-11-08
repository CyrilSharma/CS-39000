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
    
    for (int i = 0; i < n; i++) cin >> nums[i];
    sort(nums.begin(), nums.end());
}