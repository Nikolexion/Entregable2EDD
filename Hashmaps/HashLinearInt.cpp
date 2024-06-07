#ifndef INCLUDES
#define INCLUDES
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include "User.h"
#endif

#ifndef HASH_LINEAR_INT
#define HASH_LINEAR_INT
/**
 * @class HashLinearInt
 * @brief Una implementacion de una tabla hash, usando linear hashing con una key entera.
 * 
 * Esta clase representa una tabla hash que guarda pares, donde el primero es la key y el segundo es un objeto User.
 * Ocupa linear hashing como la estrategia de resolucion de colisiones.
 */
class HashLinearInt {
private:
    std::vector<std::pair<unsigned long long,User>> table; /**< El vector que almacena los pares key-User. */
    unsigned long long table_size; /**< El tamaño de la tabla hash. >*/

    /**
     * @brief Funcion hash que retorna el modulo de la key con el tamaño de la tabla.
     * @param key La key a la que se le hará hash.
     * @return El valor hash.
     */
    unsigned long long hash(unsigned long long key) const {
        return key % table_size;
    }

public:
    /**
     * @brief Construye un objeto de HashLinearInt con el tamaño especificado.
     * @param size El tamaño de la tabla hash.
     */
    HashLinearInt(unsigned long long size) : table_size(size) {
        table.resize(size);
    }

    /**
     * @brief Inserta un par key-User a la tabla hash.
     * @param key La key a ser insertada.
     * @param usuario EL User a ser insertado.
     */
    void insert(unsigned long long key, User usuario) {
        unsigned long long index = hash(key);
        unsigned long long count = 0;
        while (table[index].first != 0 && table[index].first != -1) {
            index = hash(index + ++count);
            if (count > table_size) return; //Si se ha recorrido toda la tabla y no se ha encontrado la key, se retorna (no se encuentra en la tabla)
        }

        table[index] = {key, usuario};
    }

    /**
     * @brief Busca por la key en la tabla hash y sobreescribe el Usuario entregado en el argumento con el usuario encontrado en la tabla hash.
     * @param key La key que será buscada.
     * @param usuario EL objeto User para guardar el resultado.
     * @return True si la key es encontrada, False en otro caso.
     */
    bool search(unsigned long long key, User& usuario) const {
        unsigned long long index = hash(key);
        unsigned long long count = 1;
        while(table[index].first == 0 || table[index].first == -1){
            index = hash(index + count++);
            if (count > table_size) return false; //Si se ha recorrido toda la tabla y no se ha encontrado la key, se retorna false (no se encuentra en la tabla)
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
    bool remove(unsigned long long key) {
        unsigned long long index = hash(key);
        unsigned long long count = 1;
        while(table[index].first == 0 || table[index].first == -1){
            index = hash(index + count++);
            if (count > table_size) return false; //Si se ha recorrido toda la tabla y no se ha encontrado la key, se retorna false (no se encuentra en la tabla)
        }
        if (table[index].first == key) {
            table[index].first = -1;
            return true;
        }
        return false;
    }

    
    /**
     * @brief Devuelve el tamaño total en bytes de la tabla hash.
     * @return El tamaño total en bytes de la tabla hash.
     */
    unsigned long long totalSizeInBytes() const {
        unsigned long long totalSize = 0;
        for (unsigned long long i = 0; i < table_size; ++i) {
            totalSize += sizeof(table[i]);
        }
        return totalSize;
    }
};

#endif