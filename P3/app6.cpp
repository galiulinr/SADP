// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Практическое занятие №3

// Дана очередь вещественных чисел. Удалить из очереди числа из заданного 
// пользователем диапазона.

#include <iostream>
#include <queue>
#include <sstream>
#include <string>

int main() {
    std::queue<double> numbers_queue;
    std::string input;
    double number;

    // Ввод данных единой строкой
    std::cout << "Введите числа для очереди через пробел (нажмите Enter для"
                 "завершения ввода): ";
    std::getline(std::cin, input);
    std::istringstream iss(input);

    while (iss >> number) {
        numbers_queue.push(number);
    }

    // Вывод очереди перед удалением
    std::queue<double> copy_numbers_queue = numbers_queue;
    std::cout << "Очередь перед удалением: ";
    while (!copy_numbers_queue.empty()) {
        std::cout << copy_numbers_queue.front() << " ";
        copy_numbers_queue.pop();
    }
    std::cout << std::endl;

    // Ввод диапазона
    double lower_bound, upper_bound;
    std::cout << "Введите нижнюю границу диапазона: ";
    std::cin >> lower_bound;
    std::cout << "Введите верхнюю границу диапазона: ";
    std::cin >> upper_bound;

    // Удаление элементов из очереди
    std::queue<double> filtered_mumbers_queue;
    while (!numbers_queue.empty()) {
        double current = numbers_queue.front();
        numbers_queue.pop();
        if (current < lower_bound || current > upper_bound) {
            filtered_mumbers_queue.push(current);
        }
    }

    // Вывод результата
    std::cout << "Очередь после удаления чисел из заданного диапазона: ";
    while (!filtered_mumbers_queue.empty()) {
        std::cout << filtered_mumbers_queue.front() << " ";
        filtered_mumbers_queue.pop();
    }

    return 0;
}

