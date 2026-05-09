#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include <vector>

using namespace std;

struct UnionFind {
    vector<int> padre;
    vector<int> rango;

    UnionFind(int n) {
        padre.resize(n);
        rango.resize(n, 0);
        for (int i = 0; i < n; i++) padre[i] = i;
    }


    int buscar(int i) {
        if (padre[i] == i) return i;
        return padre[i] = buscar(padre[i]);
    }


    void unir(int x, int y) {
        int rootX = buscar(x);
        int rootY = buscar(y);
        if (rootX != rootY) {
            if (rango[rootX] < rango[rootY]) padre[rootX] = rootY;
            else if (rango[rootX] > rango[rootY]) padre[rootY] = rootX;
            else {
                padre[rootY] = rootX;
                rango[rootX]++;
            }
        }
    }
};

#endif