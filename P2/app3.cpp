// Галиулин Р.Р. КЭз-391
// Структуры и алгоритмы обработки данных
// Практическое занятие №2

// Информационная запись о файле содержит следующие поля: каталог, имя файла, 
// расширение, дата и время создания, атрибуты «только для чтения», «скрытый», 
// «системный», количество выделенных секторов (размер сектора принять равным 
// 512 байтам). Поиск и сортировка — по каталогу, дате создания файла. 
// Выяснить, поместится ли файл на носитель с некоторым количеством секторов.

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

// Структура для хранения информации о файле
struct FileInfo {
    std::string directory; //Каталог
    std::string file_name; //Имя файла
    std::string extension; //Расширение
    std::string creation_date; //Дата создания 
    std::string creation_time; //Время создания
    bool read_only; //Параметр - Только для чтения
    bool hidden; //Параметр - Скрытый
    bool system; //Параметр - Системный
    int sectors_allocated; //Размер занимамых секторов
    FileInfo* next_file; //Указать на следующий элемент

    FileInfo(const std::string& dir, const std::string& f_name, const std::string& ext,
             const std::string& c_date, const std::string& c_time, bool r_only,
             bool hid, bool sys, int s_alloc)
        : directory(dir), file_name(f_name), extension(ext),
          creation_date(c_date), creation_time(c_time), read_only(r_only),
          hidden(hid), system(sys), sectors_allocated(s_alloc), next_file(nullptr) {}
};

// Функция очистки памяти от списка
void ClearFiles(FileInfo*& head //указать на первый элемент
               ) {
    while (head) {
        FileInfo* next = head->next_file;
        delete head;
        head = next;
    }
}

// Добавление нового файла в список
// FileInfo*& head - указать на первый элемент
void AddFile(FileInfo*& head, const std::string& directory, const std::string& file_name,
            const std::string& extension, const std::string& creation_date, const std::string& creation_time,
            bool read_only, bool hidden, bool system, int sectors_allocated) {
    FileInfo* new_file = new FileInfo(directory, file_name, extension,
                                      creation_date, creation_time, read_only, hidden, system, sectors_allocated);
    if (!head) {
        head = new_file;
    } else {
        FileInfo* temp = head;
        while (temp->next_file) {
            temp = temp->next_file;
        }
        temp->next_file = new_file;
    }
}

// Функция для сравнения дат
bool CompareDates(const std::string& date1, const std::string& date2) {
    std::istringstream ss1(date1);
    std::istringstream ss2(date2);
    std::tm tm1 = {}, tm2 = {};

    if (!(ss1 >> std::get_time(&tm1, "%d.%m.%Y"))) {
        std::cerr << "Ошибка: Неверный формат даты: " << date1 << std::endl;
        return false;
    }
    if (!(ss2 >> std::get_time(&tm2, "%d.%m.%Y"))) {
        std::cerr << "Ошибка: Неверный формат даты: " << date2 << std::endl;
        return false;
    }

    return std::mktime(&tm1) < std::mktime(&tm2);
}

// Функция сортировки
void SortFiles(FileInfo*& head, bool byDate) {
    if (!head || !head->next_file) return;

    FileInfo* sorted = nullptr;
    FileInfo* current = head;

    while (current != nullptr) {
        FileInfo* next = current->next_file;
        FileInfo** prev = &sorted;

        while (*prev != nullptr &&
               (byDate ? CompareDates((*prev)->creation_date, current->creation_date) : (*prev)->directory < current->directory)) {
            prev = &(*prev)->next_file;
        }

        current->next_file = *prev;
        *prev = current;
        current = next;
    }

    head = sorted;
}

// Функция поиска
void SearchFiles(FileInfo* head, const std::string& search_term, bool byDate) {
    FileInfo* temp = head;
    bool found = false;
    while (temp) {
        if ((byDate ? temp->creation_date == search_term : temp->directory == search_term)) {
            std::cout << "DIR: " << temp->directory
                      << ", NAME: " << temp->file_name
                      << ", EXT: " << temp->extension
                      << ", C_DATE: " << temp->creation_date
                      << ", C_TIME: " << temp->creation_time
                      << ", R: " << (temp->read_only ? "1" : "0")
                      << ", H: " << (temp->hidden ? "1" : "0")
                      << ", S: " << (temp->system ? "1" : "0")
                      << ", SIZE(512б): " << temp->sectors_allocated
                      << "\n";
            found = true;
        }
        temp = temp->next_file;
    }
    if (!found) {
        std::cout << (byDate ? "Файлы, созданные " : "Файлы в каталоге \"") << search_term << (byDate ? ", не найдены.\n" : "\" не найдены.\n");
    }
}


