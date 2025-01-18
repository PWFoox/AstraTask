#include <iostream>
#include <string>
#include <vector>
#include <windows.h> // Для работы с русским языком в Windows
using namespace std;

// Структура для хранения данных о задаче
struct Task {
    int id;                 // Уникальный номер задачи
    string name;           // Название задачи
    string deadline;       // Срок выполнения
    int priority;          // Приоритет (1 - низкий, 2 - средний, 3 - высокий)
};

class TaskManager {
private:
    vector<Task> tasks;
    int nextId;

public:
    TaskManager() {
        nextId = 1;
    }

    // Функция для очистки буфера ввода
    void clearInput() {
        cin.clear();
        cin.ignore(32767, '\n');
    }

    // Функция для безопасного ввода строки
    string safeInput() {
        string input;
        getline(cin, input);
        return input;
    }

    void addTask() {
        Task newTask;
        newTask.id = nextId;
        nextId++;

        cout << "\n--- Добавление новой задачи ---\n";

        clearInput(); // Очищаем буфер перед вводом

        cout << "Введите название задачи: ";
        newTask.name = safeInput();

        cout << "Введите срок выполнения: ";
        newTask.deadline = safeInput();

        while (true) {
            cout << "Введите приоритет (1-низкий, 2-средний, 3-высокий): ";
            if (cin >> newTask.priority && newTask.priority >= 1 && newTask.priority <= 3) {
                break;
            }
            cout << "Ошибка! Введите число от 1 до 3\n";
            clearInput();
        }

        tasks.push_back(newTask);
        cout << "Задача успешно добавлена!\n";
    }

    void editTask() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        int id;
        cout << "\n--- Редактирование задачи ---\n";
        cout << "Введите ID задачи для редактирования: ";
        cin >> id;

        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].id == id) {
                clearInput();

                cout << "Введите новое название задачи: ";
                tasks[i].name = safeInput();

                cout << "Введите новый срок выполнения: ";
                tasks[i].deadline = safeInput();

                while (true) {
                    cout << "Введите новый приоритет (1-низкий, 2-средний, 3-высокий): ";
                    if (cin >> tasks[i].priority && tasks[i].priority >= 1 && tasks[i].priority <= 3) {
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

    void deleteTask() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        int id;
        cout << "\n--- Удаление задачи ---\n";
        cout << "Введите ID задачи для удаления: ";
        cin >> id;

        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].id == id) {
                tasks.erase(tasks.begin() + i);
                cout << "Задача успешно удалена!\n";
                return;
            }
        }
        cout << "Задача с таким ID не найдена!\n";
    }

    void showTasks() {
        if (tasks.empty()) {
            cout << "Список задач пуст!\n";
            return;
        }

        cout << "\n--- Список всех задач ---\n";

        for (const Task& task : tasks) {
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

int main() {
    // Настройка кодировки для Windows
    SetConsoleCP(1251);        // Установка кодировки для ввода
    SetConsoleOutputCP(1251);  // Установка кодировки для вывода

    TaskManager manager;
    int choice;

    while (true) {
        cout << "\n=== Менеджер задач ===\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Редактировать задачу\n";
        cout << "3. Удалить задачу\n";
        cout << "4. Показать все задачи\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        // Проверка корректности ввода
        if (!(cin >> choice)) {
            cout << "Ошибка ввода! Пожалуйста, введите число.\n";
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

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
        case 0:
            cout << "Программа завершена.\n";
            return 0;
        default:
            cout << "Неверный выбор!\n";
        }
    }

    return 0;
}