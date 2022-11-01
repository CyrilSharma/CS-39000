/**
 * @author Cyril Sharma
 * @note It is ok to post my anonymized solution.
 * @brief Modulo Tricks.
 * Two key observations:
 * 1. In order for a subsequence to be divisible by d, it must add to 0 %d.
 * 2. If I start at some value a, go k elements, and then arrive back at a, I've discovered a subsequence!
 * From here, just compute the sum from 0 to element n %d.
 * Store the sum values in an array. Any subsequence that starts and ends at the same module value is valid.
 * Thus, add w choose 2 (where w is the number of elements with modulo i) for each element in the sums array.
 * @date 2022-10-21
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int c; cin >> c;
    while (c--) {
        int d, n;
        cin >> d >> n;
        vector<int> counts(d,0);
        counts[0] = 1;
        using ll = long long;
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            int a; cin >> a;
            sum = (sum + a) % d;
            counts[sum]++;
        }

        ll total = 0;
        for (int i = 0; i < d; i++) {
            if (counts[i] <= 1) continue;
            total += (counts[i]) * (counts[i]-1) / 2;
        }
        cout << total << "\n";
    }
}