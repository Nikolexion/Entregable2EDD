#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include "User.cpp"

class HashTable {
private:
    std::vector<std::pair<int,User>> table;
    size_t table_size;

    size_t hash(int key) const {
        return key % table_size;
    }

    static bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;

        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }

        return true;
    }

    static int largestPrimeLessThan(int n) {
        for (int i = n - 1; i > 1; i--) {
            if (isPrime(i)) return i;
        }
        return 2;  
    }

    size_t hash2(int key) const {
        int prime = largestPrimeLessThan(table_size);
        return prime - (key % prime);
    }

public:
    HashTable(size_t size) : table_size(size) {
        table.resize(size);
    }

    void insert(int key, User usuario) {
        size_t index = hash(key);
        int count = 0;
        while (table[index].first != 0) {
            index = hash(hash(index) + count++*hash2(index));
        }

        table[index] = {key, usuario};
    }

    bool search(int key, User& usuario) const {
        size_t index = hash(key);
        int count = 1;
        while(table[index].first == 0 || table[index].first == -1){
            index = hash(hash(index) + count++*hash2(index));
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
            index = hash(hash(index) + count++*hash2(index));
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