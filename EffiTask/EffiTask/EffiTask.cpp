#include <iostream>     
#include <string>       
#include <vector>       
#include <windows.h>    
using namespace std;

// Структура для хранения информации о задаче
struct Task {
    int id;             // Уникальный идентификатор задачи
    string name;        // Название задачи
    string deadline;    // Срок выполнения
    int priority;       // Приоритет (1-низкий, 2-средний, 3-высокий)
};

// Основной класс для управления задачами
class TaskManager {
private:
    vector<Task> tasks;     // Вектор для хранения всех задач
    int nextId;             // Счетчик для генерации уникальных ID

    // Вспомогательная функция для очистки буфера ввода
    void clearInput() {
        cin.clear();
        cin.ignore(32767, '\n');
    }

    // Вспомогательная функция для безопасного ввода строк
    string safeInput() {
        string input;
        getline(cin, input);
        return input;
    }

public:
    // Конструктор класса
    TaskManager() {
        nextId = 1;     // Начинаем нумерацию задач с 1
    }

    // Функция для добавления новой задачи
    void addTask() {
        Task newTask;
        newTask.id = nextId++;    // Присваиваем уникальный ID и увеличиваем счетчик

        cout << "\n--- Добавление новой задачи ---\n";
        clearInput();

        // Запрашиваем данные у пользователя
        cout << "Введите название задачи: ";
        newTask.name = safeInput();

        cout << "Введите срок выполнения: ";
        newTask.deadline = safeInput();

        // Цикл для корректного ввода приоритета
        while (true) {
            cout << "Введите приоритет (1-низкий, 2-средний, 3-высокий): ";
            if (cin >> newTask.priority && newTask.priority >= 1 && newTask.priority <= 3) {
                break;
            }
            cout << "Ошибка! Введите число от 1 до 3\n";
            clearInput();
        }

        // Добавляем задачу в вектор
        tasks.push_back(newTask);
        cout << "Задача успешно добавлена!\n";
    }

    // Функция для редактирования существующей задачи
    void editTask() {
        // Проверяем, есть ли задачи
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        int id;
        cout << "\n--- Редактирование задачи ---\n";
        cout << "Введите ID задачи для редактирования: ";
        cin >> id;

        // Ищем задачу с указанным ID
        for (Task& task : tasks) {
            if (task.id == id) {
                clearInput();

                // Запрашиваем новые данные
                cout << "Введите новое название задачи: ";
                task.name = safeInput();

                cout << "Введите новый срок выполнения: ";
                task.deadline = safeInput();

                // Цикл для корректного ввода нового приоритета
                while (true) {
                    cout << "Введите новый приоритет (1-низкий, 2-средний, 3-высокий): ";
                    if (cin >> task.priority && task.priority >= 1 && task.priority <= 3) {
                        break;
                    }
                    cout << "Ошибка! Введите число от 1 до 3\n";
                    clearInput();
                }

                cout << "Задача успешно отредактирована!\n";
                return;
            }
        }
        cout << "Задача с таким ID не найдена!\n";
    }

    // Функция для удаления задачи
    void deleteTask() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        int id;
        cout << "\n--- Удаление задачи ---\n";
        cout << "Введите ID задачи для удаления: ";
        cin >> id;

