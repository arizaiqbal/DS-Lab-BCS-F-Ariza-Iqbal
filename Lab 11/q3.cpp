
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Hash {
public:
    static const int size = 20;
    list<pair<string,string>> table[size];

    int hashFunc(string k) {
        int sum = 0;
        for(char c : k) sum += c;
        return sum % size;
    }

    void insert(string key, string value) {
        table[hashFunc(key)].push_back({key,value});
    }

    void removeKey(string key) {
        int idx = hashFunc(key);
        for(auto it = table[idx].begin(); it != table[idx].end(); it++) {
            if(it->first == key) {
                table[idx].erase(it);
                cout << "Key deleted\n";
                return;
            }
        }
        cout << "Key not found\n";
    }

    void search(string key) {
        int idx = hashFunc(key);
        for(auto &p : table[idx]) {
            if(p.first == key) {
                cout << p.first << ": " << p.second << endl;
                return;
            }
        }
        cout << "Not found\n";
    }

    void display() {
        for(int i = 0; i < size; i++)
            for(auto &p : table[i])
                cout << "(" << p.first << ", " << p.second << ") ";
        cout << endl;
    }
};
