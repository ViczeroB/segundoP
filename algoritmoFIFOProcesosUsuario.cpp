#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Proceso {
    string nombre;
    int tLlegada;
    int tCPU;
    int TFinalizar;
    int TEspera;
};

int main() {
    int nProceso;
    cout << "Ingrese el numero de procesos: ";
    cin >> nProceso;
    vector<Proceso> procesos(nProceso);
    // Solicitar información de cada proceso
    for (int i = 0; i < nProceso; ++i) {
        cout << "Proceso " << i + 1 << ":\n";
        cout << "Nombre: ";
        cin >> procesos[i].nombre;
        cout << "Tiempo de llegada: ";
        cin >> procesos[i].tLlegada;
        cout << "Tiempo en CPU: ";
        cin >> procesos[i].tCPU;
    }
    // Ordenar procesos por tiempo de llegada (en caso de empate, el primero en llegar se ejecuta primero)
    sort(procesos.begin(), procesos.end(), [](const Proceso &a, const Proceso &b) {
        return a.tLlegada < b.tLlegada;
    });
    // Simulación FIFO
    cout << "\nOrden de ejecucion de procesos (FIFO):\n";
    int tActual = 0;
    for (int i = 0; i < nProceso; ++i) {
        if (procesos[i].tLlegada > tActual) {
            tActual = procesos[i].tLlegada;
        }
        cout << "Ejecutando proceso " << procesos[i].nombre << " en el tiempo " << tActual << "\n";
        procesos[i].TEspera = tActual - procesos[i].tLlegada;
        tActual += procesos[i].tCPU;
        procesos[i].TFinalizar = tActual;
    }
    // Mostrar tiempo de espera y tiempo de finalización de cada proceso
    cout << "\nTiempo de espera y tiempo de finalizacion para cada proceso:\n";
    for (int i = 0; i < nProceso; ++i) {
        cout << "Proceso " << procesos[i].nombre << " - Tiempo de espera: " << procesos[i].TEspera << " - Tiempo de finalizacion: " << procesos[i].TFinalizar-1 << "\n";
    }
    
    int sumaTiemposEspera = 0;
    for (int i = 0; i < nProceso; ++i) {
        sumaTiemposEspera += procesos[i].TEspera;
    }
    double promedioTiemposEspera = static_cast<double>(sumaTiemposEspera) / nProceso;
    cout << "\nT.E: " << promedioTiemposEspera << endl;

    int sumaTiemposFinalizacion = 0;
    for (int i = 0; i < nProceso; ++i) {
        sumaTiemposFinalizacion += procesos[i].TFinalizar-1;
    }
    double promedioTiemposFinalizacion = static_cast<double>(sumaTiemposFinalizacion) / nProceso;
    cout << "\nT.R: " << promedioTiemposFinalizacion << endl;
    
    return 0;
}