#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Proceso {
    string nombre;
    int tLlegada;
    int tEjecucion;
    int tInicio;
    int tFinal;
    int tEspera;
};

int main() {
    int n = 5;
    vector<Proceso> procesos(n);
    procesos[0] = {"A", 2, 9};
    procesos[1] = {"B", 4, 7};
    procesos[2] = {"C", 1, 6};
    procesos[3] = {"D", 3, 2};
    procesos[4] = {"E", 6, 5};
    sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
        return a.tLlegada < b.tLlegada;
    });
    int tiempo_actual = 0;
    double tiempo_servicio_total = 0;
    double tEspera_total = 0;
    for (int i = 0; i < n; i++) {
        if (tiempo_actual < procesos[i].tLlegada) {
            tiempo_actual = procesos[i].tLlegada;
        }
        int proceso_mas_corto = i;
        for (int j = i + 1; j < n; j++) {
            if (procesos[j].tLlegada <= tiempo_actual && procesos[j].tEjecucion < procesos[proceso_mas_corto].tEjecucion) {
                proceso_mas_corto = j;
            }
        }
        swap(procesos[i], procesos[proceso_mas_corto]);
        procesos[i].tInicio = tiempo_actual;
        procesos[i].tFinal = tiempo_actual + procesos[i].tEjecucion;
        procesos[i].tEspera = procesos[i].tInicio - procesos[i].tLlegada;
        tiempo_actual = procesos[i].tFinal;
        cout << "Nombre del proceso " << i + 1 << ": " << procesos[i].nombre << endl;
        cout << "Proceso completado: " << procesos[i].tFinal << endl;
        cout << "Tiempo de servicio: " << (procesos[i].tFinal - procesos[i].tLlegada) << endl;
        cout << "Tiempo de espera: " << procesos[i].tEspera  << endl << endl;
        tiempo_servicio_total += procesos[i].tFinal - procesos[i].tLlegada;
        tEspera_total += procesos[i].tEspera;
    }
    double promedio_tiempo_servicio = tiempo_servicio_total / n;
    double promedio_tEspera = tEspera_total / n;
    cout << "Promedio de tiempo de servicio: " << promedio_tiempo_servicio << endl;
    cout << "Promedio de tiempo de espera: " << promedio_tEspera << endl;
    return 0;
}