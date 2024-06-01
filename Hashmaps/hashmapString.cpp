#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "User.cpp"

class HashTable {
private:
    std::vector<std::list<std::pair<std::string, User>>> table;
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

    void insert(std::string key, User usuario) {
        size_t index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = usuario;
                return;
            }
        }
        table[index].emplace_back(key, usuario);
    }

    bool search(std::string key, User& usuario) const {
        size_t index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                usuario = pair.second;
                return true;
            }
        }
        return false;
    }

    bool remove(std::string key) {
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

    ht.insert(user1.username, user1);
    ht.insert(user2.username, user2);
    ht.insert(user3.username, user3);

    User usuario;
    if (ht.search("User1", usuario)) {
        std::cout << "Found: " << usuario.username << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    ht.remove("User1");

    if (ht.search("User1", usuario)) {
        std::cout << "Found: " << usuario.username << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}