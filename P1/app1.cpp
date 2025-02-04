//
// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Практическое занятие №1

// Дан одномерный целочисленный массив порядка N. Найдите сумму положительных 
// элементов массива, стоящих между первым и последним отрицательными 
// элементами. 
// Если таких элементов нет, вернуть значение 0.

#include <iostream>
#include <vector>
#include <limits>

int SumBetweenNegatives(const std::vector<int>& arr) {
// Функция возвращает сумму положительных элементов массива, между первым и посденим отрицательными элементами
    
    int first_negative_idx = -1;
    int last_negative_idx = -1;
    int sum_positive = 0;

    // Находим индексы первого и последнего отрицательных элементов
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] < 0) {
            if (first_negative_idx == -1) {
                first_negative_idx = i;
            }
            last_negative_idx = i;
        }
    }

    // Если в массиве нет отрицательных элементов или они расположены так, что 
    // между ними нет положительных элементов
    if (first_negative_idx == -1 || last_negative_idx == -1 || 
        first_negative_idx >= last_negative_idx) {
        return 0;
    }

    // Суммируем положительные элементы между первым и последним отрицательными 
    // элементами
    for (int i = first_negative_idx + 1; i < last_negative_idx; ++i) {
        if (arr[i] > 0) {
            sum_positive += arr[i];
        }
    }

    return sum_positive;
}

int main() {
   int n; //Кол-во элементов массива

    std::cout << "Сумма положительных элементов между первым и последним "<< 
    "отрицательными элементами" << std::endl;

    // Проверка ввода размера массива
    do {
        std::cout << "Введите положительное целое число для длины массива: ";
        std::cin >> n;
        if (std::cin.fail() || n <= 0) {
            std::cin.clear(); // Очистка флага ошибки
            // Игнорирование некорректного ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
        }
    } while (n <= 0);

    std::vector<int> arr(n);

    // Проверка ввода только целых чисел для элементов массива
    std::cout << "Введите элементы массива: " << std::endl;
    for (int i = 0; i < n; ++i) {
        while (true) {
            std::cout << "Элемент " << i + 1 << ": ";
            std::cin >> arr[i];
            if (std::cin.fail()) {
                std::cin.clear(); // Очистка флага ошибки
                // Игнорирование некорректного ввода
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Некорректный ввод. Введите целое число: ";
            } else {
                break; // Корректный ввод
            }
        }
    }

    int result = SumBetweenNegatives(arr);
    std::cout << "Сумма положительных элементов между первым и последним"
     "отрицательными элементами: " << result << std::endl;

    return 0;
}

