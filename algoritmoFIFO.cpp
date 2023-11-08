#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
// Función para imprimir un vector
void imprimirVector(const vector<int>& vec) { 
    for (int i : vec) { 
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    srand(time(NULL)); 
    vector<int> procesos; 
    vector<int> paginas;
    int tamanoProcesos = 0;
    int tamanoPaginas = 0;
    cout << "Ingrese el tamaño del vector de procesos (debe ser mayor que el tamaño del vector de paginas): ";
    cin >> tamanoProcesos;
    cout << "Ingrese el tamaño del vector de paginas: ";
    cin >> tamanoPaginas;
    if (tamanoProcesos <= tamanoPaginas) {
        cout << "El tamaño del vector de procesos debe ser mayor que el tamaño del vector de paginas." << endl;
        return 1;
    }
    // Llenar el vector de procesos con numeros aleatorios
    for (int i = 0; i < tamanoProcesos; i++) { 
        procesos.push_back(rand() % 10); 
    }
    // Llenar el vector de paginas
    for (int i = 0; i < tamanoProcesos; i++) {
        int pagina = procesos[i];
        if (find(paginas.begin(), paginas.end(), pagina) == paginas.end()) {
            paginas.push_back(pagina);
            if (paginas.size() > tamanoPaginas) {
                paginas.erase(paginas.begin());
            }
        }
    }
    // Imprimir los vectores de procesos y paginas
    cout << "Vector de procesos: ";
    imprimirVector(procesos);
    cout << "Vector de paginas: ";
    imprimirVector(paginas);
    // Imprimir el numero de page defaults
    cout << "Numero de page defaults: " << tamanoProcesos - paginas.size() << endl;
    // Imprimir el numero de page hits
    cout << "Numero de page hits: " << paginas.size() << endl;
    //imprimir el porcentaje de page miss y page hit
    cout << "Porcentaje de page miss: " << (tamanoProcesos - paginas.size()) * 100 / tamanoProcesos << "%" << endl;
    cout << "Porcentaje de page hit: " << paginas.size() * 100 / tamanoProcesos << "%" << endl;
    //imprimir la suma del porcentaje de page miss y page hit
    cout << "Suma del porcentaje de page miss y page hit: " << (tamanoProcesos - paginas.size()) * 100 / tamanoProcesos + paginas.size() * 100 / tamanoProcesos << "%" << endl;
    
    return 0;
}
