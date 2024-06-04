#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.cpp"

class HashAbiertoInt {
private:
    //Creamos un vector de listas de pares de enteros(keys) y usuarios
    std::vector<std::list<std::pair<int,User>>> table;
    size_t table_size;

    //Función hash que retorna el módulo de la key con el tamaño de la tabla
    size_t hash(int key) const {
        return key % table_size;
    }

public:
    HashAbiertoInt(size_t size) : table_size(size) {
        table.resize(size);
    }

    //Insertamos un usuario en la tabla hash
    void insert(int key, User usuario) {
        size_t index = hash(key); //Obtenemos el índice de la tabla
        for (auto& pair : table[index]) { //Recorremos la lista en la posición index
            if (pair.first == key) { //Si la key ya existe, actualizamos el usuario
                pair.second = usuario; 
                return;
            }
        }
        table[index].emplace_back(key, usuario); //Si no existe, insertamos el par key-usuario
    }

    //Buscamos un usuario en la tabla hash
    bool search(int key, User& usuario) const {
        size_t index = hash(key); //Obtenemos el índice de la tabla
        for (const auto& pair : table[index]) { //Recorremos la lista en la posición index
            if (pair.first == key) {
                usuario = pair.second;
                return true;
            }
        }
        return false; //Si no encontramos la key, retornamos false
    }

    //Eliminamos un usuario de la tabla hash
    bool remove(int key) {
        size_t index = hash(key); //Obtenemos el índice de la tabla
        for (auto it = table[index].begin(); it != table[index].end(); ++it) { //Recorremos la lista en la posición index
            if (it->first == key) { //Si encontramos la key, la eliminamos
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }
};
