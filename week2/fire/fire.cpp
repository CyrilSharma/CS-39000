#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool outOfBounds(int x, int y, int w, int h) {
    if (x < 0 || x > w-1 || y < 0 || y > h-1) return true;
    return false;
}

bool onBoundary(int x, int y, int w, int h) {
    if (x == 0 || x == w-1 || y == 0 || y == h-1) return true;
    return false;
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
        queue<pair<int, int>> q;
        vector<vector<int>> dist(h, vector<int>(w));
        vector<vector<int>> queued(h, vector<int>(w));
        vector<vector<int>> fireMap(h, vector<int>(w));
        dist[start.first][start.second] = 0;
        queued[start.first][start.second] = 1;
        q.push(start);

        pair<int, int> pos;
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        int x, y, fireCounter;
        bool solFound = false;
        fireCounter = 0;
        // potentially slow if that path is long, because there's an N^2 update each iteration of the BFS...
        // how can you find a path to an exit that fire doesn't block, without simulation? Fire travels in the same way
        // simulate in from an exit, see if you hit fire first or the player.
        // the issue here is that you could potentially end up simulating from every exit, which could be quite expensive.
        // iterate over exits.
        // first, run BFS on entire map, find all the closest exits.
        // then, run BFS from each exit, seeing if you find the player or the fire first. 
        // if you find the fire first, the exit doesn't work, if you find the player, then you're CHILLING. return the dist.
        while (q.size() != 0) {
            pos = q.front(); q.pop();
            if (onBoundary(pos.second, pos.first, w, h)) {
                cout << dist[pos.first][pos.second]+1 << "\n";
                solFound = true;
                break;
            }

            // when we've exhausted all places reachable in time t, simulate another step.
            if (dist[pos.first][pos.second] > fireCounter) {
                fireCounter++;
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j++) {
                        if (map[i][j] != '*') continue;
                        for (int k = 0; k < 4; k++) {
                            x = j + dx[k]; y = i + dy[k];
                            if (outOfBounds(x,y,w,h)) continue;
                            if (map[y][x] == '.' || map[y][x] == '@') {
                                fireMap[y][x] = 1;
                            }
                        }
                    }
                }
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j++) {
                        if (fireMap[i][j]) map[i][j] = '*';
                    }
                }
            }

            for (int i = 0; i < 4; i++) {
                x = pos.second + dx[i]; y = pos.first + dy[i];
                if (outOfBounds(x, y, w, h)) continue;
                if (map[y][x] == '#' || map[y][x] == '*') continue;
                if (!queued[y][x]) {
                    q.push(make_pair(y, x));
                    dist[y][x] = dist[pos.first][pos.second] + 1;
                    queued[y][x] = 1;
                }
            }
        }   
        if (!solFound) cout << "IMPOSSIBLE\n";
    }
}