#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashTable {
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
    HashTable(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(std::string key, User usuario) {
        size_t index = hash(key);

        while (table[index].first != "") {
            index = hash(std::to_string(index + 1));
        }

        table[index] = {key, usuario};
    }

    bool search(std::string key, User& usuario) const {
        size_t index = hash(key);
        while(table[index].first == "0" || table[index].first == "-1"){
            index = hash(std::to_string(index + 1));
        }
        if (table[index].first == key) {
            usuario = table[index].second;
            return true;
        }
        return false;
    }

    bool remove(std::string key) {
        size_t index = hash(key);
        while(table[index].first == "0" || table[index].first == "-1"){
            index = hash(std::to_string(index + 1));
        }
        if (table[index].first == key) {
            table[index].first = "-1";
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
