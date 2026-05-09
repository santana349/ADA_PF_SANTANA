#include "mochila.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

ResultadoMochila resolverMochila(const vector<Solicitud>& solicitudes, int W) {
    int n = solicitudes.size();

    vector<vector<double>> dp(n + 1, vector<double>(W + 1, 0.0));

    for (int i = 1; i <= n; i++) {
        int pesoActual = solicitudes[i - 1].tenure;
        double valorActual = solicitudes[i - 1].monthlyCharges;

        for (int w = 0; w <= W; w++) {
            if (pesoActual <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - pesoActual] + valorActual);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    ResultadoMochila res;
    res.valorMaximo = dp[n][W];
    int w = W;

    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            res.seleccionados.push_back(solicitudes[i - 1]);
            w -= solicitudes[i - 1].tenure;
        }
    }

    return res;
}