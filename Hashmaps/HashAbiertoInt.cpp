#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include "User.h"
/**
 * @class HashAbiertoInt
 * @brief Una implementacion de una tabla hash, usando hasing abierto con una key entera.
 * 
 * Esta clase representa una tabla hash que guarda pares, donde el primero es la key y el segundo es un objeto User.
 * Ocupa hashing abierto como la estrategia de resolucion de colisiones.
 */
class HashAbiertoInt {
private:
    std::vector<std::list<std::pair<int,User>>> table; /**< El vector que almacena los pares key-User. */
    size_t table_size; /**< El tamaño de la tabla hash. >*/

    /**
     * @brief Funcion hash que retorna el modulo de la key con el tamaño de la tabla.
     * @param key La key a la que se le hará hash.
     * @return El valor hash.
     */
    size_t hash(int key) const {
        return key % table_size;
    }

public:
    /**
     * @brief Construye un objeto de HashAbiertoInt con el tamaño especificado.
     * @param size EL tamaño de la tabla hash.
     */
    HashAbiertoInt(size_t size) : table_size(size) {
        table.resize(size);
    }

    /**
     * @brief Inserta un par key-User a la tabla hash.
     * @param key La key a ser insertada.
     * @param usuario EL User a ser insertado.
     */
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

    /**
     * @brief Busca por la key en la tabla hash y sobreescribe el Usuario entregado en el argumento con el usuario encontrado en la tabla hash.
     * @param key La key que será buscada.
     * @param usuario EL objeto User para guardar el resultado.
     * @return True si la key es encontrada, False en otro caso.
     */
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

    /**
     * @brief Elimina un par key-User de la tabla hash.
     * @param key La key que será removida.
     * @return True si la key es encontrada y eliminada, False en otro caso.
     */
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
