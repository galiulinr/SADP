// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Дополнительное практическое занятие №1

// В созданном списке определить максимальное значение и удалить его.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <algorithm>

// Определение структуры узла дерева
struct TreeNode {
    int val;
    TreeNode* left;  // Указатель на левого потомка
    TreeNode* right; // Указатель на правого потомка
    TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};
// Рекурсивный подсчет суммы и количества элементов дерева
void SumAndCount(TreeNode* node, int& sum, int& count) {
    if (!node) return; // Если узел пуст
    sum += node->val; 
    count++;
    SumAndCount(node->left, sum, count); //Обходим левую часть дерева
    SumAndCount(node->right, sum, count); //Обходим правую часть дерева
}

// Генерации полного бинарного дерева
TreeNode* GenerateCompleteBinaryTree(int num_nodes) {
    if (num_nodes <= 0) return NULL; // Если узлов нету
    TreeNode* root = new TreeNode(rand() % 100); //дело случая от 0 до 100
    std::queue<TreeNode*> q;
    q.push(root);
    int current_nodes = 1;  // Счетчик добавленных узлов
    while (current_nodes < num_nodes) { // До победного
        TreeNode* node = q.front();
        q.pop();
        if (current_nodes < num_nodes) { //Левый потомок
            node->left = new TreeNode(rand() % 100);
            q.push(node->left);
            current_nodes++;
        }
        if (current_nodes < num_nodes) { //Правый потомок
            node->right = new TreeNode(rand() % 100);
            q.push(node->right);
            current_nodes++;
        }
    }
    return root;
}

// Вывода дерева с ветками псевдографики
void PrintTree(TreeNode* root, int maxVal = 0, std::string prefix = "", bool isLeft = true) {
    if (root != nullptr) {
        std::cout << prefix;
        const char* leftSymbols = "\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80";
        const char* rightSymbols = "\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80";
        const char* vSymbols = "\xE2\x94\x82   ";
        std::cout << (isLeft ? leftSymbols : rightSymbols);
        
        
            if (root->val == maxVal) {
                std::cout << "[" << root->val << "]" << std::endl; // Отмечаем максимальное значение
            } else {
               std::cout << root->val << std::endl;
            }


        PrintTree(root->left, maxVal, prefix + (isLeft ? vSymbols : "    "), true);
        PrintTree(root->right, maxVal, prefix + (isLeft ? vSymbols : "    "), false);
    }
}

// Функция для поиска максимального значения в дереве
int FindMax(TreeNode* node, int currentMax) {
    if (!node) {
        return currentMax;
    }

    currentMax = std::max(currentMax, node->val);
    currentMax = FindMax(node->left, currentMax);
    currentMax = FindMax(node->right, currentMax);

    return currentMax;
}

// Функция для удаления узла с максимальным значением. Возвращает корень модифицированного дерева
TreeNode* DeleteMax(TreeNode* root, int maxVal, bool& removed) {
     if (!root) {
        return nullptr; //Если пусто
    }
    
    if (root->val == maxVal && !removed) { 
        removed = true;
        if (!root->left && !root->right) { // Случай 1: Удаление листового узла
            delete root;
            return nullptr;
        } else if (!root->left) {  // Случай 2: Удаление узла с правым потомком
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) { // Случай 2: Удаление узла с левым потомком
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {  // Случай 3: Удаление узла с двумя потомками
             TreeNode* temp = root->left;
            while(temp->right){
                temp = temp->right;
            }
             root->val = temp->val;
            root->left = DeleteMax(root->left, temp->val, removed);
            return root;
        }
    }
    root->left = DeleteMax(root->left, maxVal, removed);
    root->right = DeleteMax(root->right, maxVal, removed);
    return root;
}

int main() {
    srand(time(0));

    int num_nodes = rand() % 29 + 2;

    // Создание полного бинарного дерева
    TreeNode* root = GenerateCompleteBinaryTree(num_nodes);

    // Подсчет суммы и количества элементов
    int sum = 0;
    int count = 0;
    SumAndCount(root, sum, count);

    double average = (double)sum / count;
    std::cout << "Среднее арифметическое: " << average << std::endl;

    int maxVal = FindMax(root, 0); // Ищем максимальное значение


    // Вывод дерева на экран
    std::cout << "Дерева до удаления:" << std::endl;
    PrintTree(root, maxVal);

    maxVal = FindMax(root, 0); // Ищем максимальное значение

    std::cout << "Максимальное значение в дереве: " << maxVal << std::endl;

    // Удаляем максимальное значение
    bool removed = false;
    root = DeleteMax(root, maxVal, removed);

    std::cout << "Дерева после удаления:" << std::endl;
    PrintTree(root);

    // Подсчет суммы и количества элементов после удаления
    sum = 0;
    count = 0;
    SumAndCount(root, sum, count);

    average = (double)sum / count;
    std::cout << "Среднее арифметическое после удаления: " << average << std::endl;

    return 0;
}
