#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> table_mochila(int n, int m, vector<int> peso, vector<int>  benefi) {
    vector<int> solucion(n);
    n++;
    m++;
    int** matrix = new int* [n]; // row
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = new int[m]; // Col
        for (int j = 0; j < m; ++j)
        {
            matrix[i][j] = 0;
        }
    }
    n--;
    m--;
    // Llenamos la tabla
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j - peso[i - 1] >= 0)
            {
                matrix[i][j] = (matrix[i - 1][j], benefi[i - 1] + matrix[i - 1][j - peso[i - 1]]);
            }
            else
            {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }

    // Recomponer la solución optima
    int j = m;
    for (int i = n; i >= 1; i--)
    {
        if (matrix[i][j] == matrix[i - 1][j])
        {
            solucion[i - 1] = 0;
        }
        else
        {
            solucion[i - 1] = 1;
            j = j - peso[i - 1];
        }
    }

    n++;
    m++;
    cout << "Tabla:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;

    return solucion;
}

int main()
{
    int n = 3;
    int m = 6;
    vector<int>  pesos = { 2, 3, 4 };
    vector<int> beneficio = { 1, 2, 5 };

    cout << "n = " << n << endl;
    cout << "m = " << m << endl;
    cout << "pesos: " << endl; ;
    for (auto& p : pesos)
    {
        cout << p << " ";
    }
    cout << endl;
    cout << "beneficios: " << endl; ;
    for (auto& p : beneficio)
    {
        cout << p << " ";
    }
    cout << endl;

    vector<int> sol = table_mochila(3, 6, pesos, beneficio);
    cout << "Vector solucion: " << endl;
    for (auto& i : sol)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}