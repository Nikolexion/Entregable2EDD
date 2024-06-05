#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "HashAbiertoString.cpp"
#include "HashAbiertoInt.cpp"
#include "HashDoubleInt.cpp"
#include "HashDoubleString.cpp"
#include "HashLinearInt.cpp"
#include "HashLinearString.cpp"
#include "HashQuadInt.cpp"
#include "HashQuadString.cpp"

// Función para leer el archivo CSV y retornar un vector de User
std::vector<User> readCSV(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line, cell;

    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::vector<std::string> tokens;

        while (std::getline(lineStream, cell, ',')) {
            tokens.push_back(cell);
        }

        if (tokens.size() == 7) {
            std::string university = tokens[0];
            unsigned long long userID = std::stoll(tokens[1]); // Use std::stoll for long long int
            std::string userName = tokens[2];
            int numberTweets = std::stoi(tokens[3]);
            int friendsCount = std::stoi(tokens[4]);
            int followersCount = std::stoi(tokens[5]);
            std::string createdAt = tokens[6];

            users.push_back(User(university, userID, userName, numberTweets, friendsCount, followersCount, createdAt));
        }
    }
    return users;
}

int main(int argc, char** argv) {
    std::vector<User> users = readCSV("universities_followers.csv");

    // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }

    int n = atoi(argv[1]); // Almacenará la cantidad de elementos

    // Abrimos el archivo .csv en modo de escritura
    std::ofstream file("resultados.csv");
    file << "Test;Elementos;Operacion;Tiempo\n"; // Escribimos la cabecera del archivo .csv

    // Realizamos las pruebas varias veces
    for (int test = 1; test <= 10; test++) {
        HashAbiertoInt hashTable(n); // Crearemos una tabla de hash con n elementos

        // Creamos n usuarios y los insertamos en la tabla hash
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            User user = users[i];
            hashTable.insert(user.userID, user);
        }
        auto end = std::chrono::high_resolution_clock::now();
        unsigned long long insert_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Buscamos cada usuario en la tabla hash
        start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            User user = users[i];
            hashTable.search(user.userID, user);
        }
        end = std::chrono::high_resolution_clock::now();
        unsigned long long search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Eliminamos cada usuario de la tabla hash
        start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            hashTable.remove(i);
        }
        end = std::chrono::high_resolution_clock::now();
        unsigned long long remove_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Escribimos los resultados en el archivo .csv
        file << test << ";" << n << ";insert;" << insert_time << "\n";
        file << test << ";" << n << ";search;" << search_time << "\n";
        file << test << ";" << n << ";remove;" << remove_time << "\n";
    }

    file.close(); // Cerramos el archivo .csv
    return 0;
}
