#ifndef INCLUDES
#define INCLUDES
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include "User.h"
#endif

#ifndef HASH_QUAD_STRING
#define HASH_QUAD_STRING
/**
 * @class HashQuadString
 * @brief Una implementacion de una tabla hash, usando quadratic hashing con una key string.
 * 
 * Esta clase representa una tabla hash que guarda pares, donde el primero es la key y el segundo es un objeto User.
 * Ocupa quadratic hashing como la estrategia de resolucion de colisiones.
 */
class HashQuadString {
private:
    std::vector<std::pair<std::string,User>> table; /**< El vector que almacena los pares key-User. */
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
     * @brief Construye un objeto de HashQuadString con el tamaño especificado.
     * @param size EL tamaño de la tabla hash.
     */
    HashQuadString(unsigned long long size) : table_size(size) {
        table.resize(size);
    }

    /**
     * @brief Inserta un par key-User a la tabla hash.
     * @param key La key a ser insertada.
     * @param usuario El User a ser insertado.
     */
    void insert(std::string key, User usuario) {
        unsigned long long index = hash(key); //Obtenemos el índice de la tabla
        unsigned long long originalIndex = index; //Guardamos el índice original
        unsigned long long count = 0;
        //Buscamos un lugar vacío en la tabla
        do {
            //Si encontramos un lugar vacío, insertamos el par key-usuario
            if (table[index].first == "" || table[index].first == "-1") {
                table[index] = {key, usuario};
                return;
            }

            //Si no encontramos un lugar vacío, seguimos buscando con quadratic hashing
            count++;
            index = (index + count*count) % table.size();
            if (count > table_size) return; //Si se ha recorrido toda la tabla y no se ha encontrado la key, se retorna (no se encuentra en la tabla)
        } while (count < table.size() && index != originalIndex);
    }

    /**
     * @brief Busca por la key en la tabla hash y sobreescribe el Usuario entregado en el argumento con el usuario encontrado en la tabla hash.
     * @param key La key que será buscada.
     * @param usuario EL objeto User para guardar el resultado.
     * @return True si la key es encontrada, False en otro caso.
     */
    bool search(std::string key, User& usuario) const {
        unsigned long long index = hash(key); //Obtenemos el índice de la tabla
        unsigned long long originalIndex = index; //Guardamos el índice original
        unsigned long long count = 0;

        //Buscamos la key en la tabla
        do {
            //Si encontramos la key, retornamos true y guardamos el usuario en el argumento
            if (table[index].first == key) {
                usuario = table[index].second;
                return true;
            }
            //Si no encontramos la key, seguimos buscando con quadratic hashing
            count++;
            index = (index + count*count) % table.size();
            if (count > table_size) return false; //Si se ha recorrido toda la tabla y no se ha encontrado la key, se retorna false (no se encuentra en la tabla)
        } while (table[index].first != key && count < table.size());

        return false;
    }

    /**
     * @brief Elimina un par key-User de la tabla hash.
     * @param key La key que será removida.
     * @return True si la key es encontrada y eliminada, False en otro caso.
     */
    bool remove(std::string key) {
        unsigned long long index = hash(key); //Obtenemos el índice de la tabla
        unsigned long long originalIndex = index; //Guardamos el índice original
        unsigned long long count = 0;

        //Buscamos la key en la tabla
        do {
            //Si encontramos la key, la eliminamos y retornamos true
            if (table[index].first == key) {
                table[index].first = "-1";
                return true;
            }
            //Si no encontramos la key, seguimos buscando con quadratic hashing
            count++;
            index = (index + count*count) % table.size();
            if (count > table_size) return false; //Si se ha recorrido toda la tabla y no se ha encontrado la key, se retorna false (no se encuentra en la tabla)
        } while (table[index].first != key && count < table.size());

        return false;
    }

    /**
     * @brief Devuelve el tamaño en bytes de toda la tabla hash.
     * @return El tamaño en bytes de la tabla hash.
     */
    size_t totalSizeInBytes() const {
        size_t totalSize = 0;
        for (const auto& pair : table) {
            totalSize += sizeof(pair.first) + sizeof(pair.second);
        }
        return totalSize;
    }
};

#endif