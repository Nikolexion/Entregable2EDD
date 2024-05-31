#include <iostream>
#include <vector>
#include <list>
#include <utility>

class HashTable {
private:
    std::vector<std::list<std::pair<int, int>>> table;
    size_t table_size;

    size_t hash(int key) const {
        return key % table_size;
    }

public:
    HashTable(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(int key, int value) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    bool search(int key, int& value) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    bool remove(int key) {
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

    ht.insert(10, 100);
    ht.insert(20, 200);
    ht.insert(30, 300);

    int value;
    if (ht.search(20, value)) {
        std::cout << "Found: " << value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    ht.remove(20);

    if (ht.search(20, value)) {
        std::cout << "Found: " << value << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}
