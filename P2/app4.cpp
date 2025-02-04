#include <iostream>
#include <stack>
#include <limits>

// Функция печати стека
void PrintStack(const std::stack<int>& stack) {
    std::stack<int> temp_stack = stack;
    while (!temp_stack.empty()) {
        std::cout << temp_stack.top() << " ";
        temp_stack.pop();
    }
    std::cout << std::endl;
}

int main() {
    int count, sum = 0, product = 1;
    std::stack<int> oper_stack; // Основной стек
    std::stack<int> temp_stack; // Стек для операции

    std::cout << "Введите количество элементов: ";
    std::cin >> count;

    // Проверка корректности введенного количества элементов
    while (count <= 0) {
        std::cerr << "Ошибка: количество элементов должно быть положительным числом. Попробуйте еще раз: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> count;
    }

    std::cout << "Введите элементы: ";
    for (int i = 0; i < count; ++i) {
        int element;
        std::cin >> element;

        // Проверка корректности введенного элемента
        while (std::cin.fail()) {
            std::cerr << "Ошибка: введено некорректное значение. Попробуйте еще раз: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> element;
        }

        oper_stack.push(element);
    }

    std::cout << "Начальный стек: ";
    PrintStack(oper_stack);

    // Извлечение элементов из стека во временный стек,
    // нахождение их суммы и произведения
    while (!oper_stack.empty()) {
        int top_element = oper_stack.top();
        sum += top_element;
        product *= top_element;
        temp_stack.push(top_element);
        oper_stack.pop();
    }

    // Возвращаем первоначальные элементы обратно в основной стек
    while (!temp_stack.empty()) {
        oper_stack.push(temp_stack.top());
        temp_stack.pop();
    }

    // Помещаем результат в стек
    oper_stack.push(sum);
    oper_stack.push(product);

    std::cout << "Сумма: " << sum << std::endl;
    std::cout << "Произведение: " << product << std::endl;

    std::cout << "Конечный стек: ";
    PrintStack(oper_stack);

    return 0;
}
