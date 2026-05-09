#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

#include "solicitud.hpp"
#include "parser.hpp"
#include "mergesort.hpp"
#include "busqueda.hpp"
#include "grafo.hpp"
#include "unionfind.hpp"
#include "mochila.hpp"

using namespace std;
using namespace chrono;

void guardarCSV(const vector<Solicitud>& datos, string ruta) {
    ofstream archivo(ruta);
    archivo << "customerID,tenure,MonthlyCharges,TotalCharges,Churn\n";
    for (const auto& s : datos) {
        archivo << s.customerID << "," << s.tenure << "," << s.monthlyCharges
                << "," << s.totalCharges << "," << (s.churn ? "Yes" : "No") << "\n";
    }
    archivo.close();
}

void generarVisualizacionDOT(const vector<Arista>& mst, string ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    
    archivo << "graph G {" << endl;
    archivo << "    node [shape=circle, style=filled, fillcolor=lightblue];" << endl;

    for (const auto& arista : mst) {
    
        archivo << "    " << arista.origen << " -- " << arista.destino
                << " [label=\"" << arista.peso << "\", color=blue, penwidth=2];" << endl;
    }

    archivo << "}" << endl;
    archivo.close();
    cout << "Archivo DOT generado: " << ruta << endl;
}

int main() {

    cout << "\n--- Modulo A ---" << endl;


    vector<Solicitud> datos = cargarCSV("../data/WA_Fn-UseC_-Telco-Customer-Churn.csv");
    if (datos.empty()) return 1;

    
    auto inicio = high_resolution_clock::now();
    mergeSort(datos, 0, datos.size() - 1);
    auto fin = high_resolution_clock::now();

    duration<double, milli> tiempo = fin - inicio;
    cout << "Ordenamiento MergeSort: " << tiempo.count() << " ms" << endl;

    
    guardarCSV(datos, "../results/solicitudes_ordenadas.csv");

    
    vector<int> consultas = {72, 60, 45, 30, 12};
    ofstream reporteBusqueda("results/busquedas_A.txt");

    cout << "\n--- Resultados de Busqueda Binaria ---" << endl;
    reporteBusqueda << "Resultados de Busqueda para k meses:\n";

    for (int k : consultas) {
        int indice = busquedaBinariaR(datos, 0, datos.size() - 1, k);
        if (indice != -1) {
            string res = "Para k=" + to_string(k) + ", cliente: " + datos[indice].customerID + " (Tenure: " + to_string(datos[indice].tenure) + ")";
            cout << res << endl;
            reporteBusqueda << res << "\n";
        }
    }
    reporteBusqueda.close();

    cout << "\nArchivos generados en la carpeta /results" << endl;

    cout << "\n--- Modulo B: Red de Fibra Optica (MST) ---" << endl;

    int numNodos = 20;
    vector<Arista> todasLasAristas = generarGrafo(numNodos);

    
    sort(todasLasAristas.begin(), todasLasAristas.end());

    
    UnionFind uf(numNodos);
    vector<Arista> mst;
    double costoTotal = 0;

    for (const auto& arista : todasLasAristas) {
        if (uf.buscar(arista.origen) != uf.buscar(arista.destino)) {
            uf.unir(arista.origen, arista.destino);
            mst.push_back(arista);
            costoTotal += arista.peso;
        }
    }

    cout << "Costo total de la red: " << costoTotal << " USD" << endl;
    cout << "Conexiones realizadas: " << mst.size() << endl;

    ofstream archivoMST("../results/mst_red.txt");
    if (archivoMST.is_open()) {
        archivoMST << "--- REPORTE DE RED DE FIBRA OPTICA (MST) ---" << endl;
        archivoMST << "Costo Total: " << costoTotal << " USD" << endl;
        archivoMST << "Numero de conexiones: " << mst.size() << endl;
        archivoMST << "--------------------------------------------" << endl;
        archivoMST << "Origen\tDestino\tCosto" << endl;

        for (const auto& arista : mst) {
            archivoMST << arista.origen << "\t" << arista.destino << "\t" << arista.peso << " USD" << endl;
        }
        archivoMST.close();
        cout << "Reporte MST generado en results/mst_red.txt" << endl;
    } else {
        cout << "Error: No se pudo crear el archivo de reporte del MST." << endl;
    }

    generarVisualizacionDOT(mst, "../results/red_visual.dot");

    cout << "\n--- Modulo C: Asignacion de Ancho de Banda (DP) ---" << endl;

    
    vector<Solicitud> solicitudesFiltradas;
    for (const auto& s : datos) {
        if (!s.churn) { 
            solicitudesFiltradas.push_back(s);
        }
        if (solicitudesFiltradas.size() == 50) break;
    }

    
    int W = 500;
    ResultadoMochila resultado = resolverMochila(solicitudesFiltradas, W);

    
    cout << "Ingreso maximo calculado: " << resultado.valorMaximo << " USD" << endl;
    cout << "Clientes seleccionados para el ancho de banda: " << resultado.seleccionados.size() << endl;

    ofstream archivoC("../results/asignacion_bw.txt");
    if (archivoC.is_open()) {
        archivoC << "--- REPORTE ASIGNACION ANCHO DE BANDA ---" << endl;
        archivoC << "Capacidad Total (W): " << W << endl;
        archivoC << "Beneficio Maximo: " << resultado.valorMaximo << " USD" << endl;
        archivoC << "Clientes Seleccionados:" << endl;
        for (const auto& s : resultado.seleccionados) {
            archivoC << "ID: " << s.customerID << " | Tenure: " << s.tenure
                     << " | Mensualidad: " << s.monthlyCharges << " USD" << endl;
        }
        archivoC.close();
        cout << "Reporte del Modulo C generado en results/asignacion_bw.txt" << endl;
    }

    // --- BLOQUE DE VALIDACIÓN DE DATOS ---
    int totalRegistros = datos.size();
    int nulosTotalCharges = 0;
    int churnNo = 0;
    int maxTenure = -1;
    int minTenure = 999;
    double sumaMonthly = 0;

    for (const auto& s : datos) {
        if (s.totalCharges == 0 && s.tenure == 0) nulosTotalCharges++; 
        if (!s.churn) churnNo++;
        if (s.tenure > maxTenure) maxTenure = s.tenure;
        if (s.tenure < minTenure) minTenure = s.tenure;
        sumaMonthly += s.monthlyCharges;
    }

    cout << "\n=== Verificacion de Referencia ===" << endl;
    cout << "Total registros: " << totalRegistros << " (Ref: 7,043)" << endl;
    cout << "Nulos TotalCharges: " << nulosTotalCharges << " (Ref: 11)" << endl;
    cout << "Churn = No: " << churnNo << " (Ref: 5,174)" << endl;
    cout << "Tenure Max: " << maxTenure << " (Ref: 72)" << endl;
    cout << "Tenure Min: " << minTenure << " (Ref: 0)" << endl;
    cout << "Monthly promedio: " << (sumaMonthly / totalRegistros) << " (Ref: 64.76)" << endl;
    cout << "==================================\n" << endl;

    return 0;
}
