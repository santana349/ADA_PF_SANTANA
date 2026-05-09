# ADA_PF_SANTANA
# Análisis de Algoritmos

Este proyecto implementa una solución integral para la gestión, infraestructura y optimización económica de una red de fibra óptica utilizando tres paradigmas algorítmicos fundamentales: Divide y Vencerás, Algoritmos Codiciosos y Programación Dinámica.

## Estructura del Proyecto

El proyecto está organizado de la siguiente manera:
- `src/`: Archivos fuente (.cpp y .hpp).
- `data/`: Dataset original de clientes (CSV).
- `results/`: Archivos generados (CSV ordenado, Reporte MST, Asignación de Ancho de Banda y Visualización DOT).
- `report/`: Informe técnico en PDF.

## 🛠️ Tecnologías Utilizadas
- **Lenguaje:** C++17
- **Entorno de Desarrollo:** CLion
- **Sistema de Construcción:** CMake
- **Visualización:** Graphviz (para archivos .dot)

## Compilación y Ejecución

### Desde CLion (Recomendado)
1. Abre CLion y selecciona **Open**.
2. Busca la carpeta raíz del proyecto (donde se encuentra el archivo `CMakeLists.txt`).
3. CLion cargará automáticamente la configuración de CMake.
4. Asegúrate de que el "Working Directory" esté configurado correctamente para que el programa encuentre la carpeta `data/`:
   - Ve a `Run` > `Edit Configurations`.
   - En **Working Directory**, selecciona la carpeta raíz del proyecto.
5. Haz clic en el botón **Run** (el triángulo verde).

### Desde Terminal (Alternativa con CMake)
Si deseas ejecutarlo fuera de CLion:

# 1. Compilación
g++ -std=c++17 -O2 -o ada_pf src/main.cpp src/*.cpp

# 2. Ejecución (Pasando la ruta del dataset como argumento)
./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv
