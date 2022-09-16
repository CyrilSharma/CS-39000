// Author: Cyril Sharma
// It is ok to post my anonymized solution

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct story { int w,h,x,y; };
typedef vector<story> vs;
typedef vector<int> vi;

bool overlaps(story a, story b) {
    // right boundary of left object
    int r = min(a.x + a.w, b.x + b.w);
    // left boundary of right object
    int l = max(a.x, b.x);
    int t = min(a.y + a.h, b.y + b.h);
    int bo = max(a.y, b.y);

    // if right boundary of left object is past left boundary of right object
    // then there is overlap.
    if (r > l && t > bo) return true;
    return false;
}

int n;
int dfs(int prev, int area, vi exclude, vs stories) {
    int narea = area;
    // find the maximum area from the remaining possibilities.
    // start at prev+1 so that you don't use identical combinations (a, b) vs (b, a)
    for (int i = prev+1; i < n; i++) {
        if (exclude[i]) continue;
        // represents indexes that cannot be chosen
        // if there is overlap, or if you have already chosen the index,
        // mark the index as unuseable.
        vi nexclude(n);
        for (int j = 0; j < n; j++) {
            nexclude[j] = exclude[j];
            if (overlaps(stories[i], stories[j])) 
                nexclude[j] = 1;
        }
        nexclude[i] = 1;
        int sarea = stories[i].w * stories[i].h;
        narea = max(narea, dfs(i, area + sarea, nexclude, stories));
    }
    return narea;
}

int main() {
    cin >> n;
    while (n != 0) {
        vi exclude(n); vs stories(n);
        for (int i = 0; i < n; i++) {
            story s;
            cin >> s.w >> s.h >> s.x >> s.y;
            stories[i] = s;
        }
        cout << dfs(-1, 0, exclude, stories) << "\n";
        cin >> n;
    }
}