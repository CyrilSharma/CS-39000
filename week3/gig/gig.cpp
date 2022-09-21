#include <vector>
#include <iostream>
#include <math.h>
#include <functional>

using namespace std;
using ll = long long;

ll mod = (ll) 1e9+7;
ll modExp(int p) {
    ll ans = 1; 
    while (p--) {
        ans *= 2;
        ans %= mod;
    }
    return ans;
}

// You may be doing this in a really stupid way.
int main() {
    int n; cin >> n;
    vector<int> vals(n, 0);
    vector<int> twos(n, 0);

    ll dtot, dinv;
    ll ndtot, ndinv;
    ll tot = 0; ll inv = 0;
    int prev = -1; int ttwo = 0; int fone = -1;
    for (int i = 0; i < n; i++) {
        int h; cin >> h;
        vals[i] = h;
        twos[i] = ttwo;
        switch (h) {
            case 1:
                if (vals[fone] != 1) fone = i;
                break;
            case 2: 
                ttwo++;
                break;
            case 3:
                ndtot = 0; ndinv = 0;
                if (prev != -1) {
                    int dtwos = twos[i] - twos[prev];
                    ll combos = modExp(dtwos);
                    if (dtot != -1 && dinv != -1) {
                        // all possibilities
                        ndtot += dtot * combos;
                        ndinv += dinv;
                        ndtot %= mod;
                        ndinv %= mod;
                    }
                }
                prev = i;

                if (fone == -1) continue;
                int dtwos = -1;
                while (dtwos != 0 && fone < i) {
                    if (vals[fone] == 1) {
                        dtwos = twos[i] - twos[fone];
                        ndtot += modExp(dtwos);
                        ndinv += 1;
                        ndtot %= mod;
                        ndinv %= mod;
                    }
                    fone++;
                }
                if (ndtot != dtot) dtot = ndtot;
                if (ndinv != dinv) dinv = ndinv;
                tot = (tot + dtot) % mod;
                inv = (inv + dinv) % mod;
        }
    }
    ll ans = (tot - inv + mod) % mod;
    cout << ans << "\n";
}