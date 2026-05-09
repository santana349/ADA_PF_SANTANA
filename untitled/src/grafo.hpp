#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>

using namespace std;

struct Arista {
    int origen;
    int destino;
    double peso;


    bool operator<(const Arista& otra) const {
        return peso < otra.peso;
    }
};


vector<Arista> generarGrafo(int numNodos);

#endif