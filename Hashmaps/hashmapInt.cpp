#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashAbiertoInt {
private:
    std::vector<std::list<std::pair<int,User>>> table;
    size_t table_size;

    size_t hash(int key) const {
        return key % table_size;
    }

public:
    HashAbiertoInt(size_t size) : table_size(size) {
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

int main(int argc, char** argv) {
    // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]); // Almacenará la cantidad de elementos
    HashAbiertoInt hashTable(n); // Crearemos una tabla de hash con n elementos
        
    // Creamos n usuarios y los insertamos en la tabla hash
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; i++) {
        User user;
        user.userId = i;
        hashTable.insert(i, user);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double insert_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

    // Buscamos cada usuario en la tabla hash
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; i++) {
        User user;
        hashTable.search(i, user);
    }
    end = std::chrono::high_resolution_clock::now();
    double search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

    // Eliminamos cada usuario de la tabla hash
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; i++) {
        hashTable.remove(i);
    }
    end = std::chrono::high_resolution_clock::now();
    double remove_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-9;

    // Imprimimos los resultados
    std::cout << "Insert time: " << insert_time << " seconds\n";
    std::cout << "Search time: " << search_time << " seconds\n";
    std::cout << "Remove time: " << remove_time << " seconds\n";

    return 0;
}