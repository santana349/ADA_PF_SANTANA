
#include "parser.hpp"
#include "solicitud.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

std::vector<Solicitud> cargarCSV(std::string ruta) {
    std::vector<Solicitud> solicitudes;
    std::ifstream archivo(ruta);
    std::string linea;

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo en la ruta: " << ruta << std::endl;
        return solicitudes;
    }

    std::getline(archivo, linea);

    int nulos = 0;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string campo;
        std::vector<std::string> columnas;

        while (std::getline(ss, campo, ',')) {
            columnas.push_back(campo);
        }

        if (columnas.size() < 21) continue;

        Solicitud s;
        s.customerID = columnas[0];
        s.tenure = std::stoi(columnas[5]);
        s.monthlyCharges = std::stod(columnas[18]);

        if (s.tenure == 0 || columnas[19] == " " || columnas[19].empty()) {
            s.totalCharges = 0.0;
            nulos++;
        } else {
            try {
                s.totalCharges = std::stod(columnas[19]);
            } catch (...) {
                s.totalCharges = 0.0;
            }
        }

        s.churn = (columnas[20] == "Yes");
        solicitudes.push_back(s);
    }

    std::cout << "Registros cargados: " << solicitudes.size() << std::endl;
    std::cout << "Registros con TotalCharges nulo: " << nulos << std::endl;
    
    return solicitudes;
}
