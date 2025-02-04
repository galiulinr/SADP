#include <vector>
#include <iostream>
#include <random>

template <typename T>
void PrintVector(std::vector<T>& arr){
    for(T& el:arr){
        std::cout<<el<<" ";
    }
    std::cout << std::endl;
}
template <typename T>
void RandomVector(std::vector<T>& arr){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,100);
    
    for(T& el:arr){
        el =  dis(gen);
    }
}

/* Быстра сортировка */
template <typename T>
int partition(std::vector<T>& arr, size_t low, size_t high) {
    T pivot = arr[high]; 
    size_t i = (low - 1);

    for (size_t j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}
template <typename T>
void quickSort(std::vector<T>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}
template <typename T>
void quickSort(std::vector<T>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

/* Сортировка слиянием */
template <typename T>
void merge(std::vector<T>& arr, size_t left, size_t middle, size_t right) {
    size_t n1 = middle - left + 1;
    size_t n2 = right - middle;

    std::vector<T> L(n1), R(n2);

    for (size_t i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (size_t j = 0; j < n2; ++j) {
        R[j] = arr[middle + 1 + j];
    }

    size_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}
template <typename T>
void mergeSort(std::vector<T>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

template <typename T>
void mergeSort(std::vector<T>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

/* Пирамидальная сортировка */

template <typename T>
void heapify(std::vector<T>& arr, size_t n, size_t i) {
    size_t largest = i;        // Инициализируем наибольший элемент как корень
    size_t left = 2 * i + 1;   // Левый дочерний элемент
    size_t right = 2 * i + 2;  // Правый дочерний элемент

    // Если левый дочерний элемент больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый дочерний элемент больше, чем наибольший элемент на данный момент
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если наибольший элемент не корень
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Рекурсивно преобразуем в поддереве
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSort(std::vector<T>& arr) {
    size_t n = arr.size();

    // Построение пирамиды (heap)
    for (size_t i = n / 2 - 1; i != static_cast<size_t>(-1); --i) {
        heapify(arr, n, i);
    }

    // Один за другим извлекаем элементы из пирамиды
    for (size_t i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);

        // Вызываем процедуру heapify на уменьшенной пирамиде
        heapify(arr, i, 0);
    }
}

int main (){
        
    std::vector<long long int> arr(40,0);

    RandomVector(arr);
    PrintVector(arr);

    std::vector array = arr;
    std::cout << "Quick Sort: " << std::endl;
    quickSort(array);
    PrintVector(array);

    array = arr;
    std::cout << "Merge Sort: " << std::endl;
    mergeSort(array);
    PrintVector(array);

    array = arr;
    std::cout << "Heap Sort: " << std::endl;
    heapSort(array);
    PrintVector(array);
    return 0;
}
