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

int main(int argc, char** argv) {
    // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); // Almacenará la cantidad de elementos
    HashLinearString hashTable(n); // Crearemos una tabla de hash con n elementos
        
    // Creamos n usuarios y los insertamos en la tabla hash
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; i++) {
        User user;
        user.userId = i;
        hashTable.insert(std::to_string(i), user);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double insert_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

    // Buscamos cada usuario en la tabla hash
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; i++) {
        User user;
        hashTable.search(std::to_string(i), user);
    }
    end = std::chrono::high_resolution_clock::now();
    double search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

    // Eliminamos cada usuario de la tabla hash
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; i++) {
        hashTable.remove(std::to_string(i));
    }
    end = std::chrono::high_resolution_clock::now();
    double remove_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

    // Imprimimos los resultados
    std::cout << "Insert time: " << insert_time << " seconds\n";
    std::cout << "Search time: " << search_time << " seconds\n";
    std::cout << "Remove time: " << remove_time << " seconds\n";

    return 0;
}