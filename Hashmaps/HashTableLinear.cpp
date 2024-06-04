#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashTableLinear {
private:
    std::vector<std::pair<int,User>> table;
    size_t table_size;

    size_t hash(int key) const {
        return key % table_size;
    }

public:
    HashTableLinear(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(int key, User usuario) {
        size_t index = hash(key);

        while (table[index].first != 0 && table[index].first != -1) {
            index = hash(index + 1);
        }

        table[index] = {key, usuario};
    }

    bool search(int key, User& usuario) const {
        size_t index = hash(key);
        int count = 1;
        while(table[index].first == 0 || table[index].first == -1){
            index = hash(index + count++);
        }
        if (table[index].first == key) {
            usuario = table[index].second;
            return true;
        }
        return false;
    }

    bool remove(int key) {
        size_t index = hash(key);
        int count = 1;
        while(table[index].first == 0 || table[index].first == -1){
            index = hash(index + count++);
        }
        if (table[index].first == key) {
            table[index].first = -1;
            return true;
        }
        return false;
    }
};
