#include <vector>
#include <iostream>
#include <math.h>
#include <functional>

using namespace std;

int modExp(int p) {
    int ans = 1; 
    while (p != 0) {
        ans *= 2;
        ans %= (int) (1e9 + 7);
        p--;
    }
    return ans;
}

int main() {
    int n; cin >> n;
    vector<int> vals(n, 0);
    vector<int> twos(n, 0);

    using ll = long long;
    ll prevTot = 0; int prev = -1;
    int ttwo = 0; int fone = -1;
    for (int i = 0; i < n; i++) {
        int h; cin >> h;
        vals[i] = h;
        twos[i] = ttwo;
        if (h == 2) ttwo++;
        else if (h == 3) {
            if (prev != -1) {
                int dtwos = twos[i] - twos[prev];
                int combos = modExp(dtwos);
                // double counts :((
                prevTot = prevTot + prevTot * combos;
                prevTot %= (int) (1e9 + 7);
            }
            prev = i;

            if (fone == -1) continue;
            int dtwos = twos[i] - twos[fone];
            while (dtwos != 0 && fone < i) {
                if (vals[fone] == 1) {
                    prevTot += modExp(dtwos) - 1;
                    dtwos = twos[i] - twos[fone];
                }
                fone++;
            }
        }
        else if (h == 1) {
            if (vals[fone] != 1) fone = i;
        }
        cout << "prevTot: " << prevTot << "\n";
    }
    cout << prevTot << "\n";
}