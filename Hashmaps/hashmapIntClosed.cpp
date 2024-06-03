#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashTable {
private:
    std::vector<std::pair<int,User>> table;
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

        while (table[index].first != 0) {
            index = hash(index + 1);
        }

        table[index] = {key, usuario};
    }

    bool search(int key, User& usuario) const {
        size_t index = hash(key);
        while(table[index].first == 0 || table[index].first == -1){
            index = hash(index + 1);
        }
        if (table[index].first == key) {
            usuario = table[index].second;
            return true;
        }
        return false;
    }

    bool remove(int key) {
        size_t index = hash(key);
        while(table[index].first == 0 || table[index].first == -1){
            index = hash(index + 1);
        }
        if (table[index].first == key) {
            table[index].first = -1;
            return true;
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
