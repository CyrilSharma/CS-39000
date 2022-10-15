#include <bits/stdc++.h>
using namespace std;
int main() {
    int w = 23;
    vector<int> dp(1<<23, 2e9);
    function<void(int,int,int,int)> calc;
    calc = [&](int b, int d, int l, int num) {
        if (d == b) {
            return;
            dp[num] = b;
            for (int i = 1; i < w-1; i++) {
                int b1, b2, b3;
                b1 = (num & (1 << (i-1))) >> (i-1);
                b2 = (num & (1 << i)) >> i;
                b3 = (num & (1 << (i+1))) >> (i+1);
                // legality conditions
                if (b2 == 0) continue;
                if (b1 == b3) continue;
                // turn off middle bit and toggle appropriate bits.
                int nnum = num & ~(1 << i);
                nnum ^= (1 << (i-1));
                nnum ^= (1 << (i+1));
                dp[num] = min(dp[num], dp[nnum]); 
            }
            return;
        }
        // turn on bits until there are b bits on.
        for (int i = l; i < w; i++) {
            calc(b, d+1, i+1, num | 1 << i);
        }
    };
    for (int b = 1; b <= w; b++) {
        calc(b, 0, 0, 0);
    }

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int state = 0;
        for (int j = 0; j < 23; j++) {
            char c; cin >> c;
            if (c == 'o') state |= 1 << j;
        }
        cout << state << " " << dp[state] << "\n";
    }
}