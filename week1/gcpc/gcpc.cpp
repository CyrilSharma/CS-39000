#include <iostream>
#include <fstream>
#include <set>

using namespace std;

#define maxTeams 100001

int solves[maxTeams];
int penalties[maxTeams];

bool compare(pair<int, int> left, pair<int, int> right) {
    if (left.first != right.first) return left.first < right.first;
    else {
        return left.second > right.second;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    bool (*fptr)(pair<int, int>, pair<int, int>) = compare;

    multiset<pair<int, int>, bool(*)(pair<int, int>, pair<int, int>) > st (fptr);
    multiset<pair<int, int>, bool(*)(pair<int, int>, pair<int, int>) > gt (fptr);

    int t, p;
    int comp;
    int numSame = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &t, &p);
        comp = compare(make_pair(solves[1], penalties[1]), make_pair(solves[t], penalties[t]));
        if (comp) {
            auto it = gt.find(make_pair(solves[t], penalties[t]));
            if (it != gt.end()) gt.erase(it);
        }
        else {
            auto it = st.find(make_pair(solves[t], penalties[t]));
            if (it != st.end()) st.erase(it);
        }
        solves[t]++;
        penalties[t] += p;

        comp = compare(make_pair(solves[1], penalties[1]), make_pair(solves[t], penalties[t]));
        if (comp) gt.insert(make_pair(solves[t], penalties[t]));
        else st.insert(make_pair(solves[t], penalties[t]));
        
        if (t == 1) {
            while (gt.size() != 0 && (compare(*gt.begin(), make_pair(solves[1], penalties[1])) ||
            (gt.begin()->first == solves[1] && gt.begin()->second == penalties[1]))) {
                st.insert(*gt.begin());
                gt.erase(gt.begin());
            }
        }
        cout << gt.size() + 1 << "\n";
    }
}