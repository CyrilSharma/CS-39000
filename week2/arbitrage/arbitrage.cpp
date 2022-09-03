#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

#define maxVal 1e200

int main() {
    while (true) {
        int C; cin >> C;
        if (C == 0) break;
        char temp[4];
        map<string, int> m;
        for (int i = 0; i < C; i++) {
            scanf("%s", temp);
            m[temp] = i;
        }

        int R; cin >> R;
        char c1[4], c2[4]; int d1, d2;
        vector<vector<double>> graph(C, vector<double>(C, maxVal));
        for (int i = 0; i < R; i++) {
            scanf("%s %s %d:%d", c1, c2, &d1, &d2);
            graph[m[c1]][m[c2]] = -log((double) d2 / (double) d1);
        }

        vector<double> dist(C, maxVal);
        dist[0] = 0.0;
        for (int i = 0; i < C-1; i++) {
            for (int j = 0; j < C; j++) {
                for (int k = 0; k < C; k++) {
                    if (dist[j] + graph[j][k] < dist[k]) {
                        dist[k] = dist[j] + graph[j][k];
                    }
                }
            }
        }
        
        bool arbitrage = false;
        for (int j = 0; j < C; j++) {
            for (int k = 0; k < graph[j].size(); k++) {
                if (dist[j] != maxVal && dist[j] + graph[j][k] < dist[k]) {
                    arbitrage = true;
                    break;
                }
            }
            if (arbitrage) break;
        }

        if (!arbitrage) cout << "Ok\n";
        else cout << "Arbitrage\n";
    }
}