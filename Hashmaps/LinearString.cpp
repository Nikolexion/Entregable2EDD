#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashLinearString {
private:
    std::vector<std::pair<std::string,User>> table;
    size_t table_size;

    size_t hash(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 33 + ch;
        }
        return hash_value % table_size;
    }

public:
    HashLinearString(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(std::string key, User usuario) {
        size_t index = hash(key);
        size_t originalIndex = index;
        int count = 0;
        do {
            if (table[index].first == "" || table[index].first == "-1") {
                table[index] = {key, usuario};
                return;
            }
            count++;
            index = (index + count) % table.size();
        } while (index != originalIndex);
    }

    bool search(std::string key, User& usuario) const {
        size_t index = hash(key);
        size_t originalIndex = index;
        int count = 0;
        do {
            if (table[index].first == key) {
                usuario = table[index].second;
                return true;
            }
            count++;
            index = (index + count) % table.size();
        } while (table[index].first != "" && index != originalIndex);

        return false;
    }

    bool remove(std::string key) {
        size_t index = hash(key);
        size_t originalIndex = index;
        int count = 0;
        do {
            if (table[index].first == key) {
                table[index].first = "-1";
                return true;
            }
            count++;
            index = (index + count) % table.size();
        } while (table[index].first != "" && index != originalIndex);

        return false;
        }
};
