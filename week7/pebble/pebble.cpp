/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Brute Force with Caching
 * Scan the line of pebbles, and try every valid move.
 * States are passed using 23 bits in an integer.
 * Simply remember previous calls, and that's sufficient to pass
 * As there are only 2^23 states.
 * @date 2022-10-21
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int w = 23;
    vector<int> dp(1<<23, 2e9);
    function<int(int)> calc;
    calc = [&](int num) {
        if (dp[num] != 2e9) return dp[num];
        int nbits = 0;
        for (int i = 0; i < w; i++) {
            int b1, b2, b3;
            b2 = (num & (1 << i)) >> i;
            nbits += b2;

            if (i == 0 || i == w-1) continue;
            b1 = (num & (1 << (i-1))) >> (i-1);
            b3 = (num & (1 << (i+1))) >> (i+1);
            // legality conditions
            if (b2 == 0) continue;
            if (b1 == b3) continue;
            // turn off middle bit and toggle appropriate bits.
            int nnum = num & ~(1 << i);
            nnum ^= (1 << (i-1));
            nnum ^= (1 << (i+1));
            dp[num] = min(dp[num], calc(nnum)); 
        }
        return dp[num] = min(nbits, dp[num]);
    };

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int state = 0;
        for (int j = 0; j < 23; j++) {
            char c; cin >> c;
            if (c == 'o') state |= 1 << j;
        }
        cout << calc(state) << "\n";
    }
}