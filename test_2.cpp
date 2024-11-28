#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para representar un objeto con peso y beneficio
struct Item {
    int weight;
    int benefit;
};

// Funci�n para calcular el beneficio m�ximo mediante backtracking
void knapsackBacktrack(int index, int currentWeight, int currentBenefit,
    int& maxBenefit, const vector<Item>& items, int capacity) {
    // Caso base: hemos procesado todos los elementos
    if (index == items.size()) {
        // Actualizamos el beneficio m�ximo si es mejor
        maxBenefit = max(maxBenefit, currentBenefit);
        return;
    }

    // Caso 1: No incluir el objeto actual
    knapsackBacktrack(index + 1, currentWeight, currentBenefit, maxBenefit, items, capacity);

    // Caso 2: Incluir el objeto actual (si cabe en la mochila)
    if (currentWeight + items[index].weight <= capacity) {
        knapsackBacktrack(index + 1, currentWeight + items[index].weight,
            currentBenefit + items[index].benefit, maxBenefit, items, capacity);
    }
}

// Funci�n principal para inicializar y ejecutar el algoritmo
int solveKnapsack(const vector<Item>& items, int capacity) {
    int maxBenefit = 0;
    knapsackBacktrack(0, 0, 0, maxBenefit, items, capacity);
    return maxBenefit;
}

// Funci�n para leer datos y ejecutar el programa
void runKnapsack() {
    int capacity = 61; // Capacidad de la mochila
    vector<Item> items = {
        {1, 11},
        {11, 21},
        {21, 31},
        {23, 33},
        {33, 43}
    };

    int maxBenefit = solveKnapsack(items, capacity);
    cout << "El beneficio m�ximo que se puede obtener es: " << maxBenefit << endl;
}

int main() {
    runKnapsack();
    return 0;
}
