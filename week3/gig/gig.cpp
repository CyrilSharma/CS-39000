#include <bits/stdc++.h>
using namespace std;

int main() {
    using ll = long long;
    ll mod = (ll) 1e9+7;

    int n; cin >> n;
    int ones, tone = 0;
    ll combos, prev, tot, totinv, best;
    combos = 1; prev = 1; totinv = 0; best = 0; tot = 0;
    while (n--) {
        int h; cin >> h;
        if (h == 1) {
            ones++; tone++;
            tot = (tot + prev) % mod;
            combos = 1;
        }
        if (h == 2) {
            combos = (combos * 2) % mod;
            prev = (combos * prev) % mod; 
            ones = 0;
        }
        if (h == 3) {
            totinv = (tone + totinv) % mod;
            best = tot;
            ones = 0;
        }
    }
    // why is this so complex.
    cout << "tot: " << tot << "\n";
    cout << "combos: " << combos << "\n";
    cout << "prev: " << prev << "\n";
    cout << "totinv: " << totinv << "\n";
    ll ans = (best - totinv + mod) % mod;
    cout << ans << "\n";
}