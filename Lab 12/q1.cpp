#include <iostream>
#include <cstring>
using namespace std;

int* bruteForceSearch(char text[], char pat[], int &count, int &compCount) {
    int n = strlen(text);
    int m = strlen(pat);
    count = 0;
    compCount = 0;

    int* result = new int[n];

    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < m; j++) {
            compCount++;
            if (text[i + j] != pat[j]) {
                match = false;
                break;
            }
        }
        if (match) result[count++] = i;
    }
    return result;
}

int main() {
    char text[] = "the quick brown fox jumps over the lazy dog";
    char pattern[] = "the";

    int count, comparisons;
    int* positions = bruteForceSearch(text, pattern, count, comparisons);

    cout << "Matches found at: ";
    for (int i = 0; i < count; i++)
        cout << positions[i] << " ";
    cout << "\nTotal Comparisons: " << comparisons;

    delete[] positions;
    return 0;
}
