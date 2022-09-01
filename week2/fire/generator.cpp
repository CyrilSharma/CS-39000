#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    FILE* fout = fopen("sample.txt", "w");
    int num = stoi(argv[1]);
    fprintf(fout, "%d\n", 1);
    fprintf(fout, "%d %d\n", num, num);
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == num/2 && j == num/2) fprintf(fout, "%c", '@');
            else fprintf(fout, "%c", '.');
        }
        fprintf(fout, "%c", '\n');
    }
}