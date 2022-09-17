#include <vector>
#include <iostream>
#include <math.h>
#include <functional>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> dp(n+1, 0);
    for (int i = 1; i <= n; i++) {
        dp[i] = i;
    }

    function<int(string)> process;
    process = [&](string t) {
        if (t.size() == 0) return 0;
        int best = dp[stoi(t)];
        for (int i = 0; i < t.size()-1; i++) {
            int l = stoi(t.substr(0, i+1));
            int r = stoi(t.substr(i+1));
            if (t.substr(i+1)[0] == '0') continue;
            else best = min(best, dp[l] + dp[r]);
        }
        return best;
    };

    for (int its = 0; its < 50; its++) {
        // multiplication
        for (int i = 1; i <= n; i++) {
            for (int f1 = 1; f1 <= sqrt((double)i); f1++) {
                if (i % f1 == 0) {
                    int f2 = i / f1;
                    dp[i] = min(dp[i], dp[f1] + dp[f2]);
                }
            }
        }

        // concactenation.
        for (int i = 1; i <= n; i++) {
            dp[i] = min(dp[i], process(to_string(i)));
        }

        /* // addition
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                dp[i] = min(dp[i], dp[i-j] + dp[j]);
            }
        } */
        // you could do this with DP, or you could just use djikstras.
    }
    // for (int i = 0; i <= n; i++) cout << i << ": " << dp[i] << " "; cout << "\n";
    // alternate approach. what number can i make using only X ones?

    cout << dp[n] << "\n";
}