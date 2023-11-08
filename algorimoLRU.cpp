#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

// Función para imprimir un vector
void imprimirVector(const vector<int>& vec) {
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vector<int> procesos;
    vector<int> paginas;
    unordered_map<int, int> paginaTimestamp;  // Mapa para rastrear el tiempo de acceso de cada página
    int tamanoProcesos = 0;
    int tamanoPaginas = 0;
    int pageDefaults = 0;
    int pageHits = 0;
    int timestamp = 0;  // Variable para rastrear el tiempo de acceso

    cout << "Ingrese el tamaño del vector de procesos (debe ser mayor que el tamaño del vector de paginas): ";
    cin >> tamanoProcesos;
    cout << "Ingrese el tamaño del vector de paginas: ";
    cin >> tamanoPaginas;

    if (tamanoProcesos <= tamanoPaginas) {
        cout << "El tamaño del vector de procesos debe ser mayor que el tamaño del vector de paginas." << endl;
        return 1;
    }

    // Llenar el vector de procesos con números ingresados por el usuario
    cout << "Ingrese los números para el vector de procesos:" << endl;
    for (int i = 0; i < tamanoProcesos; i++) {
        int numero;
        cin >> numero;
        procesos.push_back(numero);
    }

    // Simulación de la estrategia de reemplazo de páginas LRU
    for (int i = 0; i < tamanoProcesos; i++) {
        int pagina = procesos[i];
        if (paginaTimestamp.find(pagina) == paginaTimestamp.end()) {
            // Página no en memoria, se agrega y se actualiza el tiempo de acceso
            if (paginas.size() >= tamanoPaginas) {
                // Si se excede el tamaño máximo, se busca la página LRU
                int paginaLRU = paginas[0];
                int lruTimestamp = paginaTimestamp[paginaLRU];
                for (int j = 1; j < paginas.size(); j++) {
                    if (paginaTimestamp[paginas[j]] < lruTimestamp) {
                        paginaLRU = paginas[j];
                        lruTimestamp = paginaTimestamp[paginaLRU];
                    }
                }
                // Se elimina la página LRU
                paginas.erase(remove(paginas.begin(), paginas.end(), paginaLRU), paginas.end());
                paginaTimestamp.erase(paginaLRU);
            }
            paginas.push_back(pagina);
            paginaTimestamp[pagina] = timestamp;
            pageDefaults++;
        } else {
            // Página en memoria, se actualiza el tiempo de acceso
            paginaTimestamp[pagina] = timestamp;
            pageHits++;
        }
        timestamp++;  // Aumentar el tiempo de acceso en cada iteración
    }

    cout << "Vector de procesos: ";
    imprimirVector(procesos);
    cout << "Vector de paginas: ";
    imprimirVector(paginas);

    cout << "Número de page defaults: " << pageDefaults << endl;
    cout << "Número de page hits: " << pageHits << endl;

    double porcentajePageMiss = (static_cast<double>(pageDefaults) / tamanoProcesos) * 100.0;
    double porcentajePageHit = (static_cast<double>(pageHits) / tamanoProcesos) * 100.0;

    cout << "Porcentaje de page miss: " << porcentajePageMiss << "%" << endl;
    cout << "Porcentaje de page hit: " << porcentajePageHit << "%" << endl;

    double sumaPorcentajes = porcentajePageMiss + porcentajePageHit;
    cout << "Suma del porcentaje de page miss y page hit: " << sumaPorcentajes << "%" << endl;

    return 0;
}
