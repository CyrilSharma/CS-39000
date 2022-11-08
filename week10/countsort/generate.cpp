#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> nums(n);
    for (int i = 1; i <= n; i++) nums[i-1] = i;
    auto rng = default_random_engine {};
    shuffle(nums.begin(), nums.end(), rng);
    cout << n << "\n";
    for (auto num: nums) cout << num << "\n";
}