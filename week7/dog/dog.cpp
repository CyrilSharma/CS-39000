/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Standard DP
 * Use DP to figure out what amounts are creatable using packs of hotdogs and buns.
 * Then, find the minimum value that is craftable with both hotdogs and buns.
 * @date 2022-10-21
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    function<vector<int>()> calc;
    calc = [&]() {
        int n; cin >> n;
        int max = n*1000+1;
        vector<int> dp(max, 2e9); dp[0] = 0;
        for (int i = 0; i < n; i++) {
            int val; cin >> val;
            for (int j = max-1; j >= 0; j--) {
                if (j + val < max) {
                    dp[j+val] = min(dp[j+val], dp[j]+1);
                }
            }
        }
        return dp;
    };

    vector<int> dogs = calc();
    vector<int> buns = calc();
    int best = 2e9;
    for (int i = 1; i < max(dogs.size(),buns.size()); i++) {
        if (dogs[i] != 2e9 && buns[i] != 2e9) {
            best = min(best, dogs[i]+buns[i]);
        }
    }
    if (best != 2e9) cout << best << "\n";
    else cout << "impossible\n";
}