// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Практическое занятие №1

// Отфильтровать из строки числа
// Вводится строка, содержащая буквы, целые неотрицательные числа и 
// иные символы. 
// Требуется все числа, которые встречаются в строке, поместить в отдельный 
// целочисленный массив. Например, если дана строка 
// «data 48 call 9 read13 blank0a»,
// то в массиве должны оказаться числа 48, 9, 13 и 0.

#include <iostream>
#include <string>
#include <vector>
#include <cctype>


std::vector<int> extract_numbers_from_string(const std::string& str) {
/*Функция извлечения чисел из строки*/
    std::vector<int> extract_numbers;
    std::string temp_number;

    for (char c : str) {
        if (std::isdigit(c)) {
            temp_number += c;
        } else {
            if (!temp_number.empty()) {
                extract_numbers.push_back(std::stoi(temp_number));
                temp_number.clear();
            }
        }
    }

    // Добавиление последнего числа, если строка оканчивается числом
    if (!temp_number.empty()) {
        extract_numbers.push_back(std::stoi(temp_number));
    }

    return extract_numbers;
}

int main() {
    std::cout <<"Числа, которые встречаются в строке, поместить в отдельный "
                "целочисленный массив" << std::endl;

    std::string input;
    std::cout << "Введите строку: ";
    std::getline(std::cin, input);

    std::vector<int> numbers = extract_numbers_from_string(input);

    std::cout << "Извлеченные числа: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

