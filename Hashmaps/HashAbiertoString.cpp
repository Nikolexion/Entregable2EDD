#ifndef INCLUDES
#define INCLUDES
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include "User.h"
#endif


#ifndef HASH_ABIERTO_STRING
#define HASH_ABIERTO_STRING
/**
 * @class HashAbiertoString
 * @brief Una implementacion de una tabla hash, usando hashing abierto con una key string.
 * 
 * Esta clase representa una tabla hash que guarda pares, donde el primero es la key y el segundo es un objeto User.
 * Ocupa hashing abierto como la estrategia de resolucion de colisiones.
 */
class HashAbiertoString {
private:
    std::vector<std::list<std::pair<std::string, User>>> table; /**< El vector que almacena los pares key-User. */
    unsigned long long table_size; /**< El tamaño de la tabla hash. >*/

    /**
     * @brief Funcion hash que crea un hash_value que empieza en 0 donde para cada caracter en la string key multiplica el hash_value por 33 y le suma el valor ascii del caracter, al resultado final le aplica el modulo con el tamaño de la tabla.
     * @param key La key a la que se le hará hash.
     * @return El valor hash.
     */
    unsigned long long hash(const std::string& key) const {
        unsigned long long hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 33 + ch;
        }
        return hash_value % table_size;
    }

public:
    /**
     * @brief Construye un objeto de HashAbiertoString con el tamaño especificado.
     * @param size EL tamaño de la tabla hash.
     */
    HashAbiertoString(unsigned long long size) : table_size(size) {
        table.resize(size);
    }

    /**
     * @brief Inserta un par key-User a la tabla hash.
     * @param key La key a ser insertada.
     * @param usuario EL User a ser insertado.
     */
    void insert(std::string key, User usuario) {
        unsigned long long index = hash(key); //Obtenemos el índice de la tabla
        for (auto& pair : table[index]) { //Recorremos la lista en la posición index
            if (pair.first == key) { //Si la key ya existe, actualizamos el usuario
                pair.second = usuario;
                return;
            }
        }
        table[index].emplace_back(key, usuario); //Si no existe, insertamos el par key-usuario
    }

    /**
     * @brief Busca por la key en la tabla hash y sobreescribe el Usuario entregado en el argumento con el usuario encontrado en la tabla hash.
     * @param key La key que será buscada.
     * @param usuario EL objeto User para guardar el resultado.
     * @return True si la key es encontrada, False en otro caso.
     */
    bool search(std::string key, User& usuario) const {
        unsigned long long index = hash(key); //Obtenemos el índice de la tabla
        for (const auto& pair : table[index]) { //Recorremos la lista en la posición index
            if (pair.first == key) {
                usuario = pair.second;
                return true; //Si no encontramos la key, retornamos false
            }
        }
        return false;
    }

    /**
     * @brief Elimina un par key-User de la tabla hash.
     * @param key La key que será removida.
     * @return True si la key es encontrada y eliminada, False en otro caso.
     */
    bool remove(std::string key) {
        unsigned long long index = hash(key); //Obtenemos el índice de la tabla
        for (auto it = table[index].begin(); it != table[index].end(); ++it) { //Recorremos la lista en la posición index
            if (it->first == key) { //Si encontramos la key, la eliminamos
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Devuelve el tamaño en bytes de toda la tabla hash.
     * @return El tamaño en bytes de la tabla hash.
     */
    size_t totalSizeInBytes() const {
        size_t size = 0;
        for (const auto& list : table) {
            for (const auto& pair : list) {
                size += sizeof(pair.first) + sizeof(pair.second);
            }
        }
        return size;
    }
};

#endif