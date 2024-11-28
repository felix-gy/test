#include <iostream>
#include <vector>
using namespace std;

// Estructura para guardar la información del problema
struct Mochila {
    int capacidad;               // Capacidad máxima de la mochila
    int n;                       // Número de objetos
    vector<int> pesos;           // Pesos de los objetos
    vector<int> beneficios;      // Beneficios de los objetos
};

// Función para verificar si una solución parcial es válida
bool criterio(const int pesoActual, const Mochila& mochila) {
    return pesoActual <= mochila.capacidad;
}

// Función para verificar si estamos en una solución completa
bool solucion(const int nivel, const Mochila& mochila) {
    return nivel == mochila.n;
}

// Función para calcular el beneficio de una solución parcial
int calcularBeneficio(const vector<bool>& seleccion, const Mochila& mochila) {
    int beneficio = 0;
    for (int i = 0; i < mochila.n; i++) {
        if (seleccion[i]) {
            beneficio += mochila.beneficios[i];
        }
    }
    return beneficio;
}

// Backtracking para resolver el problema
void mochilaBacktracking(
    const Mochila& mochila, vector<bool>& seleccion, int nivel,
    int pesoActual, int beneficioActual, int& mejorBeneficio, vector<bool>& mejorSeleccion
) {
    // Verificar si hemos alcanzado una solución completa
    if (solucion(nivel, mochila)) {
        if (beneficioActual > mejorBeneficio) {
            mejorBeneficio = beneficioActual;
            mejorSeleccion = seleccion;
        }
        return;
    }

    // Explorar inclusión del objeto en la mochila
    seleccion[nivel] = true;
    int nuevoPeso = pesoActual + mochila.pesos[nivel];
    int nuevoBeneficio = beneficioActual + mochila.beneficios[nivel];
    if (criterio(nuevoPeso, mochila)) {
        mochilaBacktracking(mochila, seleccion, nivel + 1, nuevoPeso, nuevoBeneficio, mejorBeneficio, mejorSeleccion);
    }

    // Retroceder (backtrack) y explorar exclusión del objeto
    seleccion[nivel] = false;
    mochilaBacktracking(mochila, seleccion, nivel + 1, pesoActual, beneficioActual, mejorBeneficio, mejorSeleccion);
}

// Función principal
int main() {
    Mochila mochila = { 61, 5, {1, 11, 21, 23, 33}, {11, 21, 31, 33, 43} };

    vector<bool> seleccion(mochila.n, false);
    vector<bool> mejorSeleccion(mochila.n, false);
    int mejorBeneficio = 0;

    mochilaBacktracking(mochila, seleccion, 0, 0, 0, mejorBeneficio, mejorSeleccion);

    // Mostrar el resultado
    cout << "Mejor beneficio: " << mejorBeneficio << endl;
    cout << "Objetos seleccionados: ";
    for (int i = 0; i < mochila.n; i++) {
        if (mejorSeleccion[i]) {
            cout << "Objeto " << i + 1 << " ";
        }
    }
    cout << endl;

    return 0;
}
