#ifndef MOCHILA_HPP
#define MOCHILA_HPP

#include <vector>
#include <string>
#include "solicitud.hpp"

using namespace std;

struct ResultadoMochila {
    double valorMaximo;
    vector<Solicitud> seleccionados;
};


ResultadoMochila resolverMochila(const vector<Solicitud>& solicitudes, int capacidadW);

#endif