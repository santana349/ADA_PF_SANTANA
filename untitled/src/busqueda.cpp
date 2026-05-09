#include "busqueda.hpp"

int busquedaBinariaR(const vector<Solicitud>& arr, int bajo, int alto, int k) {
    if (bajo > alto) {
        return -1;
    }

    int medio = bajo + (alto - bajo) / 2;


    if (arr[medio].tenure == k) {

        int izq = busquedaBinariaR(arr, bajo, medio - 1, k);
        if (izq != -1) return izq;
        return medio;
    }


    if (arr[medio].tenure < k) {

        return busquedaBinariaR(arr, bajo, medio - 1, k);
    } else {

        return busquedaBinariaR(arr, medio + 1, alto, k);
    }
}