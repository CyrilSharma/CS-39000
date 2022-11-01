#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    int ttwos = 0;
    int tfives = 0;
    long long num = 1;
    for (int i = 1; i <= n; i++) {
        int a = i;
        for (; a % 2 == 0; a/=2) 
            ttwos = ttwos + 1;
        for (; a % 5 == 0; a/=5) 
            tfives = tfives + 1;
        num = (num * a) % 1000; 
    }
    for (int i = 0; i < ttwos-tfives; i++) {
        num = (num * 2) % 1000;
    }
    stringstream ss;
    ss << setw(3) << setfill('0') << num;
    if (n < 7) cout << num << "\n";
    else cout << ss.str() << "\n";
}