#include <iostream>
#include <list>
#include <string>
using namespace std;

class ASCIIDictionary {
public:
    static const int size = 100;
    list<pair<string,string>> table[size];

    int hashFunc(string s) {
        int sum = 0;
        for(char c : s) sum += c;
        return sum % size;
    }

    void Add_Record(string key, string value) {
        int idx = hashFunc(key);
        table[idx].push_back({key,value});
    }

    void Word_Search(string key) {
        int idx = hashFunc(key);
        for(auto &p : table[idx]) {
            if(p.first == key) {
                cout << p.first << ": " << p.second << endl;
                return;
            }
        }
        cout << "Error: word not found" << endl;
    }

    void Print_Dictionary() {
        for(int i = 0; i < size; i++) {
            for(auto &p : table[i]) {
                cout << "index " << i << ": (" << p.first << ", " << p.second << ")" << endl;
            }
        }
    }
};
