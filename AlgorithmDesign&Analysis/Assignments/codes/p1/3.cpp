/*
 * 实现QuickSort
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void randomizePivot(std::vector<int>& arr, int low, int high) {
    int random = low + rand() % (high - low);
    std::swap(arr[random], arr[high]);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        randomizePivot(arr, low, high);
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(nullptr));

    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    quickSort(arr, 0, n - 1);

    for(int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}



