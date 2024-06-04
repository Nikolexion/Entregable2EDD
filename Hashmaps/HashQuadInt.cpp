#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashQuadInt {
private:
    std::vector<std::pair<int,User>> table;
    size_t table_size;

    size_t hash(int key) const {
        return key % table_size;
    }

public:
    HashQuadInt(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(int key, User usuario) {
        size_t index = hash(key);
        int count = 0;

        while (table[index].first != 0 && table[index].first != -1) {
            count++;
            index = hash(key + count * count);
        }

        table[index] = {key, usuario};
    }

    bool search(int key, User& usuario) const {
        size_t index = hash(key);
        int count = 0;

        while (table[index].first == 0 || table[index].first == -1) {
            count++;
            index = hash(key + count * count);
        }

        if (table[index].first == key) {
            usuario = table[index].second;
            return true;
        }

        return false;
    }

    bool remove(int key) {
        size_t index = hash(key);
        int count = 0;

        while (table[index].first == 0 || table[index].first == -1) {
            count++;
            index = hash(key + count * count);
        }

        if (table[index].first == key) {
            table[index].first = -1;
            return true;
        }

        return false;
    }
};
