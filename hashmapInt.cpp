#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include "User.cpp"

class HashTable {
private:
    std::vector<std::list<std::pair<int,User>>> table;
    size_t table_size;

    size_t hash(int key) const {
        return key % table_size;
    }

public:
    HashTable(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(int key, User usuario) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = usuario;
                return;
            }
        }
        table[index].emplace_back(key, usuario);
    }

    bool search(int key, User& usuario) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                usuario = pair.second;
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

    User user1 = {"University1", 10, "User1", 100, 10, 10, "2022-01-01"};
    User user2 = {"University2", 20, "User2", 200, 20, 20, "2022-02-02"};
    User user3 = {"University3", 30, "User3", 300, 30, 30, "2022-03-03"};

    ht.insert(user1.userId, user1);
    ht.insert(user2.userId, user2);
    ht.insert(user3.userId, user3);

    User usuario;
    if (ht.search(20, usuario)) {
        std::cout << "Found: " << usuario.username << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    ht.remove(20);

    if (ht.search(20, usuario)) {
        std::cout << "Found: " << usuario.username << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}