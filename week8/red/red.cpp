#include <bits/stdc++.h>
using namespace std;
int main() {
    int a;
    while (cin >> a) {
        if (a == 4) break;
        for (int iters = 1; ; iters++) {
            int num = a;
            int sum = 0;
            for (int div = 2; div * div <= a; div++) {
                if (a % div != 0) continue;
                while (a % div == 0) {
                    a /= div;
                    sum += div;
                }
            }
            // if num was prime...
            if (sum == 0) {
                cout << num << " " << iters << '\n';
                break;
            }
            if (a > 1) sum += a;
            a = sum;
        }
    }
}