#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.h"

/**
 * @class HashDoubleInt
 * @brief Una implementacion de una tabla hash, usando double hashing con una key entera.
 * 
 * Esta clase representa una tabla hash que guarda pares, donde el primero es la key y el segundo es un objeto User.
 * Ocupa double hashing como la estrategia de resolucion de colisiones.
 */
class HashDoubleInt {
private:
    std::vector<std::pair<int,User>> table; /**< El vector que almacena los pares key-User. */
    size_t table_size; /**< El tamaño de la tabla hash. >*/

    /**
     * @brief Funcion hash que retorna el modulo de la key con el tamaño de la tabla.
     * @param key La key a la que se le hará hash.
     * @return El valor hash.
     */
    size_t hash(int key) const {
        return key % table_size;
    }

    /**
     * @brief Verifica si es un numero primo.
     * @param n EL numero que será verificado.
     * @return True si el número es primo. False en otro caso
     */
    static bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;

        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }

        return true;
    }

    /**
     * @brief Busca el mayor numero primo menor que el numero dado.
     * @param n El numero para encontrar el mayor numero primo.
     * @return El mayor numero primo menor que n.
     */
    static int largestPrimeLessThan(int n) {
        for (int i = n - 1; i > 1; i--) {
            if (isPrime(i)) return i;
        }
        return 2;  
    }

    /**
     * @brief Segunda funcion hash que usa el numero primo mas cercano a el tamaño de la tabla.
     * @param key La key a la que se le hará hash.
     * @return EL valor hash.
     */
    size_t hash2(int key) const {
        int prime = largestPrimeLessThan(table_size);
        return prime - (key % prime);
    }

public:
    /**
     * @brief Construye un objeto de HashDoubleInt con el tamaño especificado.
     * @param size El tamaño de la tabla hash.
     */
    HashDoubleInt(size_t size) : table_size(size) {
        table.resize(size);
    }

    /**
     * @brief Inserta un par key-User a la tabla hash.
     * @param key La key a ser insertada.
     * @param usuario EL User a ser insertado.
     */
    void insert(int key, User usuario) {
        size_t index = hash(key); //Obtenemos el índice de la tabla
        int count = 0;
        while (table[index].first != 0 && table[index].first != -1) {
            index = (hash(index) + count++*hash2(index)) % table_size; 
        }
        table[index] = {key, usuario};
    }
    
    /**
     * @brief Busca por la key en la tabla hash y sobreescribe el Usuario entregado en el argumento con el usuario encontrado en la tabla hash.
     * @param key La key que será buscada.
     * @param usuario EL objeto User para guardar el resultado.
     * @return True si la key es encontrada, False en otro caso.
     */
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

    /**
     * @brief Elimina un par key-User de la tabla hash.
     * @param key La key que será removida.
     * @return True si la key es encontrada y eliminada, False en otro caso.
     */
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
