#include <iostream>
#include <vector>
#include <list>
#include <string>

class HashTable {
private:
    std::vector<std::list<std::pair<std::string, int>>> table;
    size_t table_size;

    size_t hash(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 33 + ch;
        }
        return hash_value % table_size;
    }

public:
    HashTable(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(const std::string& key, int value) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    bool search(const std::string& key, int& value) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    bool remove(const std::string& key) {
        size_t index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }
};

int main() {
    HashTable ht(10);

    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("orange", 3);

    int value;
    if (ht.search("banana", value)) {
        std::cout << "Found: " << value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    ht.remove("banana");

    if (ht.search("banana", value)) {
        std::cout << "Found: " << value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}
