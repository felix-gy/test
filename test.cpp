#include <iostream>
#include <vector>

void merge(std::vector<int>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            vec[k++] = L[i++];
        else
            vec[k++] = R[j++];
    }
    while (i < n1)
        vec[k++] = L[i++];
    while (j < n2)
        vec[k++] = R[j++];
}

void mergeSort(std::vector<int>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}
// quicksort
int partition(std::vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (vec[j] < pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

void quickSort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}


/*
int main() {
    std::vector<int> vec = {9, 1, 3, 5, 0, 4, 2, 6, 8, 7};
    mergeSort(vec, 0, vec.size() - 1);

    std::cout << "Vector ordenado con Mergesort: ";
    for (int v : vec) std::cout << v << " ";
    return 0;
}
*/



#include <iostream>
#include <vector>
#include <algorithm>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    std::copy(temp.begin(), temp.end(), arr.begin() + left);
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/*
int main() {
    std::vector<int> arr = {9, 3, 7, 5, 1, 6, 4, 8, 2};
    mergeSort(arr, 0, arr.size() - 1);
    for (int x : arr) std::cout << x << " ";
    return 0;
}
*/

#include <iostream>
#include <vector>
#include <algorithm>

int minimumCoins(int amount, std::vector<int>& coins) {
    std::sort(coins.rbegin(), coins.rend()); // Orden descendente para greedy
    int totalCoins = 0;
    for (int coin : coins) {
        if (amount == 0) break;
        totalCoins += amount / coin;
        amount %= coin;
    }
    return amount == 0 ? totalCoins : -1; // -1 si no es posible
}

/*
int main() {
    std::vector<int> coins = {1, 5, 10, 25};
    int amount = 63;
    int result = minimumCoins(amount, coins);
    if (result != -1) std::cout << "Mínimo de monedas: " << result << '\n';
    else std::cout << "No se puede lograr con las monedas disponibles.\n";
    return 0;
}
*/
