#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    FILE* fout = fopen("sample.txt", "w");
    int num = stoi(argv[1]);
    fprintf(fout, "%d\n", num);
    fprintf(fout, "%d", 53);
    for (int i = 0; i < num; i++) {
        if (i == num / 2) fprintf(fout, " %d", 0);
        else fprintf(fout, " %d", 53);
    }
}