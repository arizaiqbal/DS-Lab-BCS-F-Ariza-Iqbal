#include <iostream>
#include <cstring>
using namespace std;

void buildBadChar(char pat[], int m, int bad[]) {
    for (int i = 0; i < 256; i++) bad[i] = -1;
    for (int i = 0; i < m; i++)
        bad[(unsigned char)pat[i]] = i;
}

void buildGoodSuffix(int* shift, int* borderPos, char pat[], int m) {
    int i = m, j = m + 1;
    borderPos[i] = j;

    while (i > 0) {
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            if (shift[j] == 0) shift[j] = j - i;
            j = borderPos[j];
        }
        i--; j--;
        borderPos[i] = j;
    }

    j = borderPos[0];
    for (i = 0; i <= m; i++) {
        if (shift[i] == 0) shift[i] = j;
        if (i == j) j = borderPos[j];
    }
}

int* boyerMoore(char text[], char pat[], int &count) {
    int n = strlen(text);
    int m = strlen(pat);

    count = 0;
    int* result = new int[n];

    int bad[256];
    buildBadChar(pat, m, bad);

    int* shift = new int[m + 1];
    int* borderPos = new int[m + 1];
    for (int i = 0; i <= m; i++) shift[i] = 0;

    buildGoodSuffix(shift, borderPos, pat, m);

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pat[j] == text[s + j]) j--;

        if (j < 0) {
            result[count++] = s;
            s += shift[0];
        } else {
            int badMove = j - bad[(unsigned char)text[s + j]];
            int goodMove = shift[j + 1];
            s += (badMove > goodMove ? badMove : goodMove);
        }
    }
    delete[] shift;
    delete[] borderPos;

    return result;
}

int main() {
    char dna[] = "ACGTACGTGACG";
    char pat[] = "ACG";

    int count;
    int* pos = boyerMoore(dna, pat, count);

    cout << "Pattern found at: ";
    for (int i = 0; i < count; i++)
        cout << pos[i] << " ";

    delete[] pos;
    return 0;
}
