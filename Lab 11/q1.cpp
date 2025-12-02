#include <iostream>
#include <list>
#include <string>
using namespace std;

class HashTable {
public:
    static const int size = 10;
    list<pair<string,string>> table[size];

    int hashFunc(string s) {
        int sum = 0;
        for(char c : s) sum += c;
        return sum % size;
    }

    void insert(string key, string value) {
        int idx = hashFunc(key);
        table[idx].push_back({key,value});
    }
};
