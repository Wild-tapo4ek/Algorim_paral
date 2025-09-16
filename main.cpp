#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    string name;
    int age;
    string major;
    double gpa;
};

// Функция для добавления студента в базу данных
void addStudent(vector<Student>& database) {
    Student student;
    cout << "Введите имя студента: ";
    cin >> student.name;
    cout << "Введите возраст студента: ";
    cin >> student.age;
    cout << "Введите специальность студента: ";
    cin >> student.major;
    cout << "Введите средний балл студента: ";
    cin >> student.gpa;

    database.push_back(student);
    cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const vector<Student>& database) {
    cout << "Список студентов:\n";
    for (const Student& student : database) {
        cout << "Имя: " << student.name << "\n";
        cout << "Возраст: " << student.age << "\n";
        cout << "Специальность: " << student.major << "\n";
        cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// Функция для вывода студентов в алфавитном порядке
void displayStudentsAlphabetically(vector<Student>& database) {
    
    // Лямбда-функция для сравнения студентов по имени
    auto compareByName = [](const Student& a, const Student& b) {
        return a.name < b.name;
    };
    
    // Создаем копию базы данных для сортировки
    vector<Student> sortedDatabase = database;
    
    // Сортируем по имени с помощью лямбда-функции
    sort(sortedDatabase.begin(), sortedDatabase.end(), compareByName);
    
    cout << "Список студентов в алфавитном порядке:\n";
    for (const Student& student : sortedDatabase) {
        cout << "Имя: " << student.name << "\n";
        cout << "Возраст: " << student.age << "\n";
        cout << "Специальность: " << student.major << "\n";
        cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

int main() {
    vector<Student> database;

    int choice;
    do {
        cout << "Меню:\n";
        cout << "1. Добавить студента\n";
        cout << "2. Вывести список студентов\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}