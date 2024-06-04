#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.h"

/**
 * @class HashDoubleString
 * @brief Una implementacion de una tabla hash, usando double hashing con una key string.
 * 
 * Esta clase representa una tabla hash que guarda pares, donde el primero es la key y el segundo es un objeto User.
 * Ocupa double hashing como la estrategia de resolucion de colisiones.
 */
class HashDoubleString {
private:
    std::vector<std::pair<std::string,User>> table; /**< El vector que almacena los pares key-User. */
    size_t table_size; /**< El tamaño de la tabla hash. >*/

/**
     * @brief Primera funcion hash que crea un hash_value que empieza en 0 donde para cada caracter en la string key multiplica el hash_value por 33 y le suma el valor ascii del caracter, al resultado final le aplica el modulo con el tamaño de la tabla.
     * @param key La key a la que se le hará hash.
     * @return El valor hash.
     */
    size_t hash1(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 33 + ch;
        }
        return hash_value % table_size;
    }

    /**
     * @brief Segunda funcion hash que crea un hash_value que empieza en 0 donde para cada caracter en la string key multiplica el hash_value por 17 y le suma el valor ascii del caracter, al resultado final le aplica el modulo con el tamaño de la tabla - 1 y al total le suma 1.
     * @param key La key a la que se le hará hash.
     * @return El valor hash.
     */
    size_t hash2(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 17 + ch;
        }
        return 1 + (hash_value % (table_size - 1));
    }

public:
    /**
     * @brief Construye un objeto de HashDoubleString con el tamaño especificado.
     * @param size EL tamaño de la tabla hash.
     */
    HashDoubleString(size_t size) : table_size(size) {
        table.resize(size);
    }

    /**
     * @brief Inserta un par key-User a la tabla hash.
     * @param key La key a ser insertada.
     * @param usuario El User a ser insertado.
     */
    void insert(std::string key, User usuario) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        while (table[index].first != "" && table[index].first != "-1") {
            index = (index + step) % table.size();
        }
        table[index] = {key, usuario};
    }

    /**
     * @brief Busca por la key en la tabla hash y sobreescribe el Usuario entregado en el argumento con el usuario encontrado en la tabla hash.
     * @param key La key que será buscada.
     * @param usuario El objeto User para guardar el resultado.
     * @return True si la key es encontrada, False en otro caso.
     */
    bool search(std::string key, User& usuario) const {
        size_t index = hash1(key);
        size_t step = hash2(key);
        while (table[index].first != "" && table[index].first != key) {
            index = (index + step) % table.size();
        }
        if (table[index].first == key) {
            usuario = table[index].second;
            return true;
        }
        return false;
    }

    /**
     * @brief Elimina un par key-User de la tabla hash.
     * @param key La key que será removida.
     * @return True si la key es encontrada y eliminada, False en otro caso.
     */
    bool remove(std::string key) {
        size_t index = hash1(key);
        size_t step = hash2(key);
        while (table[index].first != "" && table[index].first != key) {
            index = (index + step) % table.size();
        }
        if (table[index].first == key) {
            table[index].first = "-1";
            return true;
        }
        return false;
    }
};
