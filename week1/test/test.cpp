#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    int M = 1e2;
    // allows for initialization of a vector of zeros?
    vector<vector<int>> cost(M, vector<int>(M));
    cout << cost[0][3] << "\n";
}