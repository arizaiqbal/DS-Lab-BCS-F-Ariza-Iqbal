#include <iostream>
#include <cstring>
using namespace std;

int* rabinKarp(char text[], char pat[], int &count, int &falsePositives) {
    const int prime = 101;
    int n = strlen(text);
    int m = strlen(pat);
    count = 0;
    falsePositives = 0;

    int* result = new int[n];

    long long h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * 256) % prime;

    long long patHash = 0, txtHash = 0;

    for (int i = 0; i < m; i++) {
        patHash = (patHash * 256 + pat[i]) % prime;
        txtHash = (txtHash * 256 + text[i]) % prime;
    }

    for (int i = 0; i <= n - m; i++) {

        if (patHash == txtHash) {
            bool ok = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pat[j]) {
                    ok = false;
                    falsePositives++;
                    break;
                }
            }
            if (ok) result[count++] = i;
        }

        if (i < n - m) {
            txtHash = (256 * (txtHash - text[i] * h) + text[i + m]) % prime;
            if (txtHash < 0) txtHash += prime;
        }
    }
    return result;
}

int main() {
    char text[] = "Data structures and algorithms are fun. Algorithms make tasks easier.";
    char pattern[] = "Algorithms";

    int count, fp;
    int* pos = rabinKarp(text, pattern, count, fp);

    cout << "Matches at: ";
    for (int i = 0; i < count; i++)
        cout << pos[i] << " ";
    cout << "\nFalse Positives: " << fp;

    delete[] pos;
    return 0;
}
