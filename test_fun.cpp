#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
using namespace std;

struct Student {
    string name;
    int age;
    string major;
    double gpa;
};

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
    if (database.empty()) {
        cout << "База данных пуста.\n";
        return;
    }
    
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

// Функция для ручного добавления студента (для тестирования)
void addStudentManually(vector<Student>& database, const string& name, 
                       int age, const string& major, double gpa) {
    Student student;
    student.name = name;
    student.age = age;
    student.major = major;
    student.gpa = gpa;
    database.push_back(student);
}

// Тестовые функции
TEST(StudentDatabaseTest, AddStudentTest) {
    vector<Student> database;
    
    // Добавляем студента
    addStudentManually(database, "Ivan", 20, "Computer Science", 4.5);
    
    // Проверяем, что студент добавлен
    ASSERT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Ivan");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "Computer Science");
    EXPECT_EQ(database[0].gpa, 4.5);
}

TEST(StudentDatabaseTest, EmptyDatabaseTest) {
    vector<Student> database;
    
    // Проверяем, что база пуста
    ASSERT_TRUE(database.empty());
    
    // Проверяем отображение пустой базы
    testing::internal::CaptureStdout();
    displayStudents(database);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Список студентов:") != string::npos);
}

TEST(StudentDatabaseTest, AlphabeticalOrderTest) {
    vector<Student> database;
    
    // Добавляем студентов в разном порядке
    addStudentManually(database, "Zoe", 22, "Biology", 3.8);
    addStudentManually(database, "Anna", 21, "Mathematics", 4.2);
    addStudentManually(database, "Max", 23, "Physics", 3.9);
    
    // Сортируем и проверяем порядок
    vector<Student> sortedDatabase = database;
    auto compareByName = [](const Student& a, const Student& b) {
        return a.name < b.name;
    };
    sort(sortedDatabase.begin(), sortedDatabase.end(), compareByName);
    
    // Проверяем алфавитный порядок
    EXPECT_EQ(sortedDatabase[0].name, "Anna");
    EXPECT_EQ(sortedDatabase[1].name, "Max");
    EXPECT_EQ(sortedDatabase[2].name, "Zoe");
}

TEST(StudentDatabaseTest, DisplayStudentsFunctionTest) {
    vector<Student> database;
    
    // Добавляем нескольких студентов
    addStudentManually(database, "John", 19, "Engineering", 3.7);
    addStudentManually(database, "Mary", 20, "Medicine", 4.8);
    
    // Перехватываем вывод функции displayStudents
    testing::internal::CaptureStdout();
    displayStudents(database);
    string output = testing::internal::GetCapturedStdout();
    
    // Проверяем, что вывод содержит заголовок
    EXPECT_TRUE(output.find("Список студентов:") != string::npos);
    
    // Проверяем, что вывод содержит имена всех студентов
    EXPECT_TRUE(output.find("John") != string::npos);
    EXPECT_TRUE(output.find("Mary") != string::npos);
    
    // Проверяем, что вывод содержит возраст
    EXPECT_TRUE(output.find("19") != string::npos);
    EXPECT_TRUE(output.find("20") != string::npos);
    
    // Проверяем, что вывод содержит специальности
    EXPECT_TRUE(output.find("Engineering") != string::npos);
    EXPECT_TRUE(output.find("Medicine") != string::npos);
    
    // Проверяем, что вывод содержит GPA
    EXPECT_TRUE(output.find("3.7") != string::npos);
    EXPECT_TRUE(output.find("4.8") != string::npos);
    
    // Проверяем структуру вывода (наличие ключевых слов)
    EXPECT_TRUE(output.find("Имя:") != string::npos);
    EXPECT_TRUE(output.find("Возраст:") != string::npos);
    EXPECT_TRUE(output.find("Специальность:") != string::npos);
    EXPECT_TRUE(output.find("Средний балл:") != string::npos);
}

TEST(StudentDatabaseTest, GPAValidationTest) {
    vector<Student> database;
    
    // Добавляем студентов с разным GPA
    addStudentManually(database, "LowGPA", 20, "Art", 2.0);
    addStudentManually(database, "HighGPA", 21, "Science", 4.9);
    addStudentManually(database, "AverageGPA", 22, "Business", 3.5);
    
    // Проверяем корректность хранения GPA
    EXPECT_DOUBLE_EQ(database[0].gpa, 2.0);
    EXPECT_DOUBLE_EQ(database[1].gpa, 4.9);
    EXPECT_DOUBLE_EQ(database[2].gpa, 3.5);
}

// Функция для запуска тестов
void runTests() {
    ::testing::InitGoogleTest();
    int result = RUN_ALL_TESTS();
}

int main(int argc, char** argv) {
    runTests();
    return 0;
}