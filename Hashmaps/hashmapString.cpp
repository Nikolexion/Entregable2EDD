#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>
#include "User.cpp"

class HashAbiertoString {
private:
    //Creamos un vector de listas de pares de enteros(keys) y usuarios
    std::vector<std::list<std::pair<std::string, User>>> table;
    size_t table_size;

    //Función hash que retorna el valor de la key multiplicado por 33 y sumado con el valor ASCII de cada caracter de la key
    size_t hash(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 33 + ch;
        }
        return hash_value % table_size;
    }

public:
    HashAbiertoString(size_t size) : table_size(size) {
        table.resize(size);
    }

    //Insertamos un usuario en la tabla hash
    void insert(std::string key, User usuario) {
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
    bool search(std::string key, User& usuario) const {
        size_t index = hash(key); //Obtenemos el índice de la tabla
        for (const auto& pair : table[index]) { //Recorremos la lista en la posición index
            if (pair.first == key) {
                usuario = pair.second;
                return true; //Si no encontramos la key, retornamos false
            }
        }
        return false;
    }

    //Eliminamos un usuario de la tabla hash
    bool remove(std::string key) {
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
