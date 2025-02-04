// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Дополнительное практическое занятие №1

// В созданном списке определить максимальное значение и удалить его.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>

// Структура для представления узла двусвязного списка
struct Node {
    int data;
    Node* prev; // Указатель на предыдущий узел
    Node* next; // Указатель на следующий узел
};

// Функция для поиска максимального элемента в списке
Node* FindMax(Node* head) {
    // Если список пуст, возвращаем nullptr
    if (head == nullptr) return nullptr;

    // Инициализируем максимальный узел и его значение начальным узлом
    Node* max_node = head;
    int max_value = head->data;

    // Проходим по списку, начиная со следующего узла
    Node* temp = head->next;
    while (temp != nullptr) {
        // Если текущий элемент больше максимального, обновляем max_node и max_value
        if (temp->data > max_value) {
            max_value = temp->data;
            max_node = temp;
        }
        temp = temp->next;
    }
    // Возвращаем указатель на узел с максимальным значением
    return max_node;
}

// Функция для удаления узла из списка
void DeleteNode(Node** list_head_ptr, Node* del) {
    // Если список пуст или узел для удаления не существует
    if (*list_head_ptr == nullptr || del == nullptr)
        return;

    // Если узел головной, то меняем указатель на голову
    if (*list_head_ptr == del)
        *list_head_ptr = del->next;

    // Если есть следующий узел, то изменяем его указатель на предыдущий
    if (del->next != nullptr)
        del->next->prev = del->prev;

    // Если есть предыдущий узел, то изменяем его указатель на следующий
    if (del->prev != nullptr)
        del->prev->next = del->next;

    // Чистим
    delete del;
}

// Функция для удаления максимального элемента из списка
void DeleteMax(Node** list_head_ptr) {
    // Если список пуст
    if (*list_head_ptr == nullptr)
        return;

    // Находим максимальный узел
    Node* max_node = FindMax(*list_head_ptr);
    // и удаляем
    DeleteNode(list_head_ptr, max_node);
}

// Функция для добавления нового узла в конец списка
void Append(Node** list_head_ptr, int new_data) {
    Node* new_node = new Node();
    Node* last = *list_head_ptr; // временный указатель для перемещения по списку

    // Записываем данные в новый узел, устанавливаем next = nullptr
    new_node->data = new_data;
    new_node->next = nullptr;

    // Если список пуст, новый узел становится головным
    if (*list_head_ptr == nullptr) {
        new_node->prev = nullptr;
        *list_head_ptr = new_node;
        return;
    }
    // Находим последний узел
    while (last->next != nullptr)
        last = last->next;

    // Привязываем новый узел к последнему узлу
    last->next = new_node;
    new_node->prev = last;
}

// Функция для вывода двусвязного списка в консоль.
// Параметр highlight_max определяет, нужно ли выделять максимальный эл.
void PrintList(Node* node, bool highlight_max) {
    // Если список пуст
    if (node == nullptr) return;

    // Определяем max_node и его значение, для выделения максимума
    Node* max_node = nullptr;
    int max_value = 0;
    if (highlight_max) {
        max_node = FindMax(node);
        max_value = (max_node != nullptr) ? max_node->data : 0;
    }

    // Проходим по списку и печатаем значения
    while (node != nullptr) {
        // максимум выводим в скобках
        if (highlight_max && node->data == max_value) {
            std::cout << "[" << node->data << "] ";
        } else {
            std::cout << node->data << " ";
        }
        node = node->next; // Переходим к следующему узлу
    }
    std::cout << std::endl;
}

// Функция для получения корректного целого числа
int get_int_from_user(const std::string& prompt) {
    int input_value;
    while (true) {
        std::cout << prompt;
        std::cin >> input_value;

        if (std::cin.fail()) {
            std::cout << "Некорректный ввод. Введите целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break; // если ввод корректен
        }
    }
    return input_value;
}

int main() {
    Node* head = nullptr; // Инициализируем голову списка nullptr
    int num_elements;

    // Получаем количество элементов
    num_elements = get_int_from_user("Введите количество элементов в списке: ");
    
    // Заполняем список данными
    for (int i = 0; i < num_elements; ++i) {
        int data = get_int_from_user("Введите целое число для элемента " + std::to_string(i + 1) + ": ");
        Append(&head, data);
    }

    std::cout << "Исходный список: ";
    PrintList(head, true);

    // Удаляем максимальный элемент
    DeleteMax(&head);

    std::cout << "Список после удаления максимального элемента: ";
    PrintList(head, false);

    return 0;
}
