// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Практическое занятие №4

// Отсортировать одномерный массив вещественных чисел размерности n, 
// применив сортировки бинарным включением и шейкерную.

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

//Печать массива
void PrintArray(const std::vector<double>& arr) {
    for (double num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Функция бинарного поиска для нахождения позиции вставки
// arr - отсортированный массив, в который вставляется элемент
// value - вставляемое значение
// start - начальный индекс диапазона поиска
// end - конечный индекс диапазона поиска
int BinarySearch(const std::vector<double>& arr, double value, 
                  int start, int end) {
    while (start <= end) {
        int mid = start + (end - start) / 2; // Находим середину
        if (arr[mid] == value) { 
            return mid; // Если угадали сразу
        } else if (arr[mid] < value) { //Определяем в правой или левой части
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return start; //Индекс, куда нужно вставить значение
}

/// Сортировка бинарным включением
// arr - массив для сортировки
void BinarySort(std::vector<double>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        double value = arr[i]; // Текущий элемент для вставки
        int j = BinarySearch(arr, value, 0, i - 1); // Находим куда вставить
        arr.erase(arr.begin() + i); // Удаляем элемент с текущей позиции
        arr.insert(arr.begin() + j, value); // Вставляем элемент в найденную позицию
    }
}

// Шейкерная сортировка
// arr - массив для сортировки
void ShakerSort(std::vector<double>& arr) {
    int left = 0; // Левая граница
    int right = arr.size() - 1; //Правая граница
    while (left < right) {
        // Идем слева на право - подымаем максимальный эелемент
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
            }
        }
        --right; //Подняли и  больше не задействуем
        for (int i = right; i > left; --i) {
        // Идем справа на лево - опускаем минимальный элемент
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
            }
        }
        ++left; // Опустили и больше не задействуем
    }
}

int main() {
    int n;
    std::cout << "Введите размер массива: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Введите корректное положительное число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::vector<double> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "Введите элемент " << i + 1 << ": ";
        while (!(std::cin >> arr[i])) {
            std::cout << "Введите корректное вещественное число для элемента " 
                      << i + 1 << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Исходный массив перед сортировкой
    std::cout << "Оригинальный массив: ";
    PrintArray(arr);

    // Сортировка бинарными включениями
    std::vector<double> arr_binary = arr;
    auto start = std::chrono::high_resolution_clock::now();
    BinarySort(arr_binary);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Массив после сортировки бинарными включениями: ";
    PrintArray(arr_binary);
    std::cout << "Время выполнения бинарной сортировки: " << elapsed.count() 
              << " секунд" << std::endl;

    // Сортировка шейкерная
    std::vector<double> arr_shaker = arr;
    start = std::chrono::high_resolution_clock::now();
    ShakerSort(arr_shaker);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Массив после шейкерной сортировки: ";
    PrintArray(arr_shaker);
    std::cout << "Время выполнения шейкерной сортировки: " << elapsed.count() 
         << " секунд" << std::endl;

    return 0;
}

