// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Дополнительное практическое занятие №3

// Найти маршрут обхода конем шахматной доски, заданных размеров, из заданного 
// начального положения коня.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

// представляет все возможные ходы коня на шахматной доске.
const int moves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

// Проверяет, является ли ход допустимым.
bool IsValidMove(int x, int y, int M, int N, 
                 const std::vector<std::vector<int>>& board) 
{
    return (x >= 0 && x < M && y >= 0 && y < N && board[x][y] == 0);
}

// Количество допустимых ходов из текущей позиции.
int CountValidMoves(int x, int y, int M, int N, 
                    const std::vector<std::vector<int>>& board) {
    int count = 0;
    for (const auto& move : moves) {
        int nx = x + move[0];
        int ny = y + move[1];
        if (IsValidMove(nx, ny, M, N, board)) {
            count++;
        }
    }
    return count;
}

// обход конём шахматной доски с использованием метода Варнсдорфа.
bool SolveKnightTour(int x, int y, int move_count, int M, int N, 
                     std::vector<std::vector<int>>& board) {
    if (move_count == M * N + 1) return true; // Проверяет завершение обхода всей доски.

    std::vector<std::pair<int, std::pair<int, int>>> next_moves;

    for (const auto& move : moves) {
        int nx = x + move[0];
        int ny = y + move[1];
        if (IsValidMove(nx, ny, M, N, board)) {
            int valid_moves = CountValidMoves(nx, ny, M, N, board);
            next_moves.push_back({valid_moves, {nx, ny}});
        }
    }
    // Сортирует ходы
    std::sort(next_moves.begin(), next_moves.end(),
          [](auto &a, auto &b) { return a.first < b.first; });

    for (const auto& next_move : next_moves) {
        int nx = next_move.second.first;
        int ny = next_move.second.second;
        board[nx][ny] = move_count;
        if (SolveKnightTour(nx, ny, move_count + 1, M, N, board)) return true;
        board[nx][ny] = 0; // backtracking
    }

    return false;
}

// Записывает текущее состояние доски в выходной файл и на консоль.
void PrintBoard(std::ofstream& output_file, 
                const std::vector<std::vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            output_file << std::setw(3) << cell << " ";
            std::cout << std::setw(3) << cell << " ";
        }
        output_file << std::endl;
        std::cout << std::endl;
    }
}

// Извлекает входные данные
int ParseValue(const std::string& str) {
    size_t pos = str.find('=');
    if (pos != std::string::npos) {
        return stoi(str.substr(pos + 1));
    }
    return -1;
}

int main() {
    std::ifstream input_file("input.txt");
    std::ofstream output_file("output.txt");

    if (!input_file || !output_file) {
        std::cerr << "Не удалось открыть файл." << std::    endl;
        return 1;
    }

    std::string line;
    getline(input_file, line);
    std::stringstream ss(line);

    std::string m_str, n_str, x_str, y_str;
    ss >> m_str >> n_str >> x_str >> y_str;

    int M = ParseValue(m_str);
    int N = ParseValue(n_str);
    int X = ParseValue(x_str);
    int Y = ParseValue(y_str);

    std::cout << "Входные данные:" << std::endl;
    std::cout << "M = " << M << ", N = " << N << ", X = " << X << ", Y = " 
              << Y << std::endl;

    // Проверяет корректность входных данных.
    if (input_file.fail() || M <= 0 || N <= 0 || X <= 0 || Y <= 0 || X > M || Y > N) {
        std::cerr << "Некорректные входные данные" << std::endl;
        return 1;
    }

    // Предупреждение для больших размеров доски.
    if (M * N > 1000) {
        std::cerr << "Предупреждение: большие размеры доски могут замедлить "
                      "выполнение программы." << std::endl;
    }

    std::vector<std::vector<int>> board(M, std::vector<int>(N, 0));
    board[X - 1][Y - 1] = 1; // Начальная позиция.

    // Запускает решение
    if (SolveKnightTour(X - 1, Y - 1, 2, M, N, board)) {
        std::cout << "Решение найдено:" << std::endl;
        PrintBoard(output_file, board);
    } else {
        std::cout << "Маршрут не существует" << std::endl;
        output_file << "Маршрут не существует" << std::endl;
    }

    input_file.close();
    output_file.close();

    return 0;
}
