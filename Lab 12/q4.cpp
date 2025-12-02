#include <iostream>
#include <cstring>
using namespace std;

void buildLPS(char pat[], int m, int lps[]) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
    }
}

int* KMP(char text[], char pat[], int &count, int* &lpsOut) {
    int n = strlen(text);
    int m = strlen(pat);

    count = 0;
    int* result = new int[n];

    int* lps = new int[m];
    buildLPS(pat, m, lps);
    lpsOut = lps;

    int i = 0, j = 0;

    while (i < n) {
        if (text[i] == pat[j]) {
            i++; j++;
        }

        if (j == m) {
            result[count++] = i - j;
            j = lps[j - 1];
        } 
        else if (i < n && text[i] != pat[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return result;
}

int main() {
    char text[] = "ababababc";
    char pat[] = "abab";

    int count;
    int* lpsArray;
    int* pos = KMP(text, pat, count, lpsArray);

    cout << "Matches at: ";
    for (int i = 0; i < count; i++)
        cout << pos[i] << " ";

    cout << "\nLPS Array: ";
    for (int i = 0; i < strlen(pat); i++)
        cout << lpsArray[i] << " ";

    delete[] pos;
    delete[] lpsArray;
    return 0;
}
