#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define maxDist 1000000000

bool outOfBounds(int x, int y, int w, int h) {
    return (x < 0 || x > w-1 || y < 0 || y > h-1);
}

bool onBoundary(int x, int y, int w, int h) {
    return (x == 0 || x == w-1 || y == 0 || y == h-1);
}

int main() {
    int numTests;
    cin >> numTests;
    for (int t = 0; t < numTests; t++) {
        int w, h;
        cin >> w >> h;

        pair<int, int> start;
        vector<vector<char>> map(h, vector<char>(w));
        char line[w];
        for (int i = 0; i < h; i++) {
            scanf("%s\n", line);
            for (int j = 0; j < w; j++) {
                if (line[j] == '@') start = make_pair(i, j);
                map[i][j] = line[j];
            }
        }

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        queue<pair<int, int>> fq;
        vector<vector<int>> fdist(h, vector<int>(w, maxDist));
        // run BFS for all fire tiles.
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (map[i][j] == '*') {
                    fq.push(make_pair(i, j));
                    fdist[i][j] = 0;
                }
            }
        }

        pair<int, int> pos;
        while (fq.size() != 0) {
            pos = fq.front(); fq.pop();
            for (int i = 0; i < 4; i++) {
                int x = pos.second + dx[i]; int y = pos.first + dy[i];
                if (outOfBounds(x, y, w, h)) continue;
                if (map[y][x] == '#' || map[y][x] == '*') continue;
                if (fdist[y][x] <= fdist[pos.first][pos.second] + 1) continue;
                else {
                    fq.push(make_pair(y, x));
                    fdist[y][x] = fdist[pos.first][pos.second] + 1;
                }
            }
        }

        bool solFound = false;
        queue<pair<int, int>> q;
        vector<vector<int>> dist(h, vector<int>(w, maxDist));
        dist[start.first][start.second] = 0;
        q.push(start);
        while (q.size() != 0) {
            pos = q.front(); q.pop();
            if (onBoundary(pos.second, pos.first, w, h)) {
                solFound = true;
                cout << dist[pos.first][pos.second] + 1 << "\n";
                break;
            }
            for (int i = 0; i < 4; i++) {
                int x = pos.second + dx[i]; int y = pos.first + dy[i];
                if (outOfBounds(x, y, w, h)) continue;
                if (map[y][x] == '#') continue;
                if (dist[pos.first][pos.second] + 1 >= fdist[y][x]) continue;
                if (dist[y][x] == maxDist) {
                    q.push(make_pair(y, x));
                    dist[y][x] = dist[pos.first][pos.second] + 1;
                }
            }
        }
        if (!solFound) cout << "IMPOSSIBLE\n";
    }
}