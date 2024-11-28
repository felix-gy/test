#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Funciones auxiliares
bool solucion(int persona, int n) {
    return persona == n; // Es solución si hemos asignado todas las tareas
}

bool criterio(int beneficioActual, int& maxBeneficio) {
    return beneficioActual > maxBeneficio; // Actualizar si encontramos un mejor beneficio
}

void generar(vector<int>& asignacionActual, int persona, int tarea) {
    asignacionActual[persona] = tarea; // Asignar tarea a la persona
}

bool masHermanos(const vector<bool>& tareasAsignadas, int tarea, int n) {
    return tarea < n; // Mientras haya tareas disponibles, hay más hermanos
}

void retroceder(vector<bool>& tareasAsignadas, vector<int>& asignacionActual, int persona, int tarea) {
    tareasAsignadas[tarea] = false; // Desmarcar tarea como asignada
    asignacionActual[persona] = -1; // Deshacer la asignación
}

// Función principal de backtracking
void asignarTareasBacktracking(
    const vector<vector<int>>& beneficio, vector<bool>& tareasAsignadas,
    vector<int>& asignacionActual, int persona,
    int beneficioActual, int& maxBeneficio, vector<int>& mejorAsignacion)
{
    int n = beneficio.size();

    if (solucion(persona, n)) { // Verificar si llegamos a una solución
        if (criterio(beneficioActual, maxBeneficio)) { // Actualizar si es mejor solución
            maxBeneficio = beneficioActual;
            mejorAsignacion = asignacionActual;
        }
        return;
    }

    // Generar opciones de asignación
    for (int tarea = 0; masHermanos(tareasAsignadas, tarea, n); ++tarea) {
        if (!tareasAsignadas[tarea]) { // Si la tarea no está asignada
            generar(asignacionActual, persona, tarea); // Generar nodo hijo
            tareasAsignadas[tarea] = true; // Marcar tarea como asignada

            // Llamada recursiva
            asignarTareasBacktracking(beneficio, tareasAsignadas, asignacionActual, persona + 1,
                beneficioActual + beneficio[persona][tarea], maxBeneficio, mejorAsignacion);

            // Retroceder
            retroceder(tareasAsignadas, asignacionActual, persona, tarea);
        }
    }
}

int main() {
    // Matriz de beneficios (cambiar según el problema)
    vector<vector<int>> beneficio = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    int n = beneficio.size();
    vector<bool> tareasAsignadas(n, false);  // Para llevar registro de tareas asignadas
    vector<int> asignacionActual(n, -1);    // Asignación actual de tareas a personas
    vector<int> mejorAsignacion(n, -1);     // Mejor asignación encontrada
    int maxBeneficio = INT_MIN;             // Máximo beneficio encontrado

    // Llamada a la función de backtracking
    asignarTareasBacktracking(beneficio, tareasAsignadas, asignacionActual, 0, 0, maxBeneficio, mejorAsignacion);

    // Imprimir resultados
    cout << "Máximo beneficio: " << maxBeneficio << endl;
    cout << "Asignación óptima (persona -> tarea):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Persona " << i << " -> Tarea " << mejorAsignacion[i] << endl;
    }

    return 0;
}
