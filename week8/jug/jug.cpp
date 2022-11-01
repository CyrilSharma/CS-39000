#include <bits/stdc++.h>
using namespace std;

using triple = tuple<int,int,int>;
triple euclid(int a, int b, int x, int y) {
    if (b == 0) return {a, 1, 0};
    auto [d, x1, y1] = euclid(b, a%b, x, y);
    int nx = y1;
    int ny = x1 - y1 * a / b;
    return {d, nx, ny};
}

int main() {
    int t; cin >> t;
    while (t--) {
        int a,b,d;
        cin >> a >> b >> d;
        auto [g, x, y] = euclid(a, b, 0, 0);
        if (d % g == 0 || d % a == 0 || d % b == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}