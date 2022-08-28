#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define maxVal 10000000

int n, t;
int b[16];
int dp[3601];

// SO. How do I account for the values being negative.
void calc() {
    for (int i = 0; i < 3601; i++) dp[i] = maxVal;
    dp[0] = 0;

    int i = 0;
    int end = 0;
    // standard dp stuff
    for (; i < n; i++) {
        if (b[i] < 0) break;
        if (b[i] == 0) continue;
        for (int j = b[i]; j < 3601; j++) {
            dp[j] = min(dp[j - b[i]] + 1, dp[j]);
        }
        // 1hr is always reachable;
        end = 3600 / b[i];
        end += (3600 % b[i] == 0) ? 0 : 1;
        dp[3600] = min(end, dp[3600]);
    }

    // he somehow got very quick runtime...
    // you can figure out all numbers attainable under a limit, figure out associate number of presses and bounds,

    // improve minimum button presses with negative numbers.
    for (; i < n; i++) {
        for (int j = 3600; j >= -b[i]; j--) {
            dp[j + b[i]] = min(dp[j] + 1, dp[j + b[i]]);
        }
    }

    for (int j = t; j < 3601; j++) {
        if (dp[j] != maxVal) {
            cout << dp[j] << " " << j - t << "\n";
            return;
        }
    }
    return;
}

int main() {
    int numTests;
    scanf("%d\n", &numTests);
    for (int i = 0; i < numTests; i++) {
        scanf("%d %d", &n, &t);
        for (int k = 0; k < n; k++) {
            scanf("%d", &b[k]);
        }
        sort(b, b + n, greater<int>());
        // rewrite with djikstras...
        calc();
    }
}