#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int N;
    scanf("%d\n", &N);

    int cur;
    int bestDrop = -1;
    int tall, bl, br;
    int small, sb;
    tall = bl = br = -1;
    small = sb = 2147483647;
    for (int i = 0; i < N; i++) {
        scanf("%d\n", &cur);
        small = min(cur, small);
        if (cur >= tall) {
            bestDrop = max(bestDrop, tall - small);
            tall = cur;
            small = cur;

            bl = -1;
            br = -1;
            sb = cur;
        }
        if (cur == bl) {
            bestDrop = max(bestDrop, secondTallest - smallest);
            secondTallest = -1;
        }
        else {
            secondTallest = max(secondTallest, cur);
        }
    }
    bestDrop = max(secondTallest - smallest, bestDrop);
    if (bestDrop > 0) cout << bestDrop << "\n";
    else cout << 0 << "\n";
}