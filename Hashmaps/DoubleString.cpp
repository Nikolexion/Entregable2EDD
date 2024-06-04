#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashDoubleString {
private:
    std::vector<std::pair<std::string,User>> table;
    size_t table_size;

    size_t hash1(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 33 + ch;
        }
        return hash_value % table_size;
    }

    size_t hash2(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 17 + ch;
        }
        return 1 + (hash_value % (table_size - 1));
    }

public:
    HashDoubleString(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(std::string key, User usuario) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        while (table[index].first != "" && table[index].first != "-1") {
            index = (index + step) % table.size();
        }
        table[index] = {key, usuario};
    }

    bool search(std::string key, User& usuario) const {
        size_t index = hash1(key);
        size_t step = hash2(key);
        while (table[index].first != "" && table[index].first != key) {
            index = (index + step) % table.size();
        }
        if (table[index].first == key) {
            usuario = table[index].second;
            return true;
        }
        return false;
    }

    bool remove(std::string key) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        while (table[index].first != "" && table[index].first != key) {
            index = (index + step) % table.size();
        }
        if (table[index].first == key) {
            table[index].first = "-1";
            return true;
        }
        return false;
    }
};