        // Ищем и удаляем задачу с указанным ID
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].id == id) {
                tasks.erase(tasks.begin() + i);
                cout << "Задача успешно удалена!\n";
                return;
            }
        }
        cout << "Задача с таким ID не найдена!\n";
    }

    // Функция для отображения всех задач
    void showTasks() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        cout << "\n--- Список всех задач ---\n";
        // Выводим информацию о каждой задаче
        for (const Task& task : tasks) {
            cout << "ID: " << task.id << "\n";
            cout << "Название: " << task.name << "\n";
            cout << "Срок: " << task.deadline << "\n";
            cout << "Приоритет: ";
            // Преобразуем числовой приоритет в текстовый
            switch (task.priority) {
            case 1: cout << "Низкий"; break;
            case 2: cout << "Средний"; break;
            case 3: cout << "Высокий"; break;
            }
            cout << "\n---------------\n";
        }
    }

    // Функция для фильтрации задач по приоритету
    void showTasksByPriority() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        int priority;
        cout << "Введите приоритет для фильтрации (1-низкий, 2-средний, 3-высокий): ";
        cin >> priority;

        cout << "\n--- Задачи с выбранным приоритетом ---\n";
        bool found = false;

        // Показываем только задачи с выбранным приоритетом
        for (const Task& task : tasks) {
            if (task.priority == priority) {
                cout << "ID: " << task.id << "\n";
                cout << "Название: " << task.name << "\n";
                cout << "Срок: " << task.deadline << "\n";
                cout << "---------------\n";
                found = true;
            }
        }

        if (!found) {
            cout << "Задачи с таким приоритетом не найдены.\n";
        }
    }

    // Функция для поиска задач по названию
    void searchTasksByName() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        clearInput();
        cout << "Введите часть названия для поиска: ";
        string searchTerm = safeInput();

        cout << "\n--- Результаты поиска ---\n";
        bool found = false;

        // Ищем задачи, содержащие введенный текст в названии
        for (const Task& task : tasks) {
            if (task.name.find(searchTerm) != string::npos) {
                cout << "ID: " << task.id << "\n";
                cout << "Название: " << task.name << "\n";
                cout << "Срок: " << task.deadline << "\n";
                cout << "Приоритет: ";
                switch (task.priority) {
                case 1: cout << "Низкий"; break;
                case 2: cout << "Средний"; break;
                case 3: cout << "Высокий"; break;
                }
                cout << "\n---------------\n";
                found = true;
            }
        }

        if (!found) {
            cout << "Задачи не найдены.\n";
        }
    }

    // Функция для сортировки и отображения задач по приоритету
    void showTasksSortedByPriority() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        // Создаем копию вектора для сортировки
        vector<Task> sortedTasks = tasks;

        // Сортируем задачи по приоритету (пузырьковая сортировка)
        for (int i = 0; i < sortedTasks.size() - 1; i++) {
            for (int j = 0; j < sortedTasks.size() - i - 1; j++) {
                if (sortedTasks[j].priority < sortedTasks[j + 1].priority) {
                    swap(sortedTasks[j], sortedTasks[j + 1]);
                }
            }
        }

        // Выводим отсортированный список
        cout << "\n--- Задачи по приоритету ---\n";
        for (const Task& task : sortedTasks) {
            cout << "ID: " << task.id << "\n";
            cout << "Название: " << task.name << "\n";
            cout << "Срок: " << task.deadline << "\n";
            cout << "Приоритет: ";
            switch (task.priority) {
            case 1: cout << "Низкий"; break;
            case 2: cout << "Средний"; break;
            case 3: cout << "Высокий"; break;
            }
            cout << "\n---------------\n";
        }
    }
};

// Главная функция программы
int main() {
    // Настраиваем кодировку для корректного отображения русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TaskManager manager;    // Создаем объект менеджера задач
    int choice;            // Переменная для хранения выбора пользователя

    // Основной цикл программы
    while (true) {
        // Выводим меню
        cout << "\n=== Менеджер задач ===\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Редактировать задачу\n";
        cout << "3. Удалить задачу\n";
        cout << "4. Показать все задачи\n";
        cout << "5. Фильтр по приоритету\n";
        cout << "6. Поиск по названию\n";
        cout << "7. Сортировка по приоритету\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        // Проверяем корректность ввода
        if (!(cin >> choice)) {
            cout << "Ошибка ввода! Пожалуйста, введите число.\n";
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

        // Обрабатываем выбор пользователя
        switch (choice) {
        case 1:
            manager.addTask();
            break;
        case 2:
            manager.editTask();
            break;
        case 3:
            manager.deleteTask();
            break;
        case 4:
            manager.showTasks();
            break;
        case 5:
            manager.showTasksByPriority();
            break;
        case 6:
            manager.searchTasksByName();
            break;
        case 7:
            manager.showTasksSortedByPriority();
            break;
        case 0:
            cout << "Программа завершена.\n";
            return 0;
        default:
            cout << "Неверный выбор!\n";
        }
    }

    return 0;
}