// Функция для вывода списка файлов
void PrintFiles(FileInfo* head) {
    FileInfo* temp = head;
    while (temp) {
        std::cout << "DIR: " << temp->directory
                  << ", NAME: " << temp->file_name
                  << ", EXT: " << temp->extension
                  << ", C_DATE: " << temp->creation_date
                  << ", C_TIME: " << temp->creation_time
                  << ", R: " << (temp->read_only ? "1" : "0")
                  << ", H: " << (temp->hidden ? "1" : "0")
                  << ", S: " << (temp->system ? "1" : "0")
                  << ", SIZE(512б): " << temp->sectors_allocated
                  << "\n";
        temp = temp->next_file;
    }
}

// Функция для проверки, поместится ли файл на носитель
bool CanFitOnDisk(int sectors_allocated, int available_sectors) {
    return sectors_allocated <= available_sectors;
}
// Функция для вывода списка файлов и проверки, поместится ли файл на носитель
void PrintFilesAndCheckFit(FileInfo* head, int available_sectors) {
    FileInfo* temp = head;
    while (temp) {
        std::cout << "Каталог: " << temp->directory
                  << ", Имя файла: " << temp->file_name
                  << ", Размер в секторах (512б): " << temp->sectors_allocated
                  << ((temp->sectors_allocated <= available_sectors) ? " - Поместится на носитель\n" : " - Не поместится на носитель\n");
        temp = temp->next_file;
    }
}

// Функция для проверки корректности даты (DD.MM.YYYY)
bool IsValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '.' || date[5] != '.') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}



int main() {
    //Добаявляем файлы
    FileInfo* files = nullptr; //Указатель на первый элемент

    AddFile(files, "/home/user/docs", "file1", ".txt", "10.01.2023", "12:00", true, false, false, 50);
    AddFile(files, "/home/user/images", "image1", ".jpg", "10.01.2022", "14:00", false, false, false, 100);
    AddFile(files, "/home/user/docs", "file2", ".docx", "09.01.2023", "10:00", false, true, false, 150);
    AddFile(files, "/home/user/music", "song1", ".mp3", "05.01.2022", "18:30", false, false, true, 200);
    AddFile(files, "/home/user/videos", "video1", ".mp4", "01.01.2023", "09:00", true, true, false, 300);

    std::cout << "Файлы до сортировки:\n";
    PrintFiles(files);

    SortFiles(files, false);
    std::cout << "Файлы после сортировки по каталогу:\n";
    PrintFiles(files);

    SortFiles(files, true);
    std::cout << "Файлы после сортировки по дате создания:\n";
    PrintFiles(files);

    int available_sectors;
    std::cout << "Введите размер носителя в секторах (512 байт): ";
    while (true) {
        std::cin >> available_sectors;
        if (std::cin.fail() || available_sectors <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите корректное целое положительное число больше нуля: ";
        } else {
            break;
        }
    }
    // Проверяем поместится ли файл на носистель с заданным размером
    PrintFilesAndCheckFit(files, available_sectors);

    //Поиск
    char search_choice;
    std::cout << "По какому параметру искать файлы? (d - по каталогу, c - по дате создания): ";
    while (true) {
        std::cin >> search_choice;
        if (search_choice != 'd' && search_choice != 'c') {
            std::cout << "Введите 'd' для поиска по каталогу или 'c' для поиска по дате создания: ";
        } else {
            break;
        }
    }

    if (search_choice == 'd') { //Поиск по каталогу
        std::string search_directory;
        std::cout << "Введите каталог для поиска: ";
        std::cin.ignore();
        std::getline(std::cin, search_directory);
        SearchFiles(files, search_directory, false);
    } else {                    //Поиск по дате создания
        std::string search_date;
        std::cout << "Введите дату создания для поиска (формат DD.MM.YYYY): ";
        std::cin.ignore();
        std::getline(std::cin, search_date);
        if (IsValidDate(search_date)) {
            SearchFiles(files, search_date, true);
        } else {
            std::cerr << "Ошибка: Неверный формат даты. Используйте формат DD.MM.YYYY" << std::endl;
        }

    }

    ClearFiles(files);
    return 0;
}
