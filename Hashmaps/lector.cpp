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

// FunciÃ³n para leer el archivo CSV y retornar un vector de User
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

int main() {
    std::vector<User> users = readCSV("universities_followers.csv");


    int n = 10000; // Almacenará la cantidad de elementos
    int m = 15000;
    int o = 20000;
    int p = 1000;
    int q = 5000;

    // Abrimos el archivo .csv en modo de escritura
    std::ofstream file("resultados.csv");
    file << "Test;Elementos;Operacion;Tiempo\n"; // Escribimos la cabecera del archivo .csv

    // Realizamos las pruebas varias veces
    for (int test = 1; test <= 30; test++) {
        HashDoubleInt hashTableN(n); // Crearemos una tabla de hash con n elementos
        HashDoubleInt hashTableM(m);
        HashDoubleInt hashTableO(o);
        HashDoubleInt hashTableP(p);
        HashDoubleInt hashTableQ(q);
        std::cout << "Inicio del test " << test << std::endl;

        auto startP = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= p; i++) {
            User user = users[i];
            hashTableP.insert(user.userID, user);
        }
        auto endP = std::chrono::high_resolution_clock::now();
        unsigned long long insert_timeP = std::chrono::duration_cast<std::chrono::nanoseconds>(endP - startP).count();

        // Buscamos cada usuario en la tabla hash
        startP = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= p; i++) {
            User user = users[i];
            hashTableP.search(user.userID, user);
        }
        endP = std::chrono::high_resolution_clock::now();
        unsigned long long search_timeP = std::chrono::duration_cast<std::chrono::nanoseconds>(endP - startP).count();

        // Eliminamos cada usuario de la tabla hash
        startP = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= p; i++) {
            User user = User("",-i,"",0,0,0,"");
            hashTableP.search(user.userID, user);
        }
        endP = std::chrono::high_resolution_clock::now();
        unsigned long long remove_timeP = std::chrono::duration_cast<std::chrono::nanoseconds>(endP - startP).count();

        // Escribimos los resultados en el archivo .csv
        file <<"HashDoubleInt" << ";" << p << ";insert;" << insert_timeP << "\n";
        file <<"HashDoubleInt" << ";" << p << ";search;" << search_timeP << "\n";
        file <<"HashDoubleInt" << ";" << p << ";search_nouser;" << remove_timeP << "\n";
        std::cout << "Fin test "<< p << " "<< test << std::endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        auto startQ = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= q; i++) {
            User user = users[i];
            hashTableQ.insert(user.userID, user);
        }
        auto endQ = std::chrono::high_resolution_clock::now();
        unsigned long long insert_timeQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endQ - startQ).count();

        // Buscamos cada usuario en la tabla hash
        startQ = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= q; i++) {
            User user = users[i];
            hashTableQ.search(user.userID, user);
        }
        endQ = std::chrono::high_resolution_clock::now();
        unsigned long long search_timeQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endQ - startQ).count();

        // Eliminamos cada usuario de la tabla hash
        startQ = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= q; i++) {
            User user = User("",-i,"",0,0,0,"");
            hashTableQ.search(user.userID, user);
        }
        endQ = std::chrono::high_resolution_clock::now();
        unsigned long long remove_timeQ = std::chrono::duration_cast<std::chrono::nanoseconds>(endQ - startQ).count();

        // Escribimos los resultados en el archivo .csv
        file <<"HashDoubleInt" << ";" << q << ";insert;" << insert_timeQ << "\n";
        file <<"HashDoubleInt" << ";" << q << ";search;" << search_timeQ << "\n";
        file <<"HashDoubleInt" << ";" << q << ";search_nouser;" << remove_timeQ << "\n";
        std::cout << "Fin test"<< q << " "<< test << std::endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Creamos n usuarios y los insertamos en la tabla hash
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            User user = users[i];
            hashTableN.insert(user.userID, user);
        }
        auto end = std::chrono::high_resolution_clock::now();
        unsigned long long insert_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Buscamos cada usuario en la tabla hash
        start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            User user = users[i];
            hashTableN.search(user.userID, user);
        }
        end = std::chrono::high_resolution_clock::now();
        unsigned long long search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Buscamos de usuario inecistentes en la tabla hash
        start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            User user = User("",-i,"",0,0,0,"");
            hashTableN.search(user.userID, user);
        }
        end = std::chrono::high_resolution_clock::now();
        unsigned long long remove_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        // Escribimos los resultados en el archivo .csv
        file <<"HashDoubleInt" << ";" << n << ";insert;" << insert_time << "\n";
        file <<"HashDoubleInt" << ";" << n << ";search;" << search_time << "\n";
        file <<"HashDoubleInt" << ";" << n << ";search_nouser;" << remove_time << "\n";
        std::cout << "Fin test"<< n << " "<< test << std::endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Creamos n usuarios y los insertamos en la tabla hash
        auto startM = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= m; i++) {
            User user = users[i];
            hashTableM.insert(user.userID, user);
        }
        auto endM = std::chrono::high_resolution_clock::now();
        unsigned long long insert_timeM = std::chrono::duration_cast<std::chrono::nanoseconds>(endM - startM).count();

        // Buscamos cada usuario en la tabla hash
        startM = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= m; i++) {
            User user = users[i];
            hashTableM.search(user.userID, user);
        }
        endM = std::chrono::high_resolution_clock::now();
        unsigned long long search_timeM = std::chrono::duration_cast<std::chrono::nanoseconds>(endM - startM).count();

        // Eliminamos cada usuario de la tabla hash
        startM = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= m; i++) {
            User user = User("",-i,"",0,0,0,"");
            hashTableM.search(user.userID, user);
        }
        endM = std::chrono::high_resolution_clock::now();
        unsigned long long remove_timeM = std::chrono::duration_cast<std::chrono::nanoseconds>(endM - startM).count();

        // Escribimos los resultados en el archivo .csv
        file <<"HashDoubleInt" << ";" << m << ";insert;" << insert_timeM << "\n";
        file <<"HashDoubleInt" << ";" << m << ";search;" << search_timeM << "\n";
        file <<"HashDoubleInt" << ";" << m << ";search_nouser;" << remove_timeM << "\n";
        std::cout << "Fin test"<< m << " "<< test << std::endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Creamos n usuarios y los insertamos en la tabla hash
        auto startO = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= o; i++) {
            User user = users[i];
            hashTableO.insert(user.userID, user);
        }
        auto endO = std::chrono::high_resolution_clock::now();
        unsigned long long insert_timeO = std::chrono::duration_cast<std::chrono::nanoseconds>(endO - startO).count();

        // Buscamos cada usuario en la tabla hash
        startO = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= o; i++) {
            User user = users[i];
            hashTableO.search(user.userID, user);
        }
        endO = std::chrono::high_resolution_clock::now();
        unsigned long long search_timeO = std::chrono::duration_cast<std::chrono::nanoseconds>(endO - startO).count();

        // Eliminamos cada usuario de la tabla hash
        startO = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= o; i++) {
            User user = User("",-i,"",0,0,0,"");
            hashTableO.search(user.userID, user);
        }
        endO = std::chrono::high_resolution_clock::now();
        unsigned long long remove_timeO = std::chrono::duration_cast<std::chrono::nanoseconds>(endO - startO).count();

        // Escribimos los resultados en el archivo .csv
        file <<"HashDoubleInt" << ";" << o << ";insert;" << insert_timeO << "\n";
        file <<"HashDoubleInt" << ";" << o << ";search;" << search_timeO << "\n";
        file <<"HashDoubleInt" << ";" << o << ";search_nouser;" << remove_timeO << "\n";
        std::cout << "Fin test"<< o << " "<< test << std::endl;
    }

    
    file.close(); // Cerramos el archivo .csv
    return 0;
}
