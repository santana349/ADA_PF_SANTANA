#include "grafo.hpp"
#include <cmath>
#include <vector>

using namespace std;

vector<Arista> generarGrafo(int numNodos) {
    vector<Arista> aristas;
    
    for (int i = 0; i < numNodos; i++) {

        if (i + 1 < numNodos) {
            Arista a;
            a.origen = i;
            a.destino = i + 1;

            a.peso = (i * 7 + (i + 1) * 3) % 100 + 10.5; 
            aristas.push_back(a);
        }

        if (i + 2 < numNodos) {
            Arista a;
            a.origen = i;
            a.destino = i + 2;
            a.peso = (i * 5 + (i + 2) * 2) % 100 + 15.2;
            aristas.push_back(a);
        }
    }
    return aristas;
